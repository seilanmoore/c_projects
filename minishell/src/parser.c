/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/09/22 13:33:50 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	set_prev_token(t_data *data)
{
	t_tokens	*head;
	t_tokens	*prev;

	head = data->input.tokens;
	prev = head;
	if (!data->input.tokens)
		return ;
	data->input.tokens = data->input.tokens->next;
	while (data->input.tokens)
	{
		data->input.tokens->prev = prev;
		prev = data->input.tokens;
		data->input.tokens = data->input.tokens->next;
	}
	data->input.tokens = head;
}

static void	single_quote(t_data *data, t_var *var)
{
	var->aux1++;
	while (var->aux1[var->i] && var->aux1[var->i] != '\'')
		var->i++;
	if (var->aux1[var->i] && var->aux1[var->i] == '\'')
		var->aux = ft_substr(var->aux1, 0, var->i);
	var->i++;
	add_back_token(&(data->input.tokens), new_token(var->aux, QUOTE));
}

static void	double_quote(t_data *data, t_var *var)
{
	var->aux1++;
	while (var->aux1[var->i] &&
		(var->aux1[var->i] != '\"' ||
		(var->aux1[var->i] == '\"' && var->aux1[var->i - 1] == '\\')))
		var->i++;
	if (var->aux1[var->i] && var->aux1[var->i] == '\"')
		var->aux = ft_substr(var->aux1, 0, var->i);
	var->i++;
	add_back_token(&(data->input.tokens), new_token(var->aux, QUOTE));
}

static void	characters(t_data *data, t_var *var)
{
	while (var->aux1[var->i] &&
		var->aux1[var->i] != ' ' &&
		var->aux1[var->i] != '\'' &&
		var->aux1[var->i] != '\"' &&
		var->aux1[var->i] != '\n')
		var->i++;
	var->aux = ft_substr(var->aux1, 0, var->i);
	add_back_token(&(data->input.tokens), new_token(var->aux, -1));
	if (var->aux1[var->i] && var->aux1[var->i] == '\n')
		var->i++;
}

static void	parse_tokens(t_data *data)
{
	t_var	var;

	var = (t_var) {0};
	var.aux1 = data->input.raw_line;
	while (*var.aux1)
	{
		var.i = 0;
		var.aux = NULL;
		while (*var.aux1 && (*var.aux1 == ' ' || *var.aux1 == '\n'))
			var.aux1++;
		if (*var.aux1 && *var.aux1 == '\'')
			single_quote(data, &var);
		else if (*var.aux1 && *var.aux1 == '\"')
			double_quote(data, &var);
		else if (*var.aux1)
			characters(data, &var);
		var.aux1 = var.aux1 + var.i;
	}
	data->n_token = lst_size(data->input.tokens);
}

void	access_to_types(t_data *data, int target, int type)
{
	t_tokens	*head;
	int			i;

	head = data->input.tokens;
	i = -1;
	while(++i != target)
		data->input.tokens = data->input.tokens->next;
	if (data->input.tokens)
		data->input.tokens->type = type;
	data->input.tokens = head;
}

void	type_checks(t_data *data, t_tokens *ptr, int i)
{
	if (ptr->type != QUOTE && !ft_strncmp(ptr->token, ">>", 2))
			access_to_types(data, i, RIGHTT);
	else if (ptr->type != QUOTE && !ft_strncmp(ptr->token, "<<", 2))
		access_to_types(data, i, LEFTT);
	else if (ptr->prev && (ptr->prev->type == CMD || ptr->prev->type == OPTION) &&
		ptr->token[0] == '-' && ptr->type != QUOTE)
		access_to_types(data, i, OPTION);
	else if(ptr->prev && (ptr->prev->type == LEFT
	|| ptr->prev->type == RIGHT
	|| ptr->prev->type == RIGHTT))
		access_to_types(data, i, FILE);
	else if (ptr->prev && ptr->prev->type == LEFTT)
		access_to_types(data, i, HERE);
	else if (ptr->prev && (ptr->prev->type == CMD ||
		ptr->prev->type == OPTION))
		access_to_types(data, i, ARG);
	else if (ptr->type != QUOTE &&
		ptr->token[ft_strlen(ptr->token) - 1] == '=')
		access_to_types(data, i, VARIABLE);
	else if (ptr->prev && ptr->prev->type == VARIABLE)
		access_to_types(data, i, VALUE);
	else
		access_to_types(data, i, CMD);
}

void	assign_types(t_data	*data)
{
	t_tokens	*ptr;
	int			i;

	ptr = data->input.tokens;
	i = 0;
	while (ptr)
	{
		if (ft_strlen(ptr->token) == 1 && ptr->type != QUOTE &&
			(ptr->token[0] == '|' || ptr->token[0] == '<' ||
			ptr->token[0] == '>'))
		{
			if (ptr->token[0] == '|')
				access_to_types(data, i, PIPE);
			else if (ptr->token[0] == '<')
				access_to_types(data, i, LEFT);
			else if (ptr->token[0] == '>')
				access_to_types(data, i, RIGHT);
		}
		else
			type_checks(data, ptr, i);
		i++;
		ptr = ptr->next;
	}
}

char	*type_to_char(int type)
{
	if (type == 100)
		return ("CMD");
	if (type == 101)
		return ("OPTION");
	if (type == 102)
		return ("ARGUMENT");
	if (type == 103)
		return ("PIPE");
	if (type == 104)
		return ("<");
	if (type == 105)
		return (">");
	if (type == 106)
		return ("<<");
	if (type == 107)
		return (">>");
	if (type == 108)
		return ("QUOTE");
	if (type == 109)
		return ("FILE");
	if (type == 110)
		return ("HERE_DOC");
	if (type == 111)
		return ("VARIABLE");
	if (type == 112)
		return ("VALUE");
	return ("NO_TYPE");
}

void	print_types(t_data *data)
{
	t_tokens	*head;

	head = data->input.tokens;
	while (head)
	{
		printf("TOKEN: \"%s\"	TYPE: %s\n", head->token, type_to_char(head->type));
		head = head->next;
	}
}

void	parser(t_data *data)
{
	t_tokens	*ptr;

	parse_environment(data);
	get_env_paths(data);
	parse_tokens(data);
	set_prev_token(data);
	assign_types(data);
	print_types(data);
	ptr = data->input.tokens;
	if (ptr && !ft_strncmp(ptr->token, "env", ft_strlen(ptr->token)))
		env_builtin(data);
	if (ptr && !ft_strncmp(ptr->token, "exit", ft_strlen(ptr->token)))
		exit_builtin(data);
}
