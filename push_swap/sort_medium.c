/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: login <login@student.42.fr>                 +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:00:00 by login             #+#    #+#             */
/*   Updated: 2026/09/14 12:00:00 by login            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int chunk_width(int size)
{
	int width;

	width = 1;
	while ((long long)width * width < size)
		width++;
	return (width);
}

static void collect_chunks(t_ps *prog_state, int width)
{
	long long limit;
	int target;
	int pushed;

	limit = width;
	while (prog_state->stack_a.size)
	{
		target = width;
		if (target > prog_state->stack_a.size)
			target = prog_state->stack_a.size;
		pushed = 0;
		while (pushed < target)
		{
			if (get_item(&prog_state->stack_a, 0).rank < limit)
			{
				process_operation(prog_state, PB);
				pushed++;
			}
			else
				process_operation(prog_state, RA);
		}
		limit += width;
	}
}

static void return_chunks(t_ps *prog_state)
{
	while (prog_state->stack_b.size)
	{
		put_on_top(prog_state, find_extreme(&prog_state->stack_b, 1), 1);
		process_operation(prog_state, PA);
	}
}

void sort_medium(t_ps *prog_state)
{
	int width;

	width = chunk_width(prog_state->stack_a.size);
	collect_chunks(prog_state, width);
	return_chunks(prog_state);
}
