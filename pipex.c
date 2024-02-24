/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:28:17 by melachyr          #+#    #+#             */
/*   Updated: 2024/02/24 21:10:12 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int	start_program(t_pipex pipex, char **env, char **argv)
{
	int	i;
	int	return_status;

	i = 0;
	create_pipes(&pipex);
	while (i < pipex.cmd_count)
	{
		pipex.pid[i] = fork();
		if (pipex.pid[i] == -1)
			command_error("fork", 1);
		get_cmd(&pipex, argv[i], i);
		if (pipex.pid[i] == 0)
			child_process(pipex, env, i);
		else
			parent_process(pipex, &i);
		free_table(pipex.cmd);
	}
	return_status = wait_for_children(pipex);
	close_pipes(&pipex);
	free_up(&pipex);
	return (return_status);
}

void	write_here_doc(t_pipex pipex)
{
	char	*str;
	int		infile;

	infile = open(pipex.in_file_path, O_CREAT | O_RDWR, 0644);
	write(1, "> ", 2);
	while (1)
	{
		str = get_next_line(0);
		if (str)
		{
			if (ft_strcmp(pipex.delimiter, str) == 0)
			{
				free(str);
				break ;
			}
			write(1, "> ", 2);
			write(infile, str, strlen(str));
			free(str);
		}
	}
	close(infile);
}

int	check_args_count(int argc, char **argv, char **env)
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (argc <= 5 || env == NULL)
			return (1);
	}
	else
	{
		if (argc < 5 || env == NULL)
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		return_status;

	if (check_args_count(argc, argv, env))
		return (1);
	return_status = 0;
	init_vars(&pipex, argv, argc, env);
	if (pipex.is_here_doc)
	{
		write_here_doc(pipex);
		argv += 3;
	}
	else
		argv += 2;
	return_status = start_program(pipex, env, argv);
	if (pipex.is_here_doc)
	{
		if (unlink(pipex.in_file_path) == -1)
			command_error("unlink", 1);
	}
	return (return_status);
}
