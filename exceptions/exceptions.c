/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:53:19 by melachyr          #+#    #+#             */
/*   Updated: 2024/02/24 21:04:09 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	command_error(char *msg, int exit_val)
{
	perror(msg);
	exit(exit_val);
}

void	command_not_found(char *cmd, int exit_val)
{
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	exit(exit_val);
}

void	free_table(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_int_table(int **tab, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_up(t_pipex *pipex)
{
	free_table(pipex->env);
	free_int_table(pipex->fd, pipex->cmd_count - 1);
	free(pipex->pid);
}
