/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 23:42:08 by melachyr          #+#    #+#             */
/*   Updated: 2024/02/21 00:08:17 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	first_cmd(t_pipex pipex, int index)
{
	int	infile;

	infile = open(pipex.in_file_path, O_RDONLY);
	if (infile == -1)
		command_error(pipex.in_file_path, 1);
	dup2(infile, STDIN_FILENO);
	dup2(pipex.fd[index][1], STDOUT_FILENO);
	close(infile);
	close_pipes(&pipex);
}

void	last_cmd(t_pipex pipex, int index)
{
	int	outfile;

	outfile = open(pipex.out_file_path,
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfile == -1)
		command_error(pipex.out_file_path, 1);
	dup2(pipex.fd[index - 1][0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	close_pipes(&pipex);
}

void	execute_cmd(t_pipex pipex, char **env, int index)
{
	int	result;

	result = get_cmd_location(&pipex, index);
	if (!result)
		command_not_found(pipex.cmd[0], 127);
	else if (result == 2)
		command_error(pipex.cmd[0], 127);
	else if (result == 3)
		command_error(pipex.cmd[0], 126);
	execve(pipex.cmd_loc, pipex.cmd, env);
	command_error("execve", 1);
}
