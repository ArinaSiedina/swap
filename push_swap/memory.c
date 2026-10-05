/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: login <login@student.42.fr>                 +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:00:00 by login             #+#    #+#             */
/*   Updated: 2026/09/14 12:00:00 by login            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void init_stack(t_stack *stack)
{
	stack->items = NULL;
	stack->capacity = 0;
	stack->size = 0;
	stack->head = 0;
}

void init_prog_state(t_ps *prog_state)
{
	int i;

	init_stack(&prog_state->stack_a);
	init_stack(&prog_state->stack_b);
	prog_state->requested_strategy = ADAPTIVE;
	prog_state->selected_strategy = ADAPTIVE;
	prog_state->bench = 0;
	prog_state->disorder = 0;
	prog_state->total = 0;
	i = 0;
	while (i < 11)
		prog_state->counts[i++] = 0;
}

void free_stacks(t_ps *prog_state)
{
	free(prog_state->stack_a.items);
	free(prog_state->stack_b.items);
}

void end_with_error(t_ps *prog_state)
{
	free_stacks(prog_state);
	ps_putstr(2, "Error\n");
	exit(1);
}
