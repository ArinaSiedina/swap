/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: login <login@student.42.fr>                 +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:00:00 by login             #+#    #+#             */
/*   Updated: 2026/09/14 12:00:00 by login            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int get_strategy_index(const char *arg)
{
	if (ps_equal(arg, "--adaptive"))
		return (ADAPTIVE);
	if (ps_equal(arg, "--simple"))
		return (SIMPLE);
	if (ps_equal(arg, "--medium"))
		return (MEDIUM);
	if (ps_equal(arg, "--complex"))
		return (COMPLEX);
	return (-1);
}

// Checks for flags. Returns the argv index of the first numeric argument.
int identify_flags(t_ps *prog_state, int argc, char **argv)
{
	int order_index;
	int seen;
	int strategy_index;

	order_index = 1;
	seen = 0;
	while (order_index < argc && argv[order_index][0] == '-' && argv[order_index][1] == '-')
	{
		strategy_index = get_strategy_index(argv[order_index]);
		if (ps_equal(argv[order_index], "--bench") && !prog_state->bench)
			prog_state->bench = 1;
		else if (strategy_index >= 0 && !seen)
		{
			prog_state->requested_strategy = strategy_index;
			seen = 1;
		}
		else
			end_with_error(prog_state);
		order_index++;
	}
	return (order_index);
}

int count_numbers(t_ps *prog_state, int argc, char **argv, int start)
{
	char *str;
	int count;
	int before;

	count = 0;
	while (start < argc)
	{
		str = argv[start++];
		before = count;
		while (*str)
		{
			while (is_space(*str))
				str++;
			if (*str && count == INT_MAX)
				end_with_error(prog_state);
			count += (*str != '\0');
			while (*str && !is_space(*str))
				str++;
		}
		if (before == count)
			end_with_error(prog_state);
	}
	return (count);
}
