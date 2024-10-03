/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/03 13:36:16 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <string.h>
#include <time.h>

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
	//if (var->aux1[var->i] && var->aux1[var->i] == '\'')
	var->aux = ft_substr(var->aux1, 0, var->i);
	if (var->aux1[var->i])
		var->i++;
	add_back_token(&(data->input.tokens), new_token(var->aux, 0, S_QUOTE));
}

static void	double_quote(t_data *data, t_var *var)
{
	var->aux1++;
	while (var->aux1[var->i] && \
		(var->aux1[var->i] != '\"' || \
		(var->aux1[var->i] == '\"' && var->aux1[var->i - 1] == '\\')))
		var->i++;
	var->aux = ft_substr(var->aux1, 0, var->i);
	if (var->aux1[var->i])
		var->i++;
	add_back_token(&(data->input.tokens), new_token(var->aux, 0, D_QUOTE));
}

static void	characters(t_data *data, t_var *var)
{
	while (var->aux1[var->i] && \
		var->aux1[var->i] != ' ' && \
		var->aux1[var->i] != '=' && \
		var->aux1[var->i] != '\n')
		var->i++;
	if (var->aux1[var->i] == '=')
		var->i++;
	var->aux = ft_substr(var->aux1, 0, var->i);
	add_back_token(&(data->input.tokens), new_token(var->aux, 0, NO_QUOTE));
	if (var->aux1[var->i] && var->aux1[var->i] == '\n')
		var->i++;
}

static void	parse_tokens(t_data *data)
{
	t_var	var;

	var = (t_var){0};
	var.aux1 = data->input.raw_line;
	while (*var.aux1)
	{
		var.i = 0;
		var.aux = NULL;
		while (*var.aux1 && \
			(*var.aux1 == ' ' || *var.aux1 == '\t' || *var.aux1 == '\n'))
			var.aux1++;
		if (*var.aux1 && *var.aux1 == '\'' && *(var.aux1 + 1))
			single_quote(data, &var);
		else if (*var.aux1 && *var.aux1 == '\"' && *(var.aux1 + 1))
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
	while (++i != target)
		data->input.tokens = data->input.tokens->next;
	if (data->input.tokens)
		data->input.tokens->type = type;
	data->input.tokens = head;
}

int	check_redirections(t_data *data, t_tokens *ptr, int i)
{
	if (ptr->quote != NO_QUOTE)
		return (0);
	if (ft_strlen(ptr->token) == 1)
	{
		if (ptr->token[0] == '|')
			return (access_to_types(data, i, PIPE), 1);
		else if (ptr->token[0] == '<')
			return (access_to_types(data, i, LEFT), 1);
		else if (ptr->token[0] == '>')
			return (access_to_types(data, i, RIGHT), 1);
	}
	else if (ft_strlen(ptr->token) == 2)
	{
		if (!ft_strncmp(ptr->token, ">>", 2))
			return (access_to_types(data, i, RIGHTT), 1);
		else if (!ft_strncmp(ptr->token, "<<", 2))
			return (access_to_types(data, i, LEFTT), 1);
	}
	return (0);
}

int	check_files(t_data *data, t_tokens *ptr, int i)
{
	if (ptr->prev && \
		(ptr->prev->type == LEFT || \
		ptr->prev->type == RIGHT || \
		ptr->prev->type == RIGHTT))
		return (access_to_types(data, i, FILE), 1);
	return (0);
}

int	check_local_variables(t_data *data, t_tokens *ptr, int i)
{
	if (!ptr->prev && ptr->quote == NO_QUOTE && \
		ptr->token[ft_strlen(ptr->token) - 1] == '=')
		return (access_to_types(data, i, L_VARIABLE), 1);
	if (ptr->prev && ptr->prev->type == L_VARIABLE)
		return (access_to_types(data, i, L_VALUE), 1);
	return (0);
}

int	check_variables(t_data *data, t_tokens *ptr, int i)
{
	if (ptr->quote == NO_QUOTE && \
		ptr->token[ft_strlen(ptr->token) - 1] == '=')
		return (access_to_types(data, i, VARIABLE), 1);
	if (ptr->prev && ptr->prev->type == VARIABLE)
		return (access_to_types(data, i, VALUE), 1);
	return (0);
}

int	check_heredoc(t_data *data, t_tokens *ptr, int i)
{
	if (ptr->prev && ptr->prev->type == LEFTT)
		return (access_to_types(data, i, HERE), 1);
	return (0);
}

int	check_cmds(t_data *data, t_tokens *ptr, int i)
{
	if (ptr->prev)
	{
		if (ptr->quote == NO_QUOTE && \
			ptr->token[0] == '-' && \
			(ptr->prev->type == CMD || ptr->prev->type == OPTION))
			return (access_to_types(data, i, OPTION), 1);
		if (ptr->prev->type == CMD || \
			ptr->prev->type == OPTION || \
			ptr->prev->type == ARG)
			return (access_to_types(data, i, ARG), 1);
	}
	return (access_to_types(data, i, CMD), 1);
}

int	type_checks(t_data *data, t_tokens *ptr, int i)
{
	if (check_redirections(data, ptr, i))
		return (1);
	if (check_files(data, ptr, i))
		return (1);
	if (check_local_variables(data, ptr, i))
		return (1);
	if (check_variables(data, ptr, i))
		return (1);
	if (check_heredoc(data, ptr, i))
		return (1);
	return (check_cmds(data, ptr, i));
}

void	assign_types(t_data	*data)
{
	t_tokens	*ptr;
	int			i;

	ptr = data->input.tokens;
	i = 0;
	while (ptr)
	{
		type_checks(data, ptr, i);
		ptr = ptr->next;
		i++;
	}
}

void	remove_equal(t_data *data)
{
	t_tokens	*head;
	char		*tmp;

	if (!data->input.tokens)
		return ;
	head = data->input.tokens;
	while (data->input.tokens)
	{
		if (data->input.tokens->type == VARIABLE || \
			data->input.tokens->type == L_VARIABLE)
		{
			tmp = data->input.tokens->token;
			data->input.tokens->token = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
			free(tmp);
		}
		data->input.tokens = data->input.tokens->next;
	}
	data->input.tokens = head;
}

void	assign_opt_arg(t_data *data)
{
	t_tokens	*tmp;
	t_tokens	*aux;

	tmp = data->input.tokens;
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			aux = tmp->next;
			while (aux && \
			(aux->type == OPTION || aux->type == ARG))
			{
				if (aux->type == OPTION && !tmp->opt)
					tmp->opt = aux;
				else if (aux->type == ARG && !tmp->arg)
					tmp->arg = aux;
				aux = aux->next;
			}
		}
		tmp = tmp->next;
	}
}

