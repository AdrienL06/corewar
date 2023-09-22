##
## EPITECH PROJECT, 2023
## asm
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
				src/linked_list/ll_functions.c								\
				src/linked_list/ll_asm_specific_functions.c					 \
				src/linked_list/asm_destructors.c							\
				src/init/init_handling.c									\
				src/parsing/args_handling.c									\
				src/parsing/file_handling.c									 \
				src/parsing/file_cleaning.c									 \
				src/parsing/pre_parsing.c									\
				src/header/header_parsing.c									\
				src/header/name_field.c										 \
				src/header/comment_field.c									 \
				src/instructions/instructions_parsing.c						\
				src/instructions/labels_parsing.c							\
				src/instructions/instruction_validation.c					\
				src/instructions/register/register_instructions.c			\
				src/instructions/direct/direct_instructions.c				\
				src/instructions/indirect/indirect_instructions.c			\
				src/instructions/create/instruction_create.c				\
				src/instructions/create/coding_byte.c						\
				src/instructions/create/total_bytes.c						\
				src/output/create_cor_file.c								 \
				src/free/free_handling.c									\

OBJ 		= 	$(patsubst src/%.c,obj/%.o,$(SRC))

NAME		=	asm

CFLAGS    +=    -Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wshadow 	\
			    -Wwrite-strings -Wredundant-decls -I./include -I../include \

ifeq ($(shell uname),Linux)
	CFLAGS += -Wlogical-op
endif

LIBS		=	../lib/lib.a 

MAKEFLAGS	+=	--no-print-directory

# ============================== [BASIC RULES] =============================== #

all:	$(NAME)

$(NAME):	$(OBJ)
	@gcc $(OBJ) $(LIBS) $(CFLAGS) -o $(NAME)
	$(call success_message, $(NAME))

clean:
	@find . -type f \( -iname "*~" \) -delete
	@find . -name "*.o" -delete -o -name "*.gcno" -delete -o -name "*.gcda"
	@$(RM) -f tests/unit_test
	@$(ECHO) $(PURPLE_C)$(DIM_T)"[clean]  "$(DEFAULT) $(BOLD_T)$(PURPLE_C)	\
		"DELETED: "$(DEFAULT) $(LIGHT_PURPLE)"$(NAME)'s unit_test"$(DEFAULT)
	@$(RM) -rf obj/
	@$(ECHO) $(PURPLE_C)$(DIM_T)"[clean]  "$(DEFAULT) $(BOLD_T)$(PURPLE_C)	\
		"DELETED: "$(DEFAULT) $(LIGHT_PURPLE)"$(NAME)'s object files"$(DEFAULT)
	@$(RM) vgcore.*
	@$(ECHO) $(PURPLE_C)$(DIM_T)"[clean]  "$(DEFAULT) $(BOLD_T)$(PURPLE_C)	\
		"DELETED: "$(DEFAULT) $(LIGHT_PURPLE)"$(NAME)'s valgrind files"		 \
	$(DEFAULT)

fclean:
	@$(RM) $(NAME)
	@$(RM) lib/lib.a
	@$(RM) -rf obj/
	@$(ECHO) $(PURPLE_C)$(DIM_T)"[fclean] "$(DEFAULT) $(BOLD_T)$(PURPLE_C)	\
		"DELETED: "$(DEFAULT) $(LIGHT_PURPLE)"$(NAME) binary"$(DEFAULT)

re:	fclean	all

# ============================== [UTILS RULES] =============================== #

lib:
	@make re -C ../lib/

obj/%.o:	src/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< && $(ECHO) $(BLUE_C)"[OK] "	\
	$(BOLD_T)"$<"$(DEFAULT) || ($(ECHO) $(PURPLE_C)[KO]$(BOLD_T)"$<"		\
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
	@gcc $(SRC) $(CFLAGS) -g3 -o $(NAME)
	$(call success_message, $(NAME))
	@make clean
	@valgrind -s --track-origins=yes --leak-check=full						\
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

checker	$(CHAMPION):	re
	@$(ECHO) $(BOLD_T)$(BLUE_C)"[⟳] RUNNING: "$(DEFAULT)$(LIGHT_BLUE)		\
	"asm checker\n"$(DEFAULT)

	@$(ECHO) $(BLUE_C)"1- "$(LIGHT_BLUE)"Executing mouli asm"$(DEFAULT);
	@./testing/asm .champions/$(CHAMPION) || (($(ECHO) $(PURPLE_C)"[✘] DIFF \
	FAILED: "$(LIGHT_PURPLE)"$(CHAMPION) champion file is invalid, error at	 \
	mouli asm"$(DEFAULT)); exit 1)

	@$(ECHO) $(BLUE_C)"2- "$(LIGHT_BLUE)"$(CHAMPION).cor created, renaming it\
	to $(CHAMPION)_mouli.cor"$(DEFAULT);
	@mv $(CHAMPION).cor $(CHAMPION)_mouli.cor

	@$(ECHO) $(BLUE_C)"3- "$(LIGHT_BLUE)"Moving $(CHAMPION)_mouli.cor into	\
	.tmp/ folder"$(DEFAULT);
	@mkdir -p ./.tmp
	@mv $(CHAMPION)_mouli.cor ./.tmp

	@$(ECHO) $(BLUE_C)"4- "$(LIGHT_BLUE)"Executing student's asm"$(DEFAULT);
	@./asm .champions/$(CHAMPION) || (($(ECHO) $(PURPLE_C)"[✘] DIFF FAILED: "\
	$(LIGHT_PURPLE)"$(CHAMPION) champion file is invalid, error at student's \
	asm"$(DEFAULT)); exit 1)

	@$(ECHO) $(BLUE_C)"5- "$(LIGHT_BLUE)"$(CHAMPION).cor created, renaming it \
	to $(CHAMPION)_student.cor"$(DEFAULT);
	@mv $(CHAMPION).cor $(CHAMPION)_student.cor

	@$(ECHO) $(BLUE_C)"6- "$(LIGHT_BLUE)"Moving $(CHAMPION)_student.cor into \
	.tmp/ folder"$(DEFAULT);
	@mv $(CHAMPION)_student.cor ./.tmp

	@$(ECHO) $(BLUE_C)"7- "$(LIGHT_BLUE)"Converting $(CHAMPION)_mouli.cor and \
	$(CHAMPION)_student.cor to hexadecimal files"$(DEFAULT);
	@hexdump -C -v ./.tmp/$(CHAMPION)_mouli.cor > 							\
	./.tmp/$(CHAMPION)_mouli.hex
	@hexdump -C -v ./.tmp/$(CHAMPION)_student.cor >							\
	./.tmp/$(CHAMPION)_student.hex

	@$(ECHO) $(BLUE_C)"6- "$(LIGHT_BLUE)"Executing diff on					\
	$(CHAMPION)_mouli.cor and $(CHAMPION)_student.cor"$(DEFAULT);
	@diff -u ./.tmp/$(CHAMPION)_mouli.hex ./.tmp/$(CHAMPION)_student.hex > \
	./.tmp/trace.diff || (($(ECHO) $(PURPLE_C)"[✘] DIFF FAILED: "		   \
	$(LIGHT_PURPLE)"$(CHAMPION) files differ"$(DEFAULT));					\
	code ./.tmp/trace.diff; exit 1)

CHAMPION	?=	Jon_Snow
COLS := $(shell tput cols)

.PHONY: all clean fclean re lib debug valgrind valgrind_plus g3only gprof \
		checker
