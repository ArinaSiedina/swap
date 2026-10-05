/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: login <login@student.42.fr>                 +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:00:00 by login             #+#    #+#             */
/*   Updated: 2026/09/14 12:00:00 by login            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int parse_number(t_ps *prog_state, char **str)
{
	long long number;
	int sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	if (**str < '0' || **str > '9')
		end_with_error(prog_state);
	number = 0;
	while (**str >= '0' && **str <= '9')
	{
		number = number * 10 + (**str - '0');
		if (number > (long long)INT_MAX + (sign == -1))
			end_with_error(prog_state);
		(*str)++;
	}
	if (**str && !is_space(**str))
		end_with_error(prog_state);
	return ((int)(number * sign));
}
//Ads value of number to stack A with 0 rank
static void add_num_to_stack(t_ps *prog_state, int value)
{
	int i;
	int index;

	i = 0;
	while (i < prog_state->stack_a.size)
	{
		if (prog_state->stack_a.items[i].value == value)
			end_with_error(prog_state);
		i++;
	}
	index = prog_state->stack_a.size;
	prog_state->stack_a.items[index].value = value;
	prog_state->stack_a.items[index].rank = 0;
	prog_state->stack_a.size++;
}

static void extract_numbers(t_ps *prog_state, char *str)
{
	while (is_space(*str))
		str++;
	while (*str)
	{
		add_num_to_stack(prog_state, parse_number(prog_state, &str));
		while (is_space(*str))
			str++;
	}
}

void parse_args(t_ps *prog_state, int argc, char **argv)
{
	int start;
	int qty;

	start = identify_flags(prog_state, argc, argv);
	qty = count_numbers(prog_state, argc, argv, start);
	if (!qty)
		return;
	prog_state->stack_a.items = malloc(sizeof(t_item) * (size_t)qty);
	prog_state->stack_b.items = malloc(sizeof(t_item) * (size_t)qty);
	if (!prog_state->stack_a.items || !prog_state->stack_b.items)
		end_with_error(prog_state);
	prog_state->stack_a.capacity = qty;
	prog_state->stack_b.capacity = qty;
	while (start < argc)
		extract_numbers(prog_state, argv[start++]);
}
