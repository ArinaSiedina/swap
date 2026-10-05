/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: login <login@student.42.fr>                 +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:00:00 by login             #+#    #+#             */
/*   Updated: 2026/09/14 12:00:00 by login            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

typedef enum e_op
{
	SA,	 // swap first two elements of stack A
	SB,	 // swap first two elements of stack B
	SS,	 // execute SA and SB
	PA,	 // move top element from B to A
	PB,	 // move top element from A to B
	RA,	 // move top element of A to the bottom
	RB,	 // move top element of B to the bottom
	RR,	 // execute RA and RB
	RRA, // move bottom element of A to the top
	RRB, // move bottom element of B to the top
	RRR	 // execute RRA and RRB
} t_op;

typedef enum e_strategy
{
	ADAPTIVE,
	SIMPLE,
	MEDIUM,
	COMPLEX
} t_strategy;

typedef struct s_item
{
	int value;
	int rank;
} t_item;

typedef struct s_stack
{
	t_item *items;
	int capacity;
	int size;
	int head;
} t_stack;

typedef struct s_prog_state
{
	t_stack stack_a;
	t_stack stack_b;
	t_strategy requested_strategy;
	t_strategy selected_strategy;
	int bench;
	double disorder;
	unsigned long long counts[11];
	unsigned long long total;
} t_ps;

int ps_equal(const char *a, const char *b);
int is_space(char c);
void ps_putstr(int fd, const char *str);
void ps_putnum(int fd, unsigned long long number);
void init_prog_state(t_ps *prog_state);
void free_stacks(t_ps *prog_state);
void end_with_error(t_ps *prog_state);
void parse_args(t_ps *prog_state, int argc, char **argv);
int identify_flags(t_ps *prog_state, int argc, char **argv);
int count_numbers(t_ps *prog_state, int argc, char **argv, int start);
void measure_disorder(t_ps *prog_state);
t_item get_item(t_stack *stack, int index);
int is_sorted(t_stack *stack);
void swap_upper_items(t_stack *stack);
void moove_head_between_stacks(t_stack *from, t_stack *to);
void moove_head_to_end(t_stack *stack);
void moove_last_to_head(t_stack *stack);
const char *get_operation_name(t_op op);
void process_operation(t_ps *prog_state, t_op op);
void put_on_top(t_ps *prog_state, int index, int is_stack_b);
int find_extreme(t_stack *stack, int maximum);
void ps_simple(t_ps *prog_state);
void sort_medium(t_ps *prog_state);
void sort_complex(t_ps *prog_state);
void print_benchmark_report(t_ps *prog_state);

#endif
