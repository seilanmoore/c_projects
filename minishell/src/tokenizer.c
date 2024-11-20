/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:21:13 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/10 20:45:08 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	single_quote(t_data *data, t_var *var)
{
	var->aux1++;
	if (*(var->aux1) == '\0' || *(var->aux1) == '\'')
	{
		if (*(var->aux1) == '\'')
			var->aux1++;
		return ;
	}
	while (var->aux1[var->i] && var->aux1[var->i] != '\'')
		var->i++;
	var->aux = ft_substr(var->aux1, 0, var->i);
	if (var->aux1[var->i])
		var->i++;
	if (end_space(var))
		add_back_token(\
			&(data->input.tokens), new_token(var->aux, 0, S_QUOTE, 1));
	else
		add_back_token(\
			&(data->input.tokens), new_token(var->aux, 0, S_QUOTE, 0));
}

static void	double_quote(t_data *data, t_var *var)
{
	var->aux1++;
	if (var->aux1[var->i] == '\0')
		return ;
	if (var->aux1[var->i] == '\"')
	{
		var->aux1++;
		return ;
	}
	while (var->aux1[var->i] && var->aux1[var->i] != '\"')
		var->i++;
	var->aux = ft_substr(var->aux1, 0, var->i);
	if (var->aux1[var->i])
		var->i++;
	if (end_space(var))
		add_back_token(\
			&(data->input.tokens), new_token(var->aux, 0, D_QUOTE, 1));
	else
		add_back_token(\
			&(data->input.tokens), new_token(var->aux, 0, D_QUOTE, 0));
}

void	handle_redir_char(t_data *data, t_var *var)
{
	if (var->aux1[var->i] == '<')
	{
		var->i++;
		if (var->aux1[var->i] && var->aux1[var->i] == '<')
			var->i++;
	}
	else if (var->aux1[var->i] == '>')
	{
		var->i++;
		if (var->aux1[var->i] && var->aux1[var->i] == '>')
			var->i++;
	}
	else if (var->aux1[var->i] == '|')
		var->i++;
	var->aux = ft_substr(var->aux1, 0, var->i);
	add_back_token(\
		&(data->input.tokens), new_token(var->aux, 0, NO_QUOTE, 1));
}

static void	characters(t_data *data, t_var *var)
{
	if (no_word(var->aux1[var->i]))
		return (handle_redir_char(data, var));
	while (var->aux1[var->i] && \
	!is_space(var->aux1[var->i]) && \
	var->aux1[var->i] != '\'' && \
	var->aux1[var->i] != '\"' && \
	var->aux1[var->i] != '|' && \
	var->aux1[var->i] != '<' && \
	var->aux1[var->i] != '>')
		var->i++;
	var->aux = ft_substr(var->aux1, 0, var->i);
	if (var->aux1[var->i] && \
	(var->aux1[var->i] == '|' || \
	var->aux1[var->i] == '<' || \
	var->aux1[var->i] == '>'))
		add_back_token(&(data->input.tokens), \
		new_token(var->aux, 0, NO_QUOTE, 1));
	else if (end_space(var))
		add_back_token(&(data->input.tokens), \
		new_token(var->aux, 0, NO_QUOTE, 1));
	else
		add_back_token(&(data->input.tokens), \
		new_token(var->aux, 0, NO_QUOTE, 0));
}

void	tokenizer(t_data *data)
{
	t_var	var;

	var = (t_var){0};
	var.aux1 = data->input.raw_line;
	while (*var.aux1)
	{
		var.i = 0;
		var.aux = NULL;
		while (is_space(*var.aux1))
			var.aux1++;
		if (*var.aux1 && *var.aux1 == '\'')
			single_quote(data, &var);
		else if (*var.aux1 && *var.aux1 == '\"')
			double_quote(data, &var);
		else if (*var.aux1)
			characters(data, &var);
		var.aux1 = var.aux1 + var.i;
	}
}
