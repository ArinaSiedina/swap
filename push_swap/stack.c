/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: login <login@student.42.fr>                 +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 12:00:00 by login             #+#    #+#             */
/*   Updated: 2026/09/14 12:00:00 by login            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// returns the element at the given position, counting from the head of the stack.
t_item get_item(t_stack *stack, int index)
{
	return (stack->items[((size_t)stack->head + index) % stack->capacity]);
}

void swap_upper_items(t_stack *stack)
{
	t_item tmp;
	int next;

	if (stack->size < 2)
		return;
	next = (stack->head + 1) % stack->capacity;
	tmp = stack->items[stack->head];
	stack->items[stack->head] = stack->items[next];
	stack->items[next] = tmp;
}

void moove_head_between_stacks(t_stack *from, t_stack *to)
{
	if (!from->size)
		return;
	to->head = ((size_t)to->head + to->capacity - 1) % to->capacity;
	to->items[to->head] = from->items[from->head];
	to->size++;
	from->head = (from->head + 1) % from->capacity;
	from->size--;
}

void moove_head_to_end(t_stack *stack)
{
	int last;

	if (stack->size < 2)
		return;
	last = ((size_t)stack->head + stack->size) % stack->capacity;
	stack->items[last] = stack->items[stack->head];
	stack->head = (stack->head + 1) % stack->capacity;
}

void moove_last_to_head(t_stack *stack)
{
	t_item last;

	if (stack->size < 2)
		return;
	last = get_item(stack, stack->size - 1);
	stack->head = ((size_t)stack->head + stack->capacity - 1) % stack->capacity;
	stack->items[stack->head] = last;
}
