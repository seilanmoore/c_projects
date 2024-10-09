/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:39:54 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/07 09:10:26 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

int	is_built(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", len))
		return (1);
	if (!ft_strncmp(cmd, "cd", len))
		return (1);
	if (!ft_strncmp(cmd, "pwd", len))
		return (1);
	if (!ft_strncmp(cmd, "export", len))
		return (1);
	if (!ft_strncmp(cmd, "unset", len))
		return (1);
	if (!ft_strncmp(cmd, "env", len))
		return (1);
	if (!ft_strncmp(cmd, "exit", len))
		return (1);
	return (0);
}

static int	count_args(t_token *token)
{
	t_token	*tmp;
	int		n_args;

	n_args = 1;
	tmp = token->next;
	while (tmp && tmp->type == OPTION)
	{
		n_args++;
		tmp = tmp->next;
	}
	while (tmp && tmp->type == ARG)
	{
		n_args++;
		tmp = tmp->next;
	}
	return (n_args);
}

static char	*put_quotes(t_token *token)
{
	char	*arg;
	char	*tmp;

	arg = NULL;
	if (token->quote == S_QUOTE)
	{
		tmp = ft_strjoin("\'", token->token);
		arg = ft_strjoin(tmp, "\'");
		free(tmp);
	}
	else if (token->quote == D_QUOTE)
	{
		tmp = ft_strjoin("\"", token->token);
		arg = ft_strjoin(tmp, "\"");
		free(tmp);
	}
	return (arg);
}

static char	**args_no_cmd(t_token *token)
{
	t_token	*tmp;
	char	**args;
	int		n_args;
	int		i;

	tmp = token->next;
	n_args = count_args(token) - 1;
	args = ft_calloc(n_args + 1, sizeof(char *));
	if (!args)
		return (NULL);
	i = -1;
	while (++i < n_args)
	{
		args[i] = ft_strdup(tmp->token);
		if (!args[i])
			return (args);
		tmp = tmp->next;
	}
	return (args);
}

static char	**extract_args(t_token *token)
{
	t_token	*tmp;
	char	**args;
	int		n_args;
	int		i;

	tmp = token->next;
	n_args = count_args(token);
	args = ft_calloc(n_args + 1, sizeof(char *));
	if (!args)
		return (NULL);
	args[0] = ft_strdup(token->token);
	i = 0;
	while (++i < n_args)
	{
		if (tmp->quote == S_QUOTE || tmp->quote == D_QUOTE)
			args[i] = put_quotes(tmp);
		else
			args[i] = ft_strdup(tmp->token);
		if (!args[i])
			return (args);
		tmp = tmp->next;
	}
	return (args);
}

void	parse_cmd_opt(t_data *data)
{
	t_token	*tmp;
	char	**args;

	tmp = data->input.tokens;
	while (tmp)
	{
		if (tmp->token && tmp->type == CMD && !is_built(tmp->token))
		{
			args = extract_args(tmp);
			add_back_cmd(&(data->input.command), new_cmd(tmp->token, args, 0));
		}
		else if (tmp->token && tmp->type == CMD && is_built(tmp->token))
		{
			args = args_no_cmd(tmp);
			add_back_cmd(&(data->input.command), new_cmd(tmp->token, args, 1));
		}
		tmp = tmp->next;
	}
	assign_paths(data);
}
