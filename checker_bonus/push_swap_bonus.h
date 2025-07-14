/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzeybek <vzeybek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:26:49 by vzeybek           #+#    #+#             */
/*   Updated: 2025/06/16 20:26:50 by vzeybek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_BONUS_H
# define PUSH_SWAP_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "../push_swap.h"

int		rotate_bonus(t_stack *stack_a, t_stack *stack_b, char *name);
int		apply_operation(t_stack *a, t_stack *b, char *str);
void	sa_bonus(t_stack *stack_a);
void	sb_bonus(t_stack *stack_b);
void	pa_bonus(t_stack *stack_a, t_stack *stack_b);
void	pb_bonus(t_stack *stack_a, t_stack *stack_b);
void	ra_bonus(t_stack *stack_a);
void	rb_bonus(t_stack *stack_b);
void	rra_bonus(t_stack *stack_a);
void	rrb_bonus(t_stack *stack_b);
void	ss_bonus(t_stack *stack_a, t_stack *stack_b);

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
size_t	ft_strlen(char *s);

#endif