/*
** EPITECH PROJECT, 2023
** virtual machine
** File description:
** header
*/

#ifndef VM_H_
    #define VM_H_

// =============================== [INCLUDES] =============================== //

    #include "../../lib/include/lib.h"
    #include <stdio.h>
    #include "op_bonus.h"
    #include "bonus.h"

// =============================== [DEFINES] ================================ //

    #define __SEMICOLON ;
    #define __S __SEMICOLON
    #define __RED "\033[38;2;168;15;1m"
    #define __GOLD "\033[38;2;230;175;21m"
    #define __RESET "\033[0m"
    #define __W_RED(stream) fwrite(__RED, sizeof(char), 16, stream)
    #define __W_GOLD(stream) fwrite(__GOLD, sizeof(char), 18, stream)
    #define __W_DEFAULT(stream) fwrite(__RESET, sizeof(char), 4, stream)
    #define ERROR_WRITE(ptr, n) __W_RED(stderr)__S \
        fwrite(ptr, sizeof(char), n, stderr)__S \
        __W_DEFAULT(stderr)__S
    #define USAGE "USAGE\n./corewar [-dump nbr_cycle] [[-n prog_number] "\
            "[-a load_address] prog_name] ...\n", 85
    #define DUMP_USAGE "-dump nbr_cycle dumps the memory after the nbr_cycle "\
            "execution (if the round isn’t already over) with the following "\
            "format: 32 bytes/line in hexadecimal (A0BCDEFE1DD3...)\n", 174
    #define PROG_NUMBER_USAGE "-n prog_number sets the next program’s number. "\
            "By default, the first free number in the parameter order\n", 107
    #define LOAD_ADDR_USAGE "-a load_address sets the next program’s loading "\
            "address. When no address is specified, optimize the addresses so "\
            "that the processes are as far away from each other as possible. "\
            "The addresses are MEM_SIZE modulo.\n", 215
    #define FAILURE 84
    #define SUCCESS 0
    #define PARSING_DEFAULT_VALUE -1
    #define PARSING_ERROR_VALUE -2147483648
    #define MAX_PLAYERS 4
    #define PROG_SIZE_POS sizeof(int) + PROG_NAME_LENGTH + 1

// ============================== [STRUCTURES] ============================== //

    typedef struct referee_s {
        bool players_alive[MAX_PLAYERS];
        int cycle_to_die;
        int nb_of_live_call;
        int last_live_call;
    } referee_t;

    typedef struct fn_args_init_player_s {
        int nbr_player;
        int n;
        int a;
    } fn_args_init_player_t;

    typedef struct temp_player_s {
        int prog_nbr;
        char *filename;
        int load_address;
    } temp_player_t;

    typedef struct command_line_info_s {
        int nbr_player;
        int dump_nbr_cycle;
        temp_player_t tmp_players[4];
        bool availaible_prog_nbr[4];
    } command_line_info_t;

    typedef struct cor_file_s {
        char *name;
        int size;
        u_int8_t *bytes;
        int pc;
    } cor_file_t;

    typedef struct pfork_s {
        char *player_name;
        int8_t *color;
        reg_t registers[16];
        int pc;
        bool carry;
        int cooldown;
        struct pfork_s *next;
    } pfork_t;

    typedef struct player_s {
        char player_name[PROG_NAME_LENGTH + 1];
        int8_t color;
        pfork_t *forks;
        bool send_live_sig;
    } player_t;

    typedef struct arena_s {
        u_int8_t battlefield[MEM_SIZE];
        int8_t nattr[MEM_SIZE];
        player_t *players[MAX_PLAYERS];
        referee_t* referee;
    } arena_t;

    typedef struct vm_data_s {
        ncurses_data_t *ndata;
        command_line_info_t *cmd_line_info;
        cor_file_t *cor_files[MAX_PLAYERS];
        arena_t *arena;
    } vm_data_t;

    typedef struct instruction_arg_s {
        int64_t data;
        args_type_t type;
        bool idx_mod;
    } instruction_arg_t;


// ============================= [DECLARATIONS] ============================= //

    vm_data_t *init_vm_data(void);
    void init_temp_player(vm_data_t *info, char *filename,
        fn_args_init_player_t args);

    int display_file_error(char *filename, const char *str1, const char *str2,
        int return_value);
    void exit_vm(vm_data_t *data, const char *message, int exit_code);

    void fill_info(int argc, char **argv, vm_data_t *data);
    void parse_arguments(int ac, char **av, vm_data_t *info);

    void create_arena(vm_data_t *data);
    void exit_vm_file(vm_data_t *data, char *filename, char *error_msg);
    int cor_file_load(vm_data_t *data, temp_player_t player, FILE *fd);

    //MINI PARSING
    bool can_be_retrieved(int max_size, int start, int size);
    int fill_instruction_arguments_error(instruction_arg_t args[3], op_t op,
        cor_file_t *file, u_int8_t *battlefield);
    int increment_pc(cor_file_t *file, op_t op, instruction_arg_t args[3]);
    int check_registers(cor_file_t *file, op_t op, instruction_arg_t args[3]);

    //INSTRUCTIONS
    bool exec_instruction(vm_data_t *vdata, pfork_t *player, arena_t *arena);

    //PARSE INSTRUCTION ARGUMENT
    void parse_instruction_arguments(instruction_arg_t args[3], op_t op,
        int pc, arena_t *arena);
    bool has_mem_bypass(op_t op);

    //OP UTILS
    op_t find_instruction(u_int8_t byte);
    bool has_coding_byte(const char *mnemonique);
    bool has_index(const char *mnemonique);
    bool check_valid_args(op_t op, instruction_arg_t *args);
    int64_t get_argument_value(instruction_arg_t *args, pfork_t *player,
        arena_t *arena);
    void set_argument_value(instruction_arg_t *args, pfork_t *player,
        vm_data_t *vdata, reg_t value);
    int64_t retrieve_data(const u_int8_t battlefield[MEM_SIZE], size_t start,
        size_t size);
    size_t get_argument_size(u_int8_t coding_byte, size_t i, bool is_index,
        instruction_arg_t args[3]);

    //INSTRUCTION UTILS
    int get_instruction_size(instruction_arg_t *args, op_t op);
    bool is_valid_reg(instruction_arg_t *args);

    //INSTRUCTIONS FN
    int live_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int ld_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int st_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int add_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int sub_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int and_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int or_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int xor_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int zjmp_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int ldi_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int sti_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int fork_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int lld_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int lldi_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int lfork_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int aff_run(vm_data_t *vdata, arena_t *arena, pfork_t *player, instruction_arg_t *args);
    void create_new_fork(pfork_t *player, int new_pc);

    //SCHEDULER
    void start_vm(vm_data_t *data);
    int referee_checking(vm_data_t* data);
    void print_player_status(cwindow_t *ncurses_data_s, int player_nb, const char *player_name,
        const char *player_status);

// ========================================================================== //
#endif /* !VM_H_ */
