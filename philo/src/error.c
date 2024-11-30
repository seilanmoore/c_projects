/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 01:12:15 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/27 17:17:09 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	print_msg(char *msg, int code)
{
	int	len;

	len = ft_strlen(msg);
	write(2, msg, len);
	write(2, NL, 1);
	return (code);
}
