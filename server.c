/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnona <pnona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 18:38:09 by pnona             #+#    #+#             */
/*   Updated: 2022/03/19 16:44:33 by pnona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_message	g_message;

static void	init_message(t_message *message)
{
	int	i;

	i = 0;
	message->flag = 1;
	message->bit_num = 0;
	message->char_num = 0;
	while (i < BUFF)
	{
		message->str[i] = 0;
		i++;
	}
}

static void	write_message(void)
{
	int	i;

	write(1, g_message.str, g_message.char_num);
	i = 0;
	while (i < g_message.char_num)
	{
		g_message.str[i] = 0;
		i++;
	}
	g_message.char_num = 0;
}

static void	get_message(int sig, siginfo_t *info, void *context)
{
	int	bit;

	(void)context;
	if (sig == SIGUSR1)
		bit = 0;
	else
		bit = 1;
	g_message.str[g_message.char_num] |= (bit << (7 - g_message.bit_num));
	if (++g_message.bit_num == 8)
	{
		if (g_message.str[g_message.char_num] == '\0')
		{
			g_message.flag = 0;
			write_message();
			kill(info->si_pid, SIGUSR2);
			write(1, "\n", 1);
			return ;
		}
		g_message.bit_num = 0;
		g_message.char_num++;
		if (g_message.char_num == BUFF)
			write_message();
	}
	usleep(50);
	kill(info->si_pid, SIGUSR1);
}

static void	decoder(void)
{
	struct sigaction	handler;

	handler.sa_sigaction = get_message;
	handler.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &handler, NULL) < 0)
	{
		write(1, "Error sigaction\n", 17);
		exit(0);
	}
	if (sigaction(SIGUSR2, &handler, NULL) < 0)
	{
		write(1, "Error sigaction\n", 17);
		exit(0);
	}
	while (g_message.flag)
		pause();
}

int	main(void)
{
	int		pid;
	char	message[BUFF];

	g_message.str = message;
	pid = getpid();
	write(1, "My PID: ", 8);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	while (1)
	{
		init_message(&g_message);
		decoder();
	}
}
