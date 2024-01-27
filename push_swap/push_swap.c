/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:22:59 by smoore-a          #+#    #+#             */
/*   Updated: 2024/01/27 16:22:00 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;	
}				t_list;

t_list	*ft_new_node(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

void ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

void	ft_lstprint(t_list *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		printf("[%s]\n", (char *)lst->content);
		lst = lst->next;
	}
}

int	ft_lstsize(t_list *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void ft_lstadd_back(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		if (*lst)
			ft_lstlast(*lst)->next = new;
		else
			*lst = new;
	}
}

void	del_node(void *node)
{
	free(node);
}

void	ft_delnode(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		(*del)(lst->content);
		free(lst);
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	while (ft_lstlast(*lst))
	{
		(*del)(ft_lstlast(*lst)->content);
		free(ft_lstlast(*lst));
	}
	*lst = NULL;
}

//sa (swap a): Swap the first 2 elements at the top of stack a.
//Do nothing if there is only one or no elements.
void swap_a(t_list **stack_a)
{
}

int	main(void)
{
	t_list	*list;
	int		i = 0;
	t_list		*elem;
	t_list		*elem2;
	t_list		*elem3;
	t_list		*elem4;
	char		**str;

	char	*str1 = strdup("lorem");
	char	*str2 = strdup("ipsum");
	char	*str3 = strdup("dolor");
	char	*str4 = strdup("sit");
	list = NULL;
 	printf("List\n");
	ft_lstprint(list);
	ft_lstadd_back(&list, ft_new_node(str1));
	ft_lstadd_back(&list, ft_new_node(str2));
	ft_lstadd_back(&list, ft_new_node(str3));
	ft_lstadd_back(&list, ft_new_node(str4));
	printf("List\n");
	ft_lstprint(list);
	ft_delnode(list, del_node);
	printf("List\n");
	ft_lstprint(list);
	return (0);
}
