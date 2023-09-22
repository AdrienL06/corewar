##
## EPITECH PROJECT, 2023
## B-CPE-200-NCE-2-1-corewar-virgile.legros
## File description:
## Makefile | Originally created by Adrien LACHAMBRE | Edited by Virgile LEGROS
##

# ================================= [SETUP] ================================== #

ifeq ($(shell uname),Linux)
    ECHO := echo -e
else ifeq ($(OS),Windows_NT)
    ECHO := echo.
else
    ECHO := echo
endif

DEFAULT 	=	"\033[0m"
BOLD_T  	=	"\033[1m"
DIM_T   	=	"\033[2m"
RED_C		=	"\033[38;2;102;9;0m" # 102 9 0
GOLD_C 		=	"\033[38;2;230;175;21m" # 230 175 21
LIGHT_RED	=	"\033[38;2;168;15;1m" # 168 15 1
LIGHT_GOLD	=	"\033[38;2;250;242;94m" # 250 242 94

define success_message
	@$(ECHO) $(BOLD_T)$(GOLD_C)"\n[✔] COMPILED:"$(DEFAULT)$(LIGHT_GOLD)\
	"$(1)\n"$(DEFAULT) || $(ECHO)$(BOLD_T)$(RED_C)"[✘]				   	\
		"$(UNDLN_T)"BUILD FAILED:" $(LIGHT_RED)"$(1)\n"$(DEFAULT)
endef

define fail_message
	$(ECHO) $(BOLD_T)$(RED_C)"[✘] BUILD FAILED:"$(LIGHT_RED) "$(1)\n"$(DEFAULT)
endef

# ================================ [PROJECT] ================================= #

SRC 		= 	src/main.c													\
				src/utils/op_utils.c										\
				src/utils/instruction_utils.c								\
				src/init/init_handling_vm.c									\
				src/free/free_handling_vm.c									\
				src/parsing/parse_arguments_vm.c							\
                src/parsing/fill_info.c										 \
                src/cor_file_checker/loader.c								 \
				src/cor_file_checker/loader_utils.c							 \
				src/cor_file_checker/loader_utils_2.c						 \
				src/arena/create_arena.c									\
				src/instruction/exec_instruction.c							\
				src/instruction/parse_instruction_arguments.c				\
				src/instruction/live.c										\
				src/instruction/ld.c										\
				src/instruction/st.c										\
				src/instruction/add.c										\
				src/instruction/sub.c										\
				src/instruction/and.c										\
				src/instruction/or.c										\
				src/instruction/xor.c										\
				src/instruction/zjmp.c										\
				src/instruction/aff.c										\
				src/instruction/ldi.c										\
				src/instruction/sti.c										\
				src/instruction/fork.c										\
				src/instruction/lfork.c										\
				src/instruction/lld.c										\
				src/instruction/lldi.c										\
				src/scheduler/scheduler.c									\
				src/scheduler/referee_checking.c							\

OBJ 		= 	$(patsubst src/%.c,obj/%.o,$(SRC))

NAME		=	corewar

CFLAGS  	+=	-Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wshadow	 \
				-Wredundant-decls -I./include -I../include				    \

ifeq ($(shell uname),Linux)
	CFLAGS += -Wlogical-op
endif

LIBS		=	../lib/lib.a 

MAKEFLAGS	+=	--no-print-directory

# ============================== [BASIC RULES] =============================== #

all:	$(NAME)

$(NAME):	$(OBJ)
	@gcc $(OBJ) $(LIBS) -o $(NAME) $(CFLAGS)
	$(call success_message, $(NAME))

clean:
	@find . -type f \( -iname "*~" \) -delete
	@find . -name "*.o" -delete -o -name "*.gcno" -delete -o -name "*.gcda"
	@$(RM) -f tests/unit_test
	@$(ECHO) $(RED_C)$(DIM_T)"[clean]  "$(DEFAULT) $(BOLD_T)$(RED_C)		\
		"DELETED: "$(DEFAULT) $(LIGHT_RED)"$(NAME)'s unit_test"$(DEFAULT)
	@$(RM) -rf obj/
	@$(ECHO) $(RED_C)$(DIM_T)"[clean]  "$(DEFAULT) $(BOLD_T)$(RED_C)		\
		"DELETED: "$(DEFAULT) $(LIGHT_RED)"$(NAME)'s object files"$(DEFAULT)
	@$(RM) vgcore.*
	@$(ECHO) $(RED_C)$(DIM_T)"[clean]  "$(DEFAULT) $(BOLD_T)$(RED_C)		\
		"DELETED: "$(DEFAULT) $(LIGHT_RED)"$(NAME)'s valgrind files"$(DEFAULT)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) -rf obj/
	@$(ECHO) $(RED_C)$(DIM_T)"[fclean] "$(DEFAULT) $(BOLD_T)$(RED_C)		\
		"DELETED: "$(DEFAULT) $(LIGHT_RED)"$(NAME) binary"$(DEFAULT)

re:	fclean	all

# ============================== [UTILS RULES] =============================== #

lib:
	@make re -C ../lib/

obj/%.o:	src/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< && $(ECHO) $(GOLD_C)"[OK]" \
		$(BOLD_T)"$<"$(DEFAULT) || ($(ECHO) $(RED_C)[KO]$(BOLD_T)"$<"$(DEFAULT)\
		; $(call fail_message, $(NAME)); exit 1)

# ============================ [DEBUGGING RULES] ============================= #

debug:
	@gcc $(SRC) -o $(NAME) $(CFLAGS) -g
	$(call success_message, $(NAME))

valgrind:
	@gcc $(SRC) -o $(NAME) $(CFLAGS) -g3
	$(call success_message, $(NAME))
	@make clean
	@valgrind -s --track-origins=yes ./$(NAME) $(ARGS)

valgrind_plus	$(KINDS):
	@echo "KINDS= all | definite | indirect | possible | reachable"
	@gcc $(SRC) -o $(NAME) $(CFLAGS) -g3
	$(call success_message, $(NAME))
	@make clean
	@valgrind -s --track-origins=yes --leak-check=full \
	--show-leak-kinds=$(KINDS) ./$(NAME) $(ARGS)
KINDS	?=	all

g3only:
	@gcc $(SRC) -o $(NAME) $(CFLAGS) -g3
	$(call success_message, $(NAME))
	@make clean

gprof	$(ARGS):
	@$(ECHO) $(GOLD_C)"\nRunning gprof" $(DEFAULT)
	@gcc $(SRC) -o $(NAME) $(CFLAGS) -pg
	$(call success_message, $(NAME))
	@./$(NAME) $(ARGS)
	@make clean
	@gprof -b -p $(NAME)

.PHONY: all clean fclean re lib debug valgrind valgrind_plus g3only gprof
