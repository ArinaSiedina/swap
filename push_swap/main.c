/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: login <login@student.42.fr>                 +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:00:00 by login             #+#    #+#             */
/*   Updated: 2026/09/14 12:00:00 by login            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void sort_based_on_strategy(t_ps *prog_state)
{
	prog_state->selected_strategy = prog_state->requested_strategy;
	if (prog_state->requested_strategy == ADAPTIVE)
	{
		if (prog_state->disorder < 0.2)
			prog_state->selected_strategy = SIMPLE;
		else if (prog_state->disorder < 0.5)
			prog_state->selected_strategy = MEDIUM;
		else
			prog_state->selected_strategy = COMPLEX;
	}
	if (is_sorted(&prog_state->stack_a))
		return;
	if (prog_state->stack_a.size <= 5)
		ps_simple(prog_state);
	else if (prog_state->selected_strategy == SIMPLE)
		ps_simple(prog_state);
	else if (prog_state->selected_strategy == MEDIUM)
		sort_medium(prog_state);
	else
		sort_complex(prog_state);
}

int main(int argc, char **argv)
{
	t_ps prog_state;

	init_prog_state(&prog_state);
	parse_args(&prog_state, argc, argv);
	if (prog_state.stack_a.size == 0)
		return (free_stacks(&prog_state), 0);
	measure_disorder(&prog_state);
	sort_based_on_strategy(&prog_state);
	if (prog_state.bench)
		print_benchmark_report(&prog_state);
	free_stacks(&prog_state);
	return (0);
}