int	parser(t_data *data)
{
	t_tokens	*ptr;

	parse_environment(data);
	get_env_paths(data);
	parse_tokens(data);
	set_prev_token(data);
	assign_types(data);
	remove_equal(data);
	add_l_variables(data);
	expand(data);
	assign_opt_arg(data);
	//print_types(data);
	ptr = data->input.tokens;
	if (ptr && !ft_strncmp(ptr->token, "env", ft_strlen(ptr->token)))
		data->exit_code = env_builtin(data);
	else if (ptr && !ft_strncmp(ptr->token, "pwd", ft_strlen(ptr->token)))
		data->exit_code = pwd_builtin(data);
	else if (ptr && !ft_strncmp(ptr->token, "echo", ft_strlen(ptr->token)))
		data->exit_code = echo_builtin(data, ptr, 1);
	else if (ptr && !ft_strncmp(ptr->token, "cd", ft_strlen(ptr->token)))
		data->exit_code = cd_builtin(data, ptr);
	else if (ptr && !ft_strncmp(ptr->token, "export", ft_strlen(ptr->token)))
		data->exit_code = export_builtin(data);
	else if (ptr && !ft_strncmp(ptr->token, "unset", ft_strlen(ptr->token)))
		data->exit_code = unset_builtin(data);
	else if (ptr && !ft_strncmp(ptr->token, "loc", ft_strlen(ptr->token)))
		print_locals(data);
	else if (ptr && !ft_strncmp(ptr->token, "exit", ft_strlen(ptr->token)))
		data->exit_code = exit_builtin(data);
	free(data->prev_exit_code);
	if (data->exit_code == -1)
		data->prev_exit_code = ft_strdup(MS "127: command not found" NL);
	else
		data->prev_exit_code = ft_itoa(data->exit_code);
	return (0);
}
