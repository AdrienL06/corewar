/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** tests
*/

#ifndef TESTS_H_
    #define TESTS_H_

    #include "asm.h"

    destructor_t *init_asm_destructors(void);

    int run_asm(char **argv);
    int run_asm_failure(char **argv);

    int run_corewar(char **argv);

#endif /* !TESTS_H_ */
