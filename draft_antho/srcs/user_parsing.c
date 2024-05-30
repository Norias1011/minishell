/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 03:31:16 by akinzeli          #+#    #+#             */
/*   Updated: 2024/05/30 04:05:09 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	input_user_parser(t_minishell *minishell)
{
	if (!(minishell->prompt))
		return (false);
	add_history(minishell->prompt);
	return (true);
}