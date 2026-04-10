## Algorithm

### Initialization
- Parse and validate all 8 arguments. Reject negatives, non-integers,
  or a scheduler other than `fifo` or `edf`.
- Allocate N dongles and N coders (N = number_of_coders).
- Each dongle sits between coder i and coder (i+1) % N.
  Special case: if N == 1, there is only one dongle and the coder
  cannot compile (can never hold two dongles), so they burn out
  immediately.
- Each dongle has:
    - a mutex protecting its state
    - a condition variable managing its waiting queue
    - a priority queue (min-heap) of pending requests
    - a cooldown timestamp (time it becomes available again)
- Each coder has:
    - a thread (pthread_create)
    - a compile counter
    - a last_compile_start timestamp (initialized to simulation start)
- A shared monitor thread is launched to watch for burnout.
- A shared log mutex serializes all output.
- Record the simulation start time with gettimeofday().

### Coder thread loop
Repeat until the simulation stop flag is set:

1. **Request both dongles**
   - Register a request on the coder's left dongle and right dongle,
     recording the request arrival time (for fifo) and the coder's
     current deadline = last_compile_start + time_to_burnout (for edf).
   - IMPORTANT: to avoid deadlock, never hold one dongle's mutex while
     acquiring the other's. Use a global arbitration lock or request
     both simultaneously so no circular wait can form.
   - Wait on each dongle's condition variable until:
       - the dongle's cooldown has elapsed, AND
       - this coder is at the front of the dongle's priority queue
         (fifo: earliest request time; edf: earliest deadline).
   - Log: `timestamp X has taken a dongle` for each dongle acquired.

2. **Compile**
   - Log: `timestamp X is compiling`
   - Update last_compile_start = now.
   - Sleep for time_to_compile milliseconds (usleep).
   - Increment the coder's compile counter.

3. **Release both dongles**
   - For each dongle:
       - Set its available_at = now + dongle_cooldown.
       - Remove this coder from the dongle's queue.
       - Signal the condition variable so waiting coders can re-check.

4. **Debug**
   - Log: `timestamp X is debugging`
   - Sleep for time_to_debug milliseconds.

5. **Refactor**
   - Log: `timestamp X is refactoring`
   - Sleep for time_to_refactor milliseconds.
   - Loop back to step 1.

### Monitor thread
- Runs in a tight loop (sleeping ~1 ms between checks).
- For each coder, check:
    deadline = last_compile_start + time_to_burnout
  If now >= deadline and the coder has not started compiling in time:
    - Log: `timestamp X burned out` (must print within 10 ms of actual burnout).
    - Set the global simulation stop flag.
    - Broadcast on all condition variables to wake blocked threads.
    - Exit.
- Also check: if all coders have compile_count >= number_of_compiles_required,
  set the stop flag and exit.

### Shutdown
- Join all coder threads and the monitor thread.
- Destroy all mutexes and condition variables.
- Free all allocated memory.