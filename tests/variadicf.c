#include "/home/smoore-a/documents/mygit/libft/libft.h"
#include <stdarg.h>
#include <stdio.h>

static size_t	count_digit(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	va_list		ap_cpy;
	const char	*p;
	int			argn;

	va_start(ap, format);
	va_start(ap_cpy, format);
	p = format;
	argn = 0;
	while (*p)
	{
		if (*p != '%' || (*p == '%' && *(p + 1) == '0'))
			ft_putchar_fd(*p, 1);
		else if (ft_isdigit(*(p + 1)))
		{
			p++;
			argn = 0;
			while (p[argn] != '$')
				argn++;
			argn = ft_atoi(ft_substr(p, 0, argn));
			if (!argn)
				return (0);
			p += count_digit(argn) + 1;
			if (*p == 's')
			{
				while(argn-- > 1)
					va_arg(ap_cpy, char *);
				ft_putstr_fd(va_arg(ap_cpy, char *), 1);
			}
		}
		else if (*(p + 1) == 's')
		{
			ft_putstr_fd(va_arg(ap, char *), 1);
			p++;
		}
		p++;
		va_start(ap_cpy, format);
	}
	va_end(ap);
	va_end(ap_cpy);
	return (0);
}

int	main(void)
{
	ft_printf("Hola %10$s %s %0$s %3$sthrsht %6$s %8$s %7$s %9$s %1$s %4$s.\n", "1aaaaaa", "2", "3", "4", "5dddd", "6", "7", "8", "9", "10");
	printf("Hola %10$s %s %0$s %3$sthrsht %6$s %8$s %7$s %9$s %1$s %4$s.\n", "1aaaaaa", "2", "3", "4", "5dddd", "6", "7", "8", "9", "10");
	return (0);
}
