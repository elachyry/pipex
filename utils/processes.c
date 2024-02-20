/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 23:36:13 by melachyr          #+#    #+#             */
/*   Updated: 2024/02/21 00:05:25 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	wait_for_children(t_pipex pipex)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 0;
	while (i < pipex.cmd_count)
	{
		waitpid(pipex.pid[i], &status, WCONTINUED);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		i++;
	}
	return (last_status);
}

void	child_process(t_pipex pipex, char **env, int index)
{
	if (index == 0)
		first_cmd(pipex, index);
	else if (index == pipex.cmd_count - 1)
		last_cmd(pipex, index);
	else
	{
		dup2(pipex.fd[index - 1][0], STDIN_FILENO);
		dup2(pipex.fd[index][1], STDOUT_FILENO);
		close_pipes(&pipex);
	}
	execute_cmd(pipex, env, index);
}

void	parent_process(t_pipex pipex, int *index)
{
	if (*index > 0)
	{
		close(pipex.fd[*index - 1][0]);
		close(pipex.fd[*index - 1][1]);
	}
	(*index)++;
}
