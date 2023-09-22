/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** Exec instructions
*/

#include "vm.h"
#include <stdio.h>

/**
 * @brief   Finds the opcode information for the given byte.
 * @details This function searches the opcode table for the opcode information
 *          that matches the given byte. It iterates through the table until it
 *          finds a matching opcode or reaches the end of the table. If a match
 *          is found, the corresponding opcode information is returned.
 * @param   byte    The byte representing the opcode.
 * @return  The opcode information if found, otherwise the last opcode in the
 *          table.
 */
op_t find_instruction(u_int8_t byte)
{
    int i = 0;

    for (; op_tab[i].code != 0; i++) {
        if (op_tab[i].code == byte)
            return op_tab[i];
    }
    return op_tab[i];
}

/**
 * @brief   Executes the current instruction for a process in the arena.
 * @details This function executes the current instruction for a process in the
 *          arena. It retrieves the opcode of the instruction at the process's
 *          current program counter (PC), parses the instruction arguments,
 *          checks their validity, and calls the corresponding execution
 *          function. If the instruction is not valid or has no execution
 *          function, the process's program counter is incremented and the
 *          function returns false.
 * @param   player  The process to execute the instruction for.
 * @param   arena   The arena containing the battlefield.
 * @return  True if the instruction was executed successfully, false otherwise.
 */
bool exec_instruction(pfork_t *player, arena_t *arena)
{
    instruction_arg_t args[3] = {0};
    op_t current_op;

    current_op = find_instruction(arena->battlefield[player->pc % MEM_SIZE]);
    if (current_op.exec) {
        parse_instruction_arguments(args, current_op, player->pc, arena);
        if (check_valid_args(current_op, args) == false) {
            player->pc++;
            return false;
        } else {
            player->pc += current_op.exec(arena, player, args);
        }
    } else {
        player->pc++;
        return false;
    }
    return true;
}
/*
printf("Executing instruction %s\n", current_op.mnemonique);
printf("At PC %d\n", player->pc);
printf("Args: \n");
for (int i = 0; i < 3; i++)
printf("Arg %d: type %d, data %ld\n", i, args[i].type, args[i].data);
*/
