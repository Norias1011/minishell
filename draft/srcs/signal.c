/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:00:53 by akinzeli          #+#    #+#             */
/*   Updated: 2024/05/29 16:31:04 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* general function to handle all the signals*/
void	signal_handler(void)
{
	struct sigaction	sa;

	nothing_signal();
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = &new_prompt;
	sigaction(SIGINT, &sa, NULL);
}
/* function that when the user do ctrl-\ nothing happen and its ignored*/
void	nothing_signal(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
/* function that display a new prompt with a newline */
void	new_prompt(int signo)
{
	(void)signo;
	printf("\n");
	// write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
