/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthamsur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:20:52 by cthamsur          #+#    #+#             */
/*   Updated: 2022/08/22 15:35:13 by cthamsur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

pid_t	getpid(void);
void	ft_putchar(char c);
void	ft_putnbr(int nb);

void	rec(int n, int pid)
{
	int				shift;
	static int		i = 7;
	static char		c;
	pid_t	g_clientpid;

	if (i == -1 || pid != g_clientpid)
	{
		i = 7;
		c = 0;
		g_clientpid = pid;
	}
	shift = 1 << (i);
	if (n != 0)
		c = (c | shift);
	i--;
	if (i == -1)
	{
		write (1, &c, 1);
		if (c == 0)
		{
			write(1, "\n", 1);
			kill(g_clientpid, SIGUSR1);
		}			
	}
}

void	server(void)
{
	int	pid;

	pid = getpid();
	write(1, "Process ID: ", 12);
	ft_putnbr(pid);
	write(1, "\n", 1);
}

void	sig_handler(int sig, siginfo_t *info, void *ptr)
{
	(void)ptr;
	if (sig == SIGUSR1)
		rec(1, info->si_pid);
	else
		rec(0, info->si_pid);
}

int	main(void)
{
	struct sigaction	act;

	act.sa_flags = 0;
	act.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &act, 0);
	sigaction(SIGUSR2, &act, 0);
	server();
	while (1)
		pause();
	return (0);
}
