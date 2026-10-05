/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: login <login@student.42.fr>                 +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:00:00 by login             #+#    #+#             */
/*   Updated: 2026/09/14 12:00:00 by login            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int ps_equal(const char *a, const char *b)
{
	while (*a && *a == *b)
	{
		a++;
		b++;
	}
	return (*a == *b);
}

int is_space(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

void ps_putstr(int fd, const char *str)
{
	size_t len;

	len = 0;
	while (str[len])
		len++;
	write(fd, str, len);
}

void ps_putnum(int fd, unsigned long long number)
{
	char buffer[21];
	int index;

	index = 20;
	buffer[index] = '\0';
	while (number >= 10)
	{
		buffer[--index] = '0' + number % 10;
		number /= 10;
	}
	buffer[--index] = '0' + number;
	ps_putstr(fd, buffer + index);
}
