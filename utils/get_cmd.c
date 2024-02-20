/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_in_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:01:36 by melachyr          #+#    #+#             */
/*   Updated: 2024/02/20 23:26:12 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	arglen(char *arg)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] != ' ')
			c++;
		i++;
	}
	return (c);
}

void	check_empty_cmd(t_pipex *pipex, char *incmd, int i)
{
	if (!arglen(incmd) && i == 0)
		exit(0);
	else if (!arglen(incmd) && i == pipex->cmd_count - 2)
		exit(0);
	else if (!arglen(incmd))
		exit(258);
}

void	get_cmd(t_pipex *pipex, char *incmd, int i)
{
	char	**result;
	int		j;

	check_empty_cmd(pipex, incmd, i);
	result = ft_split_2(incmd);
	if (result[0] == NULL)
		return ;
	j = 0;
	while (result[j] != NULL)
		j++;
	pipex->cmd = malloc(sizeof(char **) * (j + 1));
	if (pipex->cmd == NULL)
		return ;
	j = 0;
	while (result[j] != NULL)
	{
		pipex->cmd[j] = result[j];
		j++;
	}
	pipex->cmd[j] = NULL;
	free(result);
}
