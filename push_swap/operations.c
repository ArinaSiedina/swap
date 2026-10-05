/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: login <login@student.42.fr>                 +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:00:00 by login             #+#    #+#             */
/*   Updated: 2026/09/14 12:00:00 by login            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

const char *get_operation_name(t_op operation)
{
	static const char *const names[] = {
		"sa", "sb", "ss", "pa", "pb",
		"ra", "rb", "rr", "rra", "rrb", "rrr"};

	return (names[operation]);
}

static void execute(t_stack *stack_a, t_stack *stack_b, t_op operation)
{
	if (operation == SA || operation == SS)
		swap_upper_items(stack_a);
	if (operation == SB || operation == SS)
		swap_upper_items(stack_b);
	if (operation == PA)
		moove_head_between_stacks(stack_b, stack_a);
	if (operation == PB)
		moove_head_between_stacks(stack_a, stack_b);
	if (operation == RA || operation == RR)
		moove_head_to_end(stack_a);
	if (operation == RB || operation == RR)
		moove_head_to_end(stack_b);
	if (operation == RRA || operation == RRR)
		moove_last_to_head(stack_a);
	if (operation == RRB || operation == RRR)
		moove_last_to_head(stack_b);
}

void process_operation(t_ps *prog_state, t_op operation)
{
	execute(&prog_state->stack_a, &prog_state->stack_b, operation);
	prog_state->counts[operation]++;
	prog_state->total++;
	ps_putstr(1, get_operation_name(operation));
	ps_putstr(1, "\n");
}
