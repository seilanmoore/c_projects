/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/11 14:04:09 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parser(t_data *data)
{
	parse_environment(data);
	tokenizer(data);
	add_l_variables(data);
	expand(data);
	assign_opt_arg(data);
	parse_cmd_opt(data);
	//print_cmd_array(data);
	// print_types(data);
	// exit (0);
}
