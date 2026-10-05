/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: login <login@student.42.fr>                 +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:00:00 by login             #+#    #+#             */
/*   Updated: 2026/09/14 12:00:00 by login            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void sort_three(t_ps *prog_state)
{
	int a;
	int b;
	int c;

	a = get_item(&prog_state->stack_a, 0).rank;
	b = get_item(&prog_state->stack_a, 1).rank;
	c = get_item(&prog_state->stack_a, 2).rank;
	if (a > b && a > c)
		process_operation(prog_state, RA);
	else if (b > a && b > c)
		process_operation(prog_state, RRA);
	if (get_item(&prog_state->stack_a, 0).rank > get_item(&prog_state->stack_a, 1).rank)
		process_operation(prog_state, SA);
}

void ps_simple(t_ps *prog_state)
{
	int index;

	while (prog_state->stack_a.size > 3
		&& !is_sorted(&prog_state->stack_a))
	{
		index = find_extreme(&prog_state->stack_a, 0);
		put_on_top(prog_state, index, 0);
		process_operation(prog_state, PB);
	}
	if (prog_state->stack_a.size == 3
		&& !is_sorted(&prog_state->stack_a))
		sort_three(prog_state);
	else if (prog_state->stack_a.size == 2
		&& !is_sorted(&prog_state->stack_a))
		process_operation(prog_state, SA);
	while (prog_state->stack_b.size)
		process_operation(prog_state, PA);
}
