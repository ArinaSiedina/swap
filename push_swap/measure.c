/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   measure.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: login <login@student.42.fr>                 +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:00:00 by login             #+#    #+#             */
/*   Updated: 2026/09/14 12:00:00 by login            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static unsigned long long assign_rank_and_count_mistakes(t_stack *stack, int i)
{
	int j;
	int current_number;
	int compared_number;
	unsigned long long mistakes;

	mistakes = 0;
	current_number = stack->items[i].value;
	j = 0;
	while (j < stack->size)
	{
		compared_number = stack->items[j].value;
		if (current_number > compared_number)
		{
			stack->items[i].rank++;
			if (j > i)
				mistakes++;
		}
		j++;
	}
	return (mistakes);
}

void measure_disorder(t_ps *prog_state)
{
	int i;
	unsigned long long mistakes;
	unsigned long long pairs;

	mistakes = 0;
	i = 0;
	while (i < prog_state->stack_a.size)
	{
		mistakes += assign_rank_and_count_mistakes(&prog_state->stack_a, i);
		i++;
	}
	pairs = (unsigned long long)prog_state->stack_a.size * (prog_state->stack_a.size - 1) / 2;
	if (pairs)
		prog_state->disorder = (double)mistakes / (double)pairs;
}

