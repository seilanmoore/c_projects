/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/07/22 19:45:58 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>

static void	count_token(t_data *data)
{
	char	**tmp;
	int		i;
	int		count;

	tmp = ft_split(data->input.raw_line, ' ');
	printf(RED "PARSE: ");
	i = -1;
	count = 0;
	while (tmp[++i])
		count++;
	free_mtrx(tmp);
	data->n_token = count;
}

void	one_letter_token(t_data *data)
{
	
}

void	assign_types(t_data	*data)
{
	int	i;

	i = -1;
	while (data->input.tokens[++i].token)
	{
		if (ft_strlen(data->input.tokens[i].token) == 1)
		{
			if (ft_strncmp(data->input.tokens[i].token, "|", 1))
				data->input.tokens[i].type = PIPE;
			else if (ft_strncmp(data->input.tokens[i].token, "<", 1))
				data->input.tokens[i].type = LEFT;
			else if (ft_strncmp(data->input.tokens[i].token, ">", 1))
				data->input.tokens[i].type = RIGHT;
		}
	}
}

void	assign_tokens(t_data *data)
{
	char	**tmp;
	int		n_tok;
	int		i;

	tmp = ft_split(data->input.raw_line, ' ');
	if (!tmp)
		return ;
	n_tok = data->n_token;
	i = -1;
	while (++i < n_tok)
	{
		data->input.tokens[i].token = ft_strdup(tmp[i]);
		if (!data->input.tokens[i].token)
			return ;
	}
	free_mtrx(tmp);
	// i = -1;
	// printf("TOKENS:\n");
	// while (data->input.tokens[++i].token)
	// 	printf("%s\n", data->input.tokens[i].token);
}

/*
void	command_checker(char *cmd)
{
	if (!ft_strchr(cmd, '/'))
	{

	}
} */

void	parse(t_data *data)
{
	get_env_paths(data);
	count_token(data);
	printf(GREEN "INPUT: %s" WHITE "\n" WHITE, data->input.raw_line);
	data->input.tokens = ft_calloc(data->n_token + 1, sizeof(t_tokens));
	if (!data->input.tokens)
		return ;
	assign_tokens(data);
	printf(WHITE "\n" WHITE);
}
