/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:22:35 by melachyr          #+#    #+#             */
/*   Updated: 2024/02/20 23:59:14 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	get_path(t_pipex *pipex, char **env)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			path = ft_strchr(env[i], '/');
			break ;
		}
		i++;
	}
	if (path)
		pipex->env = ft_split(path, ':');
	else
		pipex->env = ft_split("  ", ':');
}

void	get_infile_outfile(t_pipex *pipex, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i] != NULL)
	{
		if (i == 1)
		{
			if (pipex->is_here_doc)
				pipex->in_file_path = ft_strjoin(".", argv[i]);
			else
				pipex->in_file_path = argv[i];
		}
		if (argv[i + 1] == NULL)
			pipex->out_file_path = argv[i];
		i++;
	}
}

void	init_vars(t_pipex *pipex, char **argv, char argc, char **env)
{
	pipex->cmd_loc = NULL;
	pipex->cmd = NULL;
	pipex->env = NULL;
	pipex->delimiter = NULL;
	pipex->is_here_doc = 0;
	get_path(pipex, env);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		pipex->cmd_count = argc - 4;
		pipex->is_here_doc = 1;
		pipex->delimiter = ft_strjoin(argv[2], "\n");
	}
	else
		pipex->cmd_count = argc - 3;
	pipex->pid = malloc(sizeof(int) * pipex->cmd_count);
	if (pipex->pid == NULL)
		return ;
	pipex->fd = malloc(sizeof(int *) * (pipex->cmd_count - 1));
	if (pipex->fd == NULL)
		return ;
	get_infile_outfile(pipex, argv);
}
// int i = 0;
// 	while (pipex->in_cmd[i] != NULL)
// 	{
// 		printf("%s\n", pipex->in_cmd[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (pipex->out_cmd[i] != NULL)
// 	{
// 		printf("%s\n", pipex->out_cmd[i]);
// 		i++;
// 	}