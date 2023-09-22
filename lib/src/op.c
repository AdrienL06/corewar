/*
** EPITECH PROJECT, 2023
** asm
** File description:
** New version of op.c edited by Fowdre <virgile.legros@epitech.eu> and
** AdrienL06 <adrien.lachambre@epitech.eu>
** Original description:
** op.c for  korewar
** Made by Astek
** Login   <astek@epitech.net>
** Started on  Mon Mar 30 11:14:31 2009 Astek
** Last update Tue Mar 22 16:44:20 2011 Astek
*/

#include "op.h"
#include "vm.h"

/**
* @brief A table of instructions containing their mnemonic, number of arguments,
*  argument types, opcode, cycle duration, and description.
* @details Each element of the table represents an instruction, with the
*  mnemonic being a string, the number of arguments being an integer, the
*  argument types being a bitwise OR combination of the available argument
*  types (T_DIR, T_IND, T_REG), the opcode being an integer, the cycle duration
*  being an integer, and the description being a string. The last element of
*  the table has null values for all fields and serves as a sentinel value.
*/
op_t op_tab[] = {
    {"live", 1, {T_DIR}, 1, 10, NULL, "alive"},
    {"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, NULL,
        "load the content of the first parameter into the second parameter"},
    {"st", 2, {T_REG, T_IND | T_REG}, 3, 5, NULL,
        "store the content of the first parameter into the second parameter"},
    {"add", 3, {T_REG, T_REG, T_REG}, 4, 10, NULL,
        "add the contents of the first two parameters and store the result "
        "into the third"},
    {"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, NULL,
        "substract the contents of the first two parameters and store the "
        "result into the third"},
    {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
        NULL, "performs a binary and between the first two parameters and "
        "stores the result into the third | MODIFIES THE CARRY"},
    {"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
        NULL, "ou  (or   r1, r2, r3   r1 | r2 -> r3"},
    {"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
        NULL, "ou (xor  r1, r2, r3   r1^r2 -> r3"},
    {"zjmp", 1, {T_DIR}, 9, 20, NULL, "jump if zero"},
    {"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
        NULL, "load index"},
    {"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
        NULL, "store index"},
    {"fork", 1, {T_DIR}, 12, 800, NULL, "fork"},
    {"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, NULL, "long load"},
    {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
        NULL, "long load index"},
    {"lfork", 1, {T_DIR}, 15, 1000, NULL, "long fork"},
    {"aff", 1, {T_REG}, 16, 2, NULL, "aff"},
    {0, 0, {0}, 0, 0, 0, 0}
};
