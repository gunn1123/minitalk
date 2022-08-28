/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cthamsur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:29:27 by cthamsur          #+#    #+#             */
/*   Updated: 2022/08/22 15:28:48 by cthamsur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>

int		ft_atoi(char *str, int *res);
void	ft_putchar(char c);
void	ft_putstr(char *str);

void	send_char(int pid, char c)
{
	int	shift;
	int	i;

	i = 8;
	while (i >= 0)
	{
		shift = 1 << (i);
		if (c & shift)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(550);
		i--;
	}
}

void	send_message(int pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_char(pid, str[i]);
		i++;
	}
	send_char(pid, str[i]);
}

void	sighandler(int sig)
{
	(void)sig;
	//write(1, "hello", 6);
	ft_putstr("message send succasfully!!\n");
}

int	send(int pid, char *str)
{
	if (kill(pid, 0) == -1)
	{
		ft_putstr("Invalid PID\n");
		return (1);
	}
	else
	{
		if (pid == 0)
		{
			ft_putstr("Invalid PID\n");
			return (1);
		}
		send_message(pid, str);
		return (0);
	}
}

int	main(int ac, char **av)
{
	int	pid;

	if (ac != 3)
		return (1);
	signal(SIGUSR1, sighandler); // Register signal handler
	if (ft_atoi(av[1], &pid) == 0)
	{
		ft_putstr("invalid argument");
		return (1);
	}
	else
		return (send(pid, av[2]));
}
