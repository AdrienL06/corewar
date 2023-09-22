/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** test_asm
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "tests.h"

// ================================ [special] =============================== //

Test(asm_special, help, .timeout=1.5, .init=cr_redirect_stdout)
{
    char *argv[] = {"./asm", "-h", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 0);
}

Test(asm_special, invalid_help_call, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "hh", NULL};
    int return_value = run_asm(argv);  
    cr_assert(return_value == 84);

    char *argv1[] = {"./asm", "-w", NULL};
    int return_value1 = run_asm(argv1);  
    cr_assert(return_value1 == 84);
}

Test(asm_special, not_enough_arguments, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 84);
}

Test(asm_special, too_many_arguments, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "arg1", "arg2", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 84);
}

Test(asm_special, only_slashes, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "/", NULL};
    int return_value = run_asm(argv);  
    cr_assert(return_value == 84);
}

Test(asm_special, no_extension, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/special/no_extension", NULL};
    int return_value = run_asm(argv);  
    cr_assert(return_value == 0);

    char *argv1[] = {"./asm", "tests/test_files/asm/special/no_extension_1s", NULL};
    int return_value1 = run_asm(argv1);  
    cr_assert(return_value1 == 0);
}

Test(asm_special, not_found, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/niko.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 84);
}

Test(asm_special, empty, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/special/empty.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 84);
}

Test(asm_special, empty_lines_and_spaces, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/special/empty_lines_and_spaces.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 0);
}

Test(asm_special, comment, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/special/comment.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 84);
}

Test(asm_special, linked_list, .timeout=1.5, .init=cr_redirect_stderr)
{
    ll_find_label(NULL, NULL);  

    linked_list_t *list_with_no_destructors = ll_init(NULL);
    ll_free(list_with_no_destructors);

    destructor_t *destructors = init_asm_destructors();
    linked_list_t *list_with_destructors = ll_init(destructors);
    ll_add_to_end(list_with_destructors, NULL, T_NONE);
    ll_free(list_with_destructors);
}

Test(asm_special, my_atoi, .timeout=1.5, .init=cr_redirect_stdout)
{
    char endptr = '\0';
    my_atoi("-2147483648", &endptr);
    my_atoi("-727", &endptr);
    my_atoi("\n", &endptr);
    my_atoi("/", &endptr);
    my_atoi("", &endptr);
    my_atoi(NULL, &endptr);
}

Test(asm_special, my_put_nbr, .timeout=1.5, .init=cr_redirect_stdout)
{
    my_put_nbr(727);
    my_put_nbr(-727);
    my_put_nbr(-2147483648);
}

Test(asm_special, my_strcat, .timeout=1.5, .init=cr_redirect_stdout)
{
    const char src[] = "niko";

    char dest[11] = "hello ";
    my_strcat(dest, src);

    char dest1[11] = "hello ";
    my_strncat(dest1, (char*)src, 5);

    char dest2[11] = "hello ";
    my_strncat(dest2, (char*)src, -1);

    char *dest3 = my_strcat_delim("niko", "pancakes", "cat");
    free(dest3);
}

Test(asm_special, my_strcmp, .timeout=1.5, .init=cr_redirect_stdout)
{
    my_strncmp("niko", "", 5);
    my_strncmp("niko", "pancakes", 1);
}

Test(asm_special, my_strcpy, .timeout=1.5, .init=cr_redirect_stdout)
{
    char dest[11] = "hello ";
    my_strcpy(dest, "niko");

    char dest1[11] = "hello ";
    my_strncpy(dest1, "niko", 4);

    char dest2[11] = "hello ";
    my_strncpy(dest2, "niko", 5);
}

Test(asm_special, my_strstr, .timeout=1.5, .init=cr_redirect_stdout)
{
    my_strstr("niko", NULL);
    my_strstr(NULL, "niko");
    my_strstr("niko", "");
    my_strstr("", "niko");
    my_strstr("pancakes niko", "niko");
}

// ================================= [name] ================================= //

Test(asm_name, only_valid_name, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/name/only_valid_name.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 0);
}

Test(asm_name, no_name, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/name/no_name.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 84);
}

Test(asm_name, empty_name, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/name/empty_name.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 84);
}

