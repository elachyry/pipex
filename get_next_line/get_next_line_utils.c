/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 08:53:00 by melachyr          #+#    #+#             */
/*   Updated: 2024/02/18 22:24:06 by melachyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*current;

	while (*lst != NULL)
	{
		current = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = current;
	}
}

int	ft_fetsh_new_line(t_list *lst)
{
	int	i;

	if (lst == NULL)
		return (0);
	while (lst != NULL)
	{
		i = 0;
		while (lst->content[i] != '\0')
		{
			if (lst->content[i] == '\n')
				return (1);
			i++;
		}
		lst = lst->next;
	}
	return (0);
}

int	ft_get_next_line_len(t_list *lst)
{
	int	i;
	int	len;

	len = 0;
	while (lst != NULL)
	{
		i = 0;
		while (lst->content[i] != '\0')
		{
			if (lst->content[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		lst = lst->next;
	}
	return (len);
}

void	ft_free_lst(t_list **lst, t_list *new_node, char *str)
{
	if (lst == NULL)
		return ;
	ft_lstclear(lst);
	if (new_node->content[0] != '\0')
		*lst = new_node;
	else
	{
		free(str);
		free(new_node);
	}
}
