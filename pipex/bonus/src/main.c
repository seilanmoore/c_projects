/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 22:13:08 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/12 17:18:50 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	init(&data, argc, argv, envp);
	if (data.here_doc_exists)
		here_doc(&data);
	else
		not_here_doc(&data);
	cleanup(&data);
	exit(EXIT_SUCCESS);
}
