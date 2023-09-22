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
GREEN_C 	=	"\033[32m"
LIGHT_CYAN	=	"\033[96m"

# =============================== [CRITERION] ================================ #

SRC-CRIT	=	tests/test_asm.c										\
				tests/test_utils.c										\
				asm/src/linked_list/ll_functions.c						\
				asm/src/linked_list/ll_asm_specific_functions.c			\
				asm/src/linked_list/asm_destructors.c					\
				asm/src/init/init_handling.c							\
				asm/src/parsing/args_handling.c							\
				asm/src/parsing/file_handling.c							\
				asm/src/parsing/file_cleaning.c							\
				asm/src/parsing/pre_parsing.c							\
				asm/src/header/header_parsing.c							\
				asm/src/header/name_field.c								\
				asm/src/header/comment_field.c							\
				asm/src/instructions/instructions_parsing.c				\
				asm/src/instructions/labels_parsing.c					\
				asm/src/instructions/instruction_validation.c			\
				asm/src/instructions/register/register_instructions.c	\
				asm/src/instructions/direct/direct_instructions.c		\
				asm/src/instructions/indirect/indirect_instructions.c	\
				asm/src/instructions/create/instruction_create.c		\
				asm/src/instructions/create/coding_byte.c				\
				asm/src/instructions/create/total_bytes.c				\
				asm/src/output/create_cor_file.c						\
				asm/src/free/free_handling.c							\
				lib/src/op.c											\
				lib/src/calculate_len.c									\
            	lib/src/my_memset.c										\
            	lib/src/my_put_nbr.c									\
            	lib/src/my_strcat.c										\
            	lib/src/my_strcmp.c										\
            	lib/src/my_strcpy.c										\
            	lib/src/my_strdup.c										\
            	lib/src/my_strstr.c										\
            	lib/src/str_to_array.c									\
            	lib/src/my_atoi.c                                       \
            	lib/src/does_str_contain_only_chars.c                   \
				corewar/src/utils/op_utils.c							\
				corewar/src/utils/instruction_utils.c					\
				corewar/src/init/init_handling_vm.c						\
				corewar/src/free/free_handling_vm.c						\
				corewar/src/parsing/parse_arguments_vm.c				\
                corewar/src/parsing/fill_info.c							\
                corewar/src/cor_file_checker/loader.c					\
				corewar/src/cor_file_checker/loader_utils.c				\
				corewar/src/cor_file_checker/loader_utils_2.c			\
				corewar/src/arena/create_arena.c						\
				corewar/src/instruction/exec_instruction.c				\
				corewar/src/instruction/parse_instruction_arguments.c	\
				corewar/src/instruction/live.c							\
				corewar/src/instruction/ld.c							\
				corewar/src/instruction/st.c							\
				corewar/src/instruction/add.c							\
				corewar/src/instruction/sub.c							\
				corewar/src/instruction/and.c							\
				corewar/src/instruction/or.c							\
				corewar/src/instruction/xor.c							\
				corewar/src/instruction/zjmp.c							\
				corewar/src/instruction/aff.c							\
				corewar/src/instruction/ldi.c							\
				corewar/src/instruction/sti.c							\
				corewar/src/instruction/fork.c							\
				corewar/src/instruction/lfork.c							\
				corewar/src/instruction/lld.c							\
				corewar/src/instruction/lldi.c							\
				corewar/src/scheduler/scheduler.c						\
				corewar/src/scheduler/referee_checking.c				\
				tests/test_corewar.c									\

OBJ-CRIT	=	$(SRC-CRIT:.c=.o)

CRITFLAGS	=	-lcriterion --coverage -L/opt/homebrew/lib				\
				-I/opt/homebrew/Cellar/criterion/2.4.1_2/include/		\
				-I./asm/include -I./lib/include -I./tests/include/		\
				./lib/lib.a -I./include -I./corewar/include

CRITFILES	=	empty_lines_and_spaces.cor			\
				instruction_valid_label_at_end.cor	\
				instruction_valid_multiple.cor		\
				label_valid.cor						\
				label_valid_1.cor					\
				label_valid_2.cor					\
				no_extension_1s.cor					\
				no_extension.cor					\
				only_valid_name.cor					\


MAKEFLAGS	+=	--no-print-directory

# ============================== [BASIC RULES] =============================== #

all :
	@make -sC lib/ all
	@make -sC asm/ all
	@make -sC corewar/ all

clean :
	@rm -rf tests/gcovr/unit_tests*
	@rm -rf tests/html/coverage.*
	@make -sC lib/ clean
	@make -sC asm/ clean
	@make -sC corewar/ clean

fclean	:	clean
	@make -sC lib/ fclean
	@make -sC asm/ fclean
	@make -sC corewar/ fclean
	@$(RM) -rf doc/html/

re	:	fclean all

# ============================== [UTILS RULES] =============================== #

tests_run:	all
	@rm -rf tests/gcovr/unit_tests*
	@gcc -o tests/gcovr/unit_tests $(SRC-CRIT) $(CRITFLAGS) &&  \
		$(ECHO) $(BOLD_T)$(GREEN_C)"\n[✔] COMPILED: unit_tests"$(DEFAULT)  \
		$(LIGHT_GREEN)$(DEFAULT) || ($(ECHO) $(BOLD_T)					  \
		$(RED_C)"[✘] BUILD FAILED: unit_tests"$(LIGHT_RED)$(DEFAULT); exit 1)
	@./tests/gcovr/unit_tests --verbose
	@rm -rf $(CRITFILES)

gcovr-reload: tests_run
	@rm -rf tests/html/coverage.*
	@gcovr --exclude tests/ --html-details -o tests/html/coverage.html

gcovr: tests_run
	@rm -rf tests/html/coverage.*
	@gcovr --exclude tests/ --html-details -o tests/html/coverage.html \
	--gcov-ignore-parse-errors
	@firefox tests/html/coverage.html

doxygen	$(BROWSER):
	cd doc;						\
	doxygen doxyfile;			\
	$(BROWSER) html/index.html;	\
	cd -

doxygen-reload	$(BROWSER):
	cd doc;			\
	doxygen doxyfile;			\
	cd -
BROWSER	?=	firefox

GITIGNORE_FILES = *.o *.a *.log *.json *.vscode vgcore.* .idea/ *.txt		\
					$(NAME) .devcontainer/ .DS_Store .gitignore				\
					*.gcno *.gcda tests/unit_tests html/ coverage.*         \
					corewar/corewar asm/asm									\

gitignore:
	@$(ECHO) $(LIGHT_CYAN)$(BOLD_T)[DOING GITIGNORE]$(DEFAULT)$(GREEN_C);	\
	for file in $(GITIGNORE_FILES); do										\
	    $(ECHO) $$file; 													\
	done >> .gitignore;														\

.PHONY: all clean fclean re tests_run doxygen doxygen-reload gitignore
