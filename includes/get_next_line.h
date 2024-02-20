/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:47:58 by melachyr          #+#    #+#             */
/*   Updated: 2023/11/28 09:55:51 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

int		ft_fetsh_new_line(t_list *lst);
char	*ft_extract_line(t_list *lst);
void	ft_get_string(t_list *list, char *str);
int		ft_get_next_line_len(t_list *lst);
void	ft_fix_lst(t_list **lst);
char	*get_next_line(int fd);
void	ft_free_lst(t_list **lst, t_list *clean_node, char *buf);
void	ft_fill_lst(t_list **lst, int fd, t_list *last_node);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(char *content);
void	ft_lstclear(t_list **lst);

#endif
