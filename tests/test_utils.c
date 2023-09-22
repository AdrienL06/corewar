/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** test_utils
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "asm.h"
#include "vm.h"

static int arr_len(char **arr)
{
    int result = 0;
    
    for (; arr[result]; result++);
    return result;
}

static int test_main_asm(int argc, char **argv)
{
    asm_data_t *asm_data = init_asm_data();

    check_input_and_output_files(asm_data, argc, argv);
    asm_data->loaded_file = load_file(asm_data);
    clean_loaded_file(asm_data);
    fill_header_fields(asm_data);
    fill_instructions_field(asm_data);
    print_into_output_file(asm_data);
    exit_asm(asm_data, NULL, SUCCESS);
}

int run_asm(char **argv)
{
    pid_t child = fork();
    int exit_status;
    
    if (child == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (child == 0) {
        test_main_asm(arr_len(argv), argv);
        perror("execl");
        exit(EXIT_FAILURE);
    }
    else {
        waitpid(child, &exit_status, 0);
        if (WIFEXITED(exit_status))
            return WEXITSTATUS(exit_status);
        else
            return -1;
    }
}

static int test_main_asm_failure(int argc, char **argv)
{
    asm_data_t *asm_data = init_asm_data();

    check_input_and_output_files(asm_data, argc, argv);
    asm_data->loaded_file = load_file(asm_data);
    clean_loaded_file(asm_data);
    fill_header_fields(asm_data);
    fill_instructions_field(asm_data);
    free(asm_data->output_file_name);
    asm_data->output_file_name = NULL;
    print_into_output_file(asm_data);
    exit_asm(asm_data, NULL, SUCCESS);
}

int run_asm_failure(char **argv)
{
    pid_t child = fork();
    int exit_status;
    
    if (child == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (child == 0) {
        test_main_asm_failure(arr_len(argv), argv);
        perror("execl");
        exit(EXIT_FAILURE);
    }
    else {
        waitpid(child, &exit_status, 0);
        if (WIFEXITED(exit_status))
            return WEXITSTATUS(exit_status);
        else
            return -1;
    }
}

static int test_main_corewar(int argc, char **argv)
{
    vm_data_t *data = init_vm_data();

    parse_arguments(argc, argv, data);
    create_arena(data);
    start_vm(data);
    exit_vm(data, NULL, SUCCESS);
}

int run_corewar(char **argv)
{
    pid_t child = fork();
    int exit_status;
    
    if (child == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (child == 0) {
        test_main_corewar(arr_len(argv), argv);
        perror("execl");
        exit(EXIT_FAILURE);
    }
    else {
        waitpid(child, &exit_status, 0);
        if (WIFEXITED(exit_status))
            return WEXITSTATUS(exit_status);
        else if (WIFSIGNALED(exit_status)) {
            fprintf(stderr, "%s\n", strsignal(WTERMSIG(exit_status)));
            kill(getpid(), WTERMSIG(exit_status));
            return exit_status;
        } else
            return -1;
    }
}
