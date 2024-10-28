/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/10/28 12:14:12 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parser(t_data *data)
{
	envp_to_lst(data);
	expand(data);
	tokenizer(data);
	concatenate_tokens(data);
	assign_types(data);
	assign_opt_arg(data);
	parse_cmd_opt(data);
	//locals(data);
	//print_cmd_array(data);
	//print_types(data);
}
