# Compiler and flags
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# Program name
NAME = megaphone

# Source files
SRC = megaphone.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Default target
all: $(NAME)

# Compile the program
$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

# Clean object files
clean:
	rm -f $(OBJ)

# Clean object files and executable
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

# Prevent make from getting confused by files named like targets
.PHONY: all clean fclean re