Test(asm_name, invalid_name, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/name/invalid_name.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 84);
}

Test(asm_name, too_long_name, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/name/too_long_name.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 84);
}

// ================================ [comment] =============================== //

Test(asm_comment, empty_comment, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/comment/empty_comment.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 84);
}

Test(asm_comment, invalid_comment, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/comment/invalid_comment.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 84);

    char *argv1[] = {"./asm", "tests/test_files/asm/comment/invalid_comment_1.s", NULL};
    int return_value1 = run_asm(argv1);
    cr_assert(return_value1 == 84);

    char *argv2[] = {"./asm", "tests/test_files/asm/comment/invalid_comment_2.s", NULL};
    int return_value2 = run_asm(argv2);
    cr_assert(return_value2 == 84);
}

Test(asm_comment, too_long_comment, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/comment/too_long_comment.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 84);
}

// ================================ [labels] ================================ //

Test(asm_labels, label_valid, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/labels/label_valid.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 0);

    char *argv1[] = {"./asm", "tests/test_files/asm/labels/label_valid_1.s", NULL};
    int return_value1 = run_asm(argv1);
    cr_assert(return_value1 == 0);

    char *argv2[] = {"./asm", "tests/test_files/asm/labels/label_valid_2.s", NULL};
    int return_value2 = run_asm(argv2);
    cr_assert(return_value2 == 0);
}

Test(asm_labels, label_already_defined, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/labels/label_already_defined.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 84);
}

Test(asm_labels, label_invalid, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/labels/label_invalid.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 84);

    char *argv1[] = {"./asm", "tests/test_files/asm/labels/label_invalid1.s", NULL};
    int return_value1 = run_asm(argv1);
    cr_assert(return_value1 == 84);
}

Test(asm_labels, label_not_found, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/labels/label_not_found.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 84);

    char *argv1[] = {"./asm", "tests/test_files/asm/labels/label_not_found_1.s", NULL};
    int return_value1 = run_asm(argv1);
    cr_assert(return_value1 == 84);
}

// ============================= [instructions] ============================= //

Test(asm_instructions, instruction_valid_multiple, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/instructions/instruction_valid_multiple.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 0);
}

Test(asm_instructions, instruction_valid_simple, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/instructions/instruction_valid_label_at_end.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 0);
}

Test(asm_instructions, instruction_invalid, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/instructions/instruction_invalid.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 84);
}

Test(asm_instructions, instruction_invalid_args_nbr, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/instructions/instruction_invalid_args_nbr.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 84);
}

Test(asm_instructions, instruction_invalid_args_type, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/instructions/instruction_invalid_args_type.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 84);

    char *argv1[] = {"./asm", "tests/test_files/asm/instructions/instruction_invalid_args_type_1.s", NULL};
    int return_value1 = run_asm(argv1);
    cr_assert(return_value1 == 84);
}

Test(asm_instructions, instruction_invalid_register_value, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/instructions/instruction_invalid_register_value.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 84);

    char *argv1[] = {"./asm", "tests/test_files/asm/instructions/instruction_invalid_register_value_1.s", NULL};
    int return_value1 = run_asm(argv1);
    cr_assert(return_value1 == 84);

    char *argv2[] = {"./asm", "tests/test_files/asm/instructions/instruction_invalid_register_value_2.s", NULL};
    int return_value2 = run_asm(argv2);
    cr_assert(return_value2 == 84);
}

Test(asm_instructions, instruction_invalid_direct_value, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/instructions/instruction_invalid_direct_value.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 84);
}

Test(asm_instructions, instruction_invalid_indirect_value, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/instructions/instruction_invalid_indirect_value.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 84);
}

// ================================ [output] ================================ //

Test(asm_output, unexpected_error, .timeout=1.5, .init=cr_redirect_stderr)
{
    char *argv[] = {"./asm", "tests/test_files/asm/output/unexpected_error.s", NULL};
    int return_value = run_asm_failure(argv);
    cr_assert(return_value == 84);
}

/*
Test(asm_output, , .timeout=1.5)
{
    char *argv[] = {"./asm", "tests/test_files/asm/output/.s", NULL};
    int return_value = run_asm(argv);
    cr_assert(return_value == 84);
}
*/
