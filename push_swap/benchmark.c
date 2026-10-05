/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: login <login@student.42.fr>                 +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:00:00 by login             #+#    #+#             */
/*   Updated: 2026/09/14 12:00:00 by login            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void print_disorder(t_ps *prog_state)
{
	unsigned long long percent;

	percent = (unsigned long long)(prog_state->disorder * 10000.0 + 0.5);
	ps_putstr(2, "[bench] disorder: ");
	ps_putnum(2, percent / 100);
	ps_putstr(2, ".");
	if (percent % 100 < 10)
		ps_putstr(2, "0");
	ps_putnum(2, percent % 100);
	ps_putstr(2, "%\n");
}

static void print_strategy(t_ps *prog_state)
{
	ps_putstr(2, "[bench] strategy: ");
	if (prog_state->requested_strategy == ADAPTIVE)
		ps_putstr(2, "Adaptive / ");
	if (prog_state->selected_strategy == SIMPLE)
		ps_putstr(2, "Simple / O(n^2)\n");
	else if (prog_state->selected_strategy == MEDIUM)
		ps_putstr(2, "Medium / O(n*sqrt(n))\n");
	else
		ps_putstr(2, "Complex / O(n*log(n))\n");
}

void print_benchmark_report(t_ps *prog_state)
{
	int i;

	print_disorder(prog_state);
	print_strategy(prog_state);
	ps_putstr(2, "[bench] total_ops: ");
	ps_putnum(2, prog_state->total);
	ps_putstr(2, "\n");
	i = 0;
	while (i < 11)
	{
		ps_putstr(2, "[bench] ");
		ps_putstr(2, get_operation_name(i));
		ps_putstr(2, ": ");
		ps_putnum(2, prog_state->counts[i]);
		ps_putstr(2, "\n");
		i++;
	}
}
