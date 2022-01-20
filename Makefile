NAME = ft_containers

LIB = tests.a

CC = c++

STD = -std=c++98 

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address

HEADERS = 	containers/vector/ClassVector.hpp iterators/vector_iterator.hpp iterators/iterator_traits.hpp iterators/reverse_iterator.hpp \
			SFINAE/enable_if.hpp SFINAE/is_integral.hpp tests/tests.hpp

SRCS = tests/iterator_tests.cpp tests/vector/modifier_tests.cpp tests/vector/capacity_tests.cpp tests/vector/element_access_tests.cpp \
		tests/vector/constructor_tests.cpp tests/stack/stack_tests.cpp tests/vector/non_members_functions.cpp

OBJS = $(SRCS:.cpp=.o)

RM = rm -f

all: $(NAME)
	
$(NAME): main.cpp $(HEADERS) $(OBJS)
	$(CC) $(STD) $(FLAGS) main.cpp $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:
	$(RM) $(NAME)
	$(RM) $(LIB)
	$(RM) $(OBJS)
	
re: fclean all