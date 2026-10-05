/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: login <login@student.42.fr>                 +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:00:00 by login             #+#    #+#             */
/*   Updated: 2026/09/14 12:00:00 by login            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Rerurns rank of MIN(0) || MAX(1) in stack
int find_extreme(t_stack *stack, int find_max)
{
	int position_index;
	int index_of_best;
	int rank_of_best;
	int rank_of_candidate;

	index_of_best = 0;
	position_index = 1;
	while (position_index < stack->size)
	{
		rank_of_best = get_item(stack, index_of_best).rank;
		rank_of_candidate = get_item(stack, position_index).rank;
		if ((find_max && rank_of_candidate > rank_of_best) || (!find_max && rank_of_candidate < rank_of_best))
			index_of_best = position_index;
		position_index++;
	}
	return (index_of_best);
}

void put_on_top(t_ps *prog_state, int index, int is_stack_b)
{
	int size;
	t_op forward;
	t_op backward;

	size = prog_state->stack_a.size;
	forward = RA;
	backward = RRA;
	if (is_stack_b)
	{
		size = prog_state->stack_b.size;
		forward = RB;
		backward = RRB;
	}
	if (index <= size / 2)
		while (index-- > 0)
			process_operation(prog_state, forward);
	else
		while (index++ < size)
			process_operation(prog_state, backward);
}

int is_sorted(t_stack *stack)
{
	int i;

	i = 1;
	while (i < stack->size)
	{
		if (get_item(stack, i - 1).value > get_item(stack, i).value)
			return (0);
		i++;
	}
	return (1);
}

