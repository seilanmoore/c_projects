/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 09:50:24 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/19 14:52:10 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

int		ft_printf(const char *arg, ...);
void	ft_conversion(char format, va_list ap);
void	ft_putpointer_fd(void *p, int fd);
char	*ft_uitoa(unsigned int n);
void	ft_puthex_fd(unsigned int n, int low_upper);

#endif