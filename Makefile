NAME = ft_containers

CC = c++

STD = -std=c++98

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address 

HEADERS = 	containers/vector/ClassVector.hpp iterators/vector_iterator.hpp iterators/iterators_traits.hpp iterators/reverse_iterator.hpp \
			SFINAE/enable_if.hpp SFINAE/is_integral.hpp

RM = rm -f

all: $(NAME)

$(NAME): main.cpp containers/vector/ClassVector.hpp
	$(CC) $(FLAGS) main.cpp -o $(NAME)

fclean:
	$(RM) -f $(NAME)

re: fclean all