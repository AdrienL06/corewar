/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** Utils
*/

#include "vm.h"

/**
 * @brief   Checks if an instruction has a coding byte.
 * @details This function checks if the specified instruction mnemonic
 *          corresponds to an instruction that requires a coding byte. It
 *          compares the mnemonic against a list of instructions known not to
 *          have a coding byte.
 * @param   mnemonique The mnemonic of the instruction.
 * @return  true if the instruction has a coding byte, false otherwise.
 */
bool has_coding_byte_vm(const char *mnemonique)
{
    const char *no_coding_byte[] = {"zjmp", "live", "fork", "lfork", NULL};

    for (int i = 0; no_coding_byte[i]; i++)
        if (my_strcmp(no_coding_byte[i], mnemonique) == 0)
            return false;
    return true;
}

/**
 * @brief   Checks if an instruction has index addressing mode.
 * @details This function checks if the specified instruction mnemonic
 *          corresponds to an instruction that uses index addressing mode. It
 *          compares the mnemonic against a list of instructions known to have
 *          index addressing mode.
 * @param   mnemonique The mnemonic of the instruction.
 * @return  true if the instruction has index addressing mode, false otherwise.
 */
bool has_index_vm(const char *mnemonique)
{
    const char *index[] = {"zjmp", "ldi", "sti", "fork", "lldi", "lfork", NULL};

    for (int i = 0; index[i]; i++)
        if (my_strcmp(index[i], mnemonique) == 0)
            return true;
    return false;
}

/**
 * @brief   Checks if the arguments of an instruction are valid.
 * @details This function checks if the arguments of an instruction are valid
 *          based on the specified opcode and the argument types.
 *          It iterates through each argument and verifies if its type matches
 *          the expected type defined by the opcode.
 * @param   op   The opcode of the instruction.
 * @param   args An array of instruction_arg_t representing the arguments.
 * @return  true if all arguments are valid, false otherwise.
*/
bool check_valid_args(op_t op, instruction_arg_t *args)
{
    for (int i = 0; i < op.nbr_args; i++)
        if (!(args[i].type & op.type[i]))
            return false;
    return true;
}

/**
 * @brief   Retrieves the value of an argument from the process or arena's data.
 * @details This function retrieves the value of an argument from the context
 *          of a process or the arena's data. The value is determined based on
 *          the type of the argument:
 *          - If the argument is a register, the value is retrieved from the
 *          process's registers.
 *          - If the argument is a direct value, the value is returned as is.
 *          - If the argument is a memory location, the value is retrieved from
 *          the arena's battlefield based on the index value specified in the
 *          argument and the process's program counter (PC).
 * @param   args   The argument to retrieve the value from.
 * @param   player The process from which to retrieve the value.
 * @param   arena  The arena containing the battlefield.
 * @return  The retrieved value of the argument.
 */
int64_t get_argument_value(instruction_arg_t *args, pfork_t *player,
                            arena_t *arena)
{
    if (args->type & T_REG)
        return player->registers[args->data - 1];
    if (args->type & T_DIR)
        return args->data;
    else {
        if (args->idx_mod)
            return arena->battlefield
                [((args->data + player->pc) % IDX_MOD) % MEM_SIZE];
        else
            return arena->battlefield[(args->data + player->pc) % MEM_SIZE];
    }
    return 0;
}

/**
 * @brief   Sets the value of an argument in the process or arena's battlefield.
 * @details This function handles setting the value of an argument in the
 *          context of a process or the arena's battlefield. If the argument is
 *          a register, the value is set in the process's register. If the
 *          argument is a memory location, the value is set in the arena's
 *          battlefield. The memory location is determined based on the index
 *          value specified in the argument and the process's program counter
 *          (PC).
 * @param   args   The argument to set the value for.
 * @param   player The process in which to set the value.
 * @param   arena  The arena containing the battlefield.
 * @param   value  The value to set.
 */
void set_argument_value(instruction_arg_t *args, pfork_t *player,
                        arena_t *arena, reg_t value)
{
    int64_t index = 0;

    if (args->type & T_REG) {
        player->registers[args->data - 1] = value;
        return;
    }
    if (args->idx_mod)
        index = (args->data % IDX_MOD) + player->pc;
    else
        index = args->data + player->pc;
    for (size_t i = 0; i < sizeof(reg_t); i++) {
        arena->battlefield[(index + i) % MEM_SIZE] =
            (value >> (8 * (sizeof(reg_t) - i - 1))) & 0xFF;
    }
}
