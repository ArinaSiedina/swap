/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: login <login@student.42.fr>                 +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:00:00 by login             #+#    #+#             */
/*   Updated: 2026/09/14 12:00:00 by login            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void radix_pass(t_ps *prog_state, int bit)
{
	int	current_rank;
	int	size;
	int	i;

	size = prog_state->stack_a.size;
	i = 0;
	while (i < size)
	{
		current_rank = get_item(&prog_state->stack_a, 0).rank;
		if (((current_rank >> bit) & 1) == 0)
			process_operation(prog_state, PB);
		else
			process_operation(prog_state, RA);
		i++;
	}
	while (prog_state->stack_b.size > 0)
		process_operation(prog_state, PA);
}

void sort_complex(t_ps *prog_state)
{
	int max_rank;
	int max_bits;
	int bit;

	max_rank = prog_state->stack_a.size - 1;
	max_bits = 0;
	while ((max_rank >> max_bits) != 0)
		max_bits++;
	bit = 0;
	while (bit < max_bits)
	{
		radix_pass(prog_state, bit);
		bit++;
	}
}
