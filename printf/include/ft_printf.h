/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 09:50:24 by smoore-a          #+#    #+#             */
/*   Updated: 2023/12/19 21:50:39 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "./libft.h"

int		ft_printf(const char *arg, ...);
void	ft_conversion(char format, va_list ap, int *count);
int		ft_hex_address(size_t address);
int		ft_uitoa(unsigned int n);
int		ft_puthex_fd(unsigned int n, int low_upper);

#endif