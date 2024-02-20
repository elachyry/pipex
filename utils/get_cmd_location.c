/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_in_cmd_location.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:51:16 by melachyr          #+#    #+#             */
/*   Updated: 2024/02/20 23:26:57 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	search_in_env(t_pipex *pipex)
{
	int		i;
	char	*path;

	i = 0;
	while (pipex->env[i] != NULL)
	{
		path = ft_strjoin(pipex->env[i], "/");
		path = ft_strjoin(path, pipex->cmd[0]);
		if (access(path, X_OK) != -1)
		{
			pipex->cmd_loc = path;
			return (1);
		}
		free(path);
		i++;
	}
	return (0);
}

int	get_cmd_location(t_pipex *pipex, int i)
{
	char	*cmd;

	if (pipex->cmd[0] == NULL)
		exit(0);
	cmd = ft_strrchr(pipex->cmd[0], '/');
	if (cmd != NULL)
	{
		if (access(pipex->cmd[0], R_OK) != -1)
		{
			pipex->cmd_loc = pipex->cmd[0];
			return (1);
		}
		else
		{
			if (errno == EACCES)
				return (3);
			else
				return (2);
		}
	}
	cmd = pipex->cmd[0];
	return (search_in_env(pipex));
}
