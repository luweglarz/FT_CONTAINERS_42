STD_MAP = std_map
FT_MAP = ft_map

STD_VECTOR = std_vector
FT_VECTOR = ft_vector

STD_STACK = std_stack
FT_STACK = ft_stack

CC = clang++

STD = -std=c++98 

FLAGS = -Wall -Wextra -Werror

HEADERS = 	containers/vector/ClassVector.hpp containers/stack/ClassStack.hpp \
			containers/map/ClassMap.hpp containers/map/utility/StructRBT.hpp \
			iterators/vector_iterator.hpp iterators/iterator_traits.hpp iterators/vector_reverse_iterator.hpp iterators/lexicographical_compare.hpp iterators/map_iterator.hpp \
			SFINAE/enable_if.hpp SFINAE/is_integral.hpp iterators/map_reverse_iterator.hpp\
			tests/tests.hpp

SRCS = 	tests/ft_map_main.cpp tests/std_map_main.cpp \
		tests/ft_vector_main.cpp std_vector_main.cpp \
		tests/ft_stack_main.cpp std_stack_main.cpp

RM = rm -f

all: $(FT_MAP) $(STD_MAP) $(FT_VECTOR) $(STD_VECTOR) $(FT_STACK) $(STD_STACK) $(HEADERS)
	
$(FT_MAP): tests/ft_map_main.cpp 
	$(CC) $(STD) $(FLAGS) tests/ft_map_main.cpp -o $(FT_MAP)
$(STD_MAP): tests/std_map_main.cpp 
	$(CC) $(STD) $(FLAGS) tests/std_map_main.cpp -o $(STD_MAP)

$(FT_VECTOR): tests/ft_vector_main.cpp 
	$(CC) $(STD) $(FLAGS) tests/ft_vector_main.cpp -o $(FT_VECTOR)
$(STD_VECTOR): tests/std_vector_main.cpp 
	$(CC) $(STD) $(FLAGS) tests/std_vector_main.cpp -o $(STD_VECTOR)

$(FT_STACK): tests/ft_stack_main.cpp 
	$(CC) $(STD) $(FLAGS) tests/ft_stack_main.cpp -o $(FT_STACK)
$(STD_STACK): tests/std_stack_main.cpp 
	$(CC) $(STD) $(FLAGS) tests/std_stack_main.cpp -o $(STD_STACK)

fclean:
	$(RM) $(STD_MAP)
	$(RM) $(FT_MAP)
	$(RM) $(STD_VECTOR)
	$(RM) $(FT_VECTOR)
	$(RM) $(STD_STACK)
	$(RM) $(FT_STACK)
	$(RM) $(OBJS)
	
re: fclean all