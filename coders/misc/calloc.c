/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 12:24:55 by gaspard           #+#    #+#             */
/*   Updated: 2026/04/04 12:30:54 by gaspard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	ft_bzero(void *dst, size_t n)
{
	size_t	i;
	char	*new_dst;

	i = 0;
	new_dst = dst;
	while (i < n)
	{
		new_dst[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*alloc;

	if (size != 0 && (nmemb * size) / size != nmemb)
		return (NULL);
	alloc = malloc(nmemb * size);
	if (!alloc)
		return (NULL);
	ft_bzero(alloc, size * nmemb);
	return (alloc);
}