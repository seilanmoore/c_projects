#include <iostream>

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return 0;
	}
	argv++;
	while (*argv)
	{
		while (**argv)
		{
			std::cout << static_cast<char>(std::toupper(**argv));
			(*argv)++;
		}
		argv++;
	}
	std::cout << std::endl;
	return 0;
}

