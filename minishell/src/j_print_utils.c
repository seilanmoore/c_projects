/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_print_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:54:56 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/12 12:24:53 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_msg(t_data *data, char *msg, int status)
{
	ft_putendl_fd(msg, 2);
	data->status = status;
}

void	print_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
	{
		ft_putstr_fd(array[i], 2);
		if (array[i + 1])
			ft_putstr_fd(" ", 2);
	}
}

/* void	print_types(t_data *data)
{
	t_token	*head;
	t_token	*aux;

	head = data->input.tokens;
	while (head)
	{
		printf("TOKEN: \"%s\"	TYPE: %s(%d)	END_SPACE: %d\n", \
		head->token, type_to_char(head->type), head->type, head->end_space);
		aux = head->opt;
		if (aux)
			printf("\t--> OPTIONS:");
		while (aux && aux->type == OPTION)
		{
			printf(" %s", aux->token);
			aux = aux->next;
		}
		printf("\n");
		aux = head->arg;
		if (aux)
			printf("\t--> ARGS:");
		while (aux && aux->type == ARG)
		{
			printf(" %s", aux->token);
			aux = aux->next;
		}
		printf("\n");
		head = head->next;
	}
} */

void	print_cmd_array(t_data *data)
{
	t_cmd	*head;

	head = data->input.command;
	while (head)
	{
		printf("CMD_PATH: \"%s\" ARGUMENTS: ", head->cmd);
		print_array(head->args);
		printf("\n");
		head = head->next;
	}
}

//From locals.c
void	print_locals(t_data *data)
{
	t_env	*head;

	head = data->locals;
	while (data->locals)
	{
		printf("%s=%s\n", data->locals->variable, data->locals->value);
		data->locals = data->locals->next;
	}
	data->locals = head;
}
