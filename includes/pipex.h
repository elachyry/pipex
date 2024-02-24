/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:55:21 by melachyr          #+#    #+#             */
/*   Updated: 2024/02/24 21:09:52 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "get_next_line.h"

typedef struct s_pipex
{
	char	**env;
	char	**cmd;
	int		**fd;
	int		*pid;
	char	*cmd_loc;
	char	*in_file_path;
	char	*out_file_path;
	int		cmd_count;
	int		is_here_doc;
	char	*delimiter;

}	t_pipex;

//libft
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
char	**ft_split(char const *s, char sep);
char	**ft_split_2(char const *s);
char	*ft_strjoin(char *s1, char *s2, int allocated);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		ft_strcmp(const char *str1, const char *str2);

//init
void	init_vars(t_pipex *pipex, char **argv, char argc, char **env);
int		get_cmd_location(t_pipex *pipex);
void	free_table(char **tab);

//exceptions
void	command_error(char *msg, int exit_val);
void	free_up(t_pipex *pipex);
void	command_not_found(char *cmd, int exit_val);

//utils
int		wait_for_children(t_pipex pipex);
void	child_process(t_pipex pipex, char **env, int index);
void	parent_process(t_pipex pipex, int *index);
void	create_pipes(t_pipex *pipex);
void	close_pipes(t_pipex *pipex);
void	first_cmd(t_pipex pipex, int index);
void	last_cmd(t_pipex pipex, int index);
void	execute_cmd(t_pipex pipex, char **env);
void	get_cmd(t_pipex *pipex, char *incmd, int i);

#endif