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
PURPLE_C   	=	"\033[38;2;119;0;173m"# rgb(119, 0, 173)
BLUE_C 		=	"\033[38;2;131;187;251m"# rgb(131, 187, 251)
LIGHT_PURPLE=	"\033[38;2;157;0;230m"# rgb(157, 0, 230)
LIGHT_BLUE	=	"\033[38;2;185;217;253m"# rgb(185, 217, 253)

define success_message
	@$(ECHO) $(BOLD_T)$(BLUE_C)"\n[✔] COMPILED:"$(DEFAULT)$(LIGHT_BLUE)\
	"$(1)\n"$(DEFAULT) || $(ECHO) $(BOLD_T)$(PURPLE_C)"[✘]				\
		"$(UNDLN_T)"BUILD FAILED:" $(LIGHT_PURPLE) "$(1)\n"$(DEFAULT)
endef

define fail_message
	$(ECHO) $(BOLD_T)$(PURPLE_C)"[✘] BUILD FAILED:" \
	$(LIGHT_PURPLE) "$(1)\n"$(DEFAULT)
endef

# ================================ [PROJECT] ================================= #

SRC 		= 	src/main.c													\
				src/utils/op_utils.c										\
				src/utils/instruction_utils.c								\
				src/init/init_handling.c									\
				src/free/free_handling.c									\
				src/parsing/parse_arguments.c								\
                src/parsing/fill_info.c										\
                src/cor_file_checker/loader.c								\
				src/cor_file_checker/loader_utils.c							\
				src/cor_file_checker/loader_utils_2.c						\
				src/arena/create_arena.c									\
				src/instruction/exec_instruction.c							\
				src/instruction/parse_arguments.c							\
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
				src/ncurses_utils/nutils.c									\
				src/ncurses_utils/nevents.c									\

OBJ 		= 	$(patsubst src/%.c,obj/%.o,$(SRC))

NAME		=	visualizer

CFLAGS    +=    -Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wshadow 	\
			    -Wredundant-decls -I./include -I../include \

ifeq ($(shell uname),Darwin)
	CFLAGS += -I/opt/homebrew/opt/ncurses/include
endif

ifeq ($(shell uname),Linux)
	CFLAGS += -Wlogical-op
endif

LIBS		=	../lib/lib.a 

LNCURSES	=	-lncurses

MAKEFLAGS	+=	--no-print-directory

# ============================== [BASIC RULES] =============================== #

all:	$(NAME)

$(NAME):	$(OBJ)
	@make -sC ../lib/ all
	@gcc $(OBJ) $(LIBS) $(CFLAGS) $(LNCURSES) -o $(NAME)
	$(call success_message, $(NAME))

clean:
	@make -sC ../lib/ clean
	@find . -type f \( -iname "*~" \) -delete
	@find . -name "*.o" -delete -o -name "*.gcno" -delete -o -name "*.gcda"
	@$(RM) -f tests/unit_test
	@$(ECHO) $(PURPLE_C)$(DIM_T)"[clean]  "$(DEFAULT) $(BOLD_T)$(PURPLE_C)	\
		"DELETED: "$(DEFAULT) $(LIGHT_PURPLE)"$(NAME)'s unit_test"$(DEFAULT)
	@$(RM) -rf obj/
	@$(ECHO) $(PURPLE_C)$(DIM_T)"[clean]  "$(DEFAULT) $(BOLD_T)$(PURPLE_C)	\
		"DELETED: "$(DEFAULT) $(LIGHT_PURPLE)"$(NAME)'s object files"$(DEFAULT)
	@$(RM) vgcore.*
	@$(ECHO) $(PURPLE_C)$(DIM_T)"[clean]  "$(DEFAULT) $(BOLD_T)$(PURPLE_C)\
		"DELETED: "$(DEFAULT) $(LIGHT_PURPLE)"$(NAME)'s valgrind files"\
	$(DEFAULT)

fclean:
	@make -sC ../lib/ fclean
	@$(RM) $(NAME)
	@$(RM) lib/lib.a
	@$(RM) -rf obj/
	@$(ECHO) $(PURPLE_C)$(DIM_T)"[fclean] "$(DEFAULT) $(BOLD_T)$(PURPLE_C)	\
		"DELETED: "$(DEFAULT) $(LIGHT_PURPLE)"$(NAME) binary"$(DEFAULT)

re:	fclean	all

# ============================== [UTILS RULES] =============================== #

lib:
	@make -C ../lib/

obj/%.o:	src/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< && $(ECHO) $(BLUE_C)"[OK] "\
	$(BOLD_T)"$<"$(DEFAULT) || ($(ECHO) $(PURPLE_C)[KO]$(BOLD_T)"$<"\
	$(DEFAULT); $(call fail_message, $(NAME)); exit 1)

# ============================ [DEBUGGING RULES] ============================= #

debug:
	@gcc $(SRC) $(CFLAGS) -g -o $(NAME)
	$(call success_message, $(NAME))

valgrind:
	@gcc $(SRC) $(CFLAGS) -g3 -o $(NAME)
	$(call success_message, $(NAME))
	@make clean
	@valgrind -s --track-origins=yes ./$(NAME) $(ARGS)

valgrind_plus	$(KINDS):
	@echo "KINDS= all | definite | indirect | possible | reachable"
	@gcc $(SRC) $(CFLAGS) $(LIBS) -g3 -o $(NAME)
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
	@$(ECHO) $(BLUE_C)"\nRunning gprof" $(DEFAULT)
	@gcc $(SRC) -o $(NAME) $(CFLAGS) -pg
	$(call success_message, $(NAME))
	@./$(NAME) $(ARGS)
	@make clean
	@gprof -b -p $(NAME)

.PHONY: all clean fclean re lib debug valgrind valgrind_plus g3only gprof
