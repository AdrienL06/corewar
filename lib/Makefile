##
## EPITECH PROJECT, 2022
## makefile
## File description:
## makefile of project
##




SRC        =src/calculate_len.c												\
            src/my_memset.c										    		\
            src/my_put_nbr.c												\
            src/my_strcat.c													\
            src/my_strcmp.c													\
            src/my_strcpy.c													\
            src/my_strdup.c													\
            src/my_strstr.c													\
            src/str_to_array.c												\
            src/my_atoi.c                                                   \
            src/does_str_contain_only_chars.c                               \
            src/op.c											            \

OBJ        =    $(SRC:src/%.c=obj/%.o)

NAME    =    lib.a

CFLAGS    +=    -Wall -Wextra -Wfloat-equal -Wundef -Wcast-align            \
			    -Wwrite-strings -Wredundant-decls -Wshadow -I./include     \
                -I../include -I../corewar/include -g                       \

ifeq ($(shell uname),Linux)
	CFLAGS += -Wlogical-op
endif

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

clean:
	@rm -rf obj

fclean: clean
	@rm -f $(NAME)

re: fclean all

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: all clean fclean re
