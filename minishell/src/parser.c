/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/15 17:14:15 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parser(t_data *data)
{
	parse_environment(data);
	expand(data);
	tokenizer(data);
	locals(data);
	assign_opt_arg(data);
	data->exit_code = parse_cmd_opt(data);
	return (data->exit_code);
	//print_cmd_array(data);
	//print_types(data);
}
