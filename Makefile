NAME = ft_containers

LIB = tests.a

CC = c++

STD = -std=c++98

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address 

HEADERS = 	containers/vector/ClassVector.hpp iterators/vector_iterator.hpp iterators/iterator_traits.hpp iterators/reverse_iterator.hpp \
			SFINAE/enable_if.hpp SFINAE/is_integral.hpp tests/tests.hpp

SRCS = tests/iterator_tests.cpp tests/modifier_tests.cpp

OBJS = $(SRCS:.cpp=.o)

.cpp.o:
	$(CC) $(FLAGS) -c $< -o $@

RM = rm -f

all: $(NAME)

$(NAME): main.cpp $(HEADERS) $(OBJS)
	@ar rcs $(LIB) $(OBJS)
	@ranlib $(LIB)
	$(CC) $(FLAGS) main.cpp $(LIB) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:
	$(RM) $(NAME)
	$(RM) $(LIB)
	
re: fclean all