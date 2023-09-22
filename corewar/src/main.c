/*
** EPITECH PROJECT, 2023
** virtual machine
** File description:
** main
*/

#include <unistd.h>
#include "vm.h"

/**
 * @brief   Main function of the program responsible for running the virtual
 *          machine.
 * @details This is the main entry point of the program. It is responsible for
 *          running the virtual machine by executing the necessary steps,
 *          including parsing command line arguments, creating the arena,
 *          starting the virtual machine, and exiting the virtual machine upon
 *          completion.
 * @author  Enzo Maltese
 * @author  Micka Daoud
 * @author  Virgile Legros
 * @author  Adrien Lachambre
 * @date    2023
 */
int main(int argc, char **argv)
{
    vm_data_t *data = init_vm_data();

    parse_arguments(argc, argv, data);
    create_arena(data);
    start_vm(data);
    exit_vm(data, NULL, SUCCESS);
}
