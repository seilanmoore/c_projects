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

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*tmp;
	char	*prompt;
	char	*input;

	data = (t_data){0};
	data.envp = envp;
	data.argc = argc;
	data.argv = argv;
	data.user = getenv("USER");
	data.cwd = getcwd(NULL, 0);
	prompt = ft_strjoin(data.user, ": ");
	tmp = ft_strjoin(prompt, data.cwd);
	free(prompt);
	free(data.cwd);
	prompt = ft_strjoin(tmp, " $ ");
	free(tmp);
	input = readline(prompt);
	printf(GREEN "The previous input was: %s\n" RESET, input);
	free(input);
	rl_clear_history();
	clear_history();
	free(prompt);
	exit(EXIT_SUCCESS);
}
