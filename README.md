*This project has been created as part of the 42 curriculum by gtourdia*


<!-- OPULLALA REVOIS LE MAKE -->
<!-- ET REVOIS LE PARSING -->
<!-- chaines de char vides -->
<!-- valeurs a 0 -->
<!-- enchaine,ent de nulls -->
<!-- check valeur de illegale usleep -->


# Description
Codexion is a project from the 42 common core where the developper has to simulate multiple coders trying
to "survive" by compiling, debugging and refactoring code. If a coder doesn't compile in the given time,
he will make a burn-out and the simulation will be over. A coder needs two USB dongles to compile, and
there are as many dongles as coders.

Also, a dongle has a cooldown before being used again to compile.

It's kinda like the Philosophers problem, but with coders.

To realize this project, the student must use multi-threading using the pthread library in C, to simulate
each coder, along side with a priority queue.

## Instructions

### Installation with make

```bash
make
```


### Running the simulation

1. **Basic execution**:

	```bash
	make run # Run with default arguments
	```

	```bash
	# Default args
	NB_CODERS=10
	BURNOUT=3000
	COMPILE=200
	DEBUG=100
	REFACTOR=200
	NB_COMPILES=10
	DONGLE_COOLDOWN=400
	SCHEDULER=fifo

	Example : make run NB_CODERS=5
	```

2. **Run without make**:
	```bash
	./$codexion <NB_CODERS> <BURNOUT> <COMPILE> <DEBUG> <REFACTOR> <NB_COMPILES> <DONGLE_COOLDOWN> <SCHEDULER>
	```

### Other make commands

1. **Valgrind leaks check**:
   ```bash
   make valgrind
   ```

2. **Debug** (recompile and runs the program):
   ```bash
   make dbg
   ```

3. **Remove useless files created during compilation**:
   ```bash
   make clean
   ```

4. **Remove all created files**:
   ```bash
   make fclean
   ```

5. **Recompile**:
   ```bash
   make re
   ```

## Resources

### Documentation & References
- https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2 to understand the basics of multi-threading in C

### AI Usage

AI tools (GitHub Copilot & Google Gemini) were utilized for:

- Finding memory leaks
- Understanding the subject, and the problems I was going to encounter
- Debug my code

## Additionnal informations

### Deadlock prevention

I prevented deadlock by restricting the coders to having both dongles available and being number 1 in the priority queue of its left dongle to then take both at one time.

Also, I added a function to bypass priority queue when a deadlock is inevitable.

To finish, I pushed all non-even coder_ids first, and then the even one to each dongle's heap.
This way, coders will alternate compilation between even and non-even ones, preventing deadlock
and optimizing everything.

### Log serialization

I used a mutex to lock the printf usage. Therefore, no coders can print at the same time.

### Burnout & End detection

I created a separate thread that checks constantly if there is a burn-out. This thread is waited to complete before the end of the program, and leave its while loop only where there is an end of simulation or if there is a burn-out.

### Thread synchronization mechanisms

A coder uses the "can_pick_dongles()" function to check securely if a dongle is available, by securing it with its mutex. It is therefore impossible to check a dongle from two threads at the same time.

Once a dongle is available, it is "locked" until the coder is finished compiling.

## Authors

- [@sousampere](https://github.com/sousampere)

## 🚀 About Me
I am a student at the 42 Mulhouse school. Most of my public projects will be from this school, while I will keep private most of my other projects.

## Contact me !

 - [LinkedIn](https://fr.linkedin.com/in/gaspardtourdiat)
 - [My website](https://gaspardtourdiat.fr/)
 - [For 42 students (my intra profile)](https://profile.intra.42.fr/users/gtourdia)


![Logo](https://github.com/sousampere/sousampere/blob/main/42mulhouse.png?raw=true)
