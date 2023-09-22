/*
** EPITECH PROJECT, 2023
** asm
** File description:
** main
*/

#include <sys/types.h>
#include "asm.h"

/**
 * @brief  The main function of the program, responsible for assembling a
 *         given input file into an output file.
 * @author Virgile Legros
 * @author Adrien Lachambre
 * @date   2023
 */
int main(int argc, char **argv)
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
