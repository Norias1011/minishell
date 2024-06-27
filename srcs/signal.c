/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akinzeli <akinzeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:00:53 by akinzeli          #+#    #+#             */
/*   Updated: 2024/06/17 11:44:44 by akinzeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler(void)
{
	struct sigaction	sa;

	nothing_signal();
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = &new_prompt;
	sigaction(SIGINT, &sa, NULL);
}

void	nothing_signal(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	new_prompt(int signo)
{
	(void)signo;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler_bis(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = &new_prompt_bis;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	new_prompt_bis(int signo)
{
	(void)signo;
	printf("\n");
	rl_on_new_line();
}