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
    #include "op.h"
    #include <stdio.h>

// =============================== [DEFINES] ================================ //

    /**
     * @brief This macro adds a semicolon to the end of the line.
     * @warning Private macro, should not be used
     */
    #define __SEMICOLON ;

    /**
     * @brief This macro is an alias of __SEMICOLON.
     * @warning Private macro, should not be used
     */
    #define __S __SEMICOLON

    /**
     * @brief Macro to write the ANSI color code for red to the specified
     *  output stream. The macro is used to change the color of output text to
     *  red on stderr. It writes the ANSI escape sequence for setting the
     *  foreground color to a custom red value.
     * @warning This is a private macro and should not be used directly.
     * @param stream The output stream where the red color code should be
     *  written.
     */
    #define __RED "\033[38;2;168;15;1m"

    /**
     * @brief Macro to write the ANSI color code for gold to the specified
     *  output stream. The macro is used to change the color of output text to
     *  gold on stderr. It writes the ANSI escape sequence for setting the
     *  foreground color to a custom gold value.
     * @warning This is a private macro and should not be used directly.
     * @param stream The output stream where the gold color code should be
     *  written.
     */
    #define __GOLD "\033[38;2;230;175;21m"

    /**
     * @brief This macro resets the ANSI color codes.
     *  It is used to reset the color of output text to stderr.
     * @warning Private macro, should not be used
     */
    #define __RESET "\033[0m"

    /**
     * @brief Macro to write the ANSI color code for red to the specified
     *  output stream. The macro is used to change the color of output text to
     *  red on the specified output stream. It writes the ANSI escape sequence
     *  for setting the foreground color to red.
     * @warning This is a private macro and should not be used directly.
     * @param stream The output stream where the red color code should be
     *  written.
     */
    #define __W_RED(stream) fwrite(__RED, sizeof(char), 16, stream)

    /**
     * @brief Macro to write the ANSI color code for gold to the specified
     * output stream. The macro is used to change the color of output text to
     * gold on the specified output stream. It writes the ANSI escape sequence
     * for setting the foreground color to gold.
     * @warning This is a private macro and should not be used directly.
     * @param stream The output stream where the gold color code should be
     *  written.
     */
    #define __W_GOLD(stream) fwrite(__GOLD, sizeof(char), 18, stream)

    /**
     * @brief This macro resets the ANSI color codes to default. It is used to
     *  reset the color of output text to the default color on stderr.
     * @warning Private macro, should not be used.
     * @param stream The output stream where to reset the color code to default.
     */
    #define __W_DEFAULT(stream) fwrite(__RESET, sizeof(char), 4, stream)

    /**
     * @brief Macro to write an error message to stderr with red color
     * highlighting. The macro writes the specified error message string to the
     * stderr stream, applying red color highlighting to the text.
     * @warning This is a private macro and should not be used directly.
     * @param ptr Pointer to the error message string.
     * @param n   Number of characters to be written.
     */
    #define ERROR_WRITE_VM(ptr, n) __W_RED(stderr)__S \
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

    /**
     * @brief The exit status code for a program failure.
     */
    #define FAILURE 84

    /**
     * @brief The exit status code for a successful program execution.
     */
    #define SUCCESS 0
    #define PARSING_DEFAULT_VALUE -1
    #define PARSING_ERROR_VALUE -2147483648
    #define MAX_PLAYERS 4
    #define PROG_SIZE_POS sizeof(int) + PROG_NAME_LENGTH + 1

// ============================== [STRUCTURES] ============================== //

    /**
     * @struct referee_t
     * @brief Represents a referee in the game.
     * The referee manages the game's rules and progress.
     */
    typedef struct referee_s {
        /** Array indicating whether players are alive. */
        bool players_alive[MAX_PLAYERS];
        /** Number of cycles until the next "cycle to die" is reached. */
        int cycle_to_die;
        /** Number of "live" calls made by players. */
        int nb_of_live_call;
        /** Player number of the last "live" call made. */
        int last_live_call;
    } referee_t;

    /**
     * @struct fn_args_init_player_t
     * @brief Represents function arguments for initializing a player.
     * The structure holds the necessary parameters for initializing a player.
     */
    typedef struct fn_args_init_player_s {
        /** Number of players. */
        int nbr_player;
        /** Player's number. */
        int n;
        /** Player's starting address. */
        int a;
    } fn_args_init_player_t;

    /**
     * @struct temp_player_t
     * @brief  Represents temporary player information.
     * The structure holds temporary information about a player, such as the
     * program number,the filename, and the load address.
     */
    typedef struct temp_player_s {
        /** Program number. */
        int prog_nbr;
        /** Player's filename. */
        char *filename;
        /** Load address of the player's program. */
        int load_address;
    } temp_player_t;

    /**
     * @struct command_line_info_t
     * @brief Represents information parsed from the command line.
     * The structure holds information parsed from the command line, including
     * the number of players, the number of cycles to perform a memory dump,
     * an array of temporary player information, and an array indicating the
     * availability of program numbers.
     */
    typedef struct command_line_info_s {
        /** Number of players. */
        int nbr_player;
        /** Number of cycles to perform a memory dump. */
        int dump_nbr_cycle;
        /** Array of temporary player information. */
        temp_player_t tmp_players[4];
        /** Availability of program numbers. */
        bool availaible_prog_nbr[4];
    } command_line_info_t;

    /**
     * @struct cor_file_t
     * @brief Represents a .cor file.
     * The structure holds information about a .cor file, including its name,
     * size, the byte content of the file, and the program counter (pc) value.
     */
    typedef struct cor_file_s {
        /** Name of the .cor file. */
        char *name;
        /** Size of the .cor file in bytes. */
        int size;
        /** Byte content of the .cor file. */
        u_int8_t *bytes;
        /** Program counter (pc) value. */
        int pc;
    } cor_file_t;

    /**
     * @struct pfork_t
     * @brief Represents a forked process (player) in the virtual machine.
     * The structure holds information about a forked process, including its
     * player name, register values, program counter (pc), carry flag, cooldown,
     * and a pointer to the next process.
     */
    typedef struct pfork_s {
        /** Name of the player associated with the process. */
        char *player_name;
        /** Register values of the process. */
        reg_t registers[16];
        /** Program counter (pc) value. */
        int pc;
        /** Carry flag indicating the status of the last operation. */
        bool carry;
        /** Cooldown value determining the process's execution delay. */
        int cooldown;
        /** Pointer to the next forked process. */
        struct pfork_s *next;
    } pfork_t;

    /**
     * @struct player_t
     * @brief Represents a player in the virtual machine.
     * The structure holds information about a player, including its name,
     * associated forked processes, and a flag indicating if a live signal has
     * been sent to the player.
     */
    typedef struct player_s {
        /** Name of the player. */
        char player_name[PROG_NAME_LENGTH + 1];
        /** Pointer to the forked processes associated with the player. */
        pfork_t *forks;
        /** Flag indicating if a live signal has been sent to the player. */
        bool send_live_sig;
    } player_t;

    /**
     * @struct arena_t
     * @brief Represents the game arena in the virtual machine.
     * The structure holds the game arena where the battles take place.
     * It contains the battlefield, the players participating in the game, and
     * a referee to manage the game flow.
     */
    typedef struct arena_s {
        /** The game battlefield. */
        u_int8_t battlefield[MEM_SIZE];
        /** Array of players participating in the game. */
        player_t *players[MAX_PLAYERS];
        /** Pointer to the referee managing the game. */
        referee_t* referee;
    } arena_t;

    /**
     * @struct vm_data_t
     * @brief Represents the data needed for the virtual machine.
     * The structure holds the necessary data for running the virtual machine.
     * It includes the command line information, the loaded COR files, and the
     * game arena.
     */
    typedef struct vm_data_s {
        /** Pointer to the command line information. */
        command_line_info_t *cmd_line_info;
        /** Array of loaded COR files. */
        cor_file_t *cor_files[MAX_PLAYERS];
        /** Pointer to the game arena. */
        arena_t *arena;
    } vm_data_t;

    /**
     * @struct instruction_arg_t
     * @brief Represents an argument of an instruction.
     * The structure holds the data and attributes of an argument used in an
     * instruction. It includes the argument data, the argument type, and an
     * indicator for index modification.
     */
    typedef struct instruction_arg_s {
        /** The data value of the argument. */
        int64_t data;
        /** The type of the argument. */
        args_type_t type;
        /** Indicates if the argument uses index modification. */
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
    bool exec_instruction(pfork_t *player, arena_t *arena);

    //PARSE INSTRUCTION ARGUMENT
    void parse_instruction_arguments(instruction_arg_t args[3], op_t op,
        int pc, arena_t *arena);
    bool has_mem_bypass(op_t op);

    //OP UTILS
    op_t find_instruction(u_int8_t byte);
    bool has_coding_byte_vm(const char *mnemonique);
    bool has_index_vm(const char *mnemonique);
    bool check_valid_args(op_t op, instruction_arg_t *args);
    int64_t get_argument_value(instruction_arg_t *args, pfork_t *player,
        arena_t *arena);
    void set_argument_value(instruction_arg_t *args, pfork_t *player,
        arena_t *arena, reg_t value);
    int64_t retrieve_data(const u_int8_t battlefield[MEM_SIZE], size_t start,
        size_t size);
    size_t get_argument_size(u_int8_t coding_byte, size_t i, bool is_index,
        instruction_arg_t args[3]);

    //INSTRUCTION UTILS
    int get_instruction_size(instruction_arg_t *args, op_t op);
    bool is_valid_reg(instruction_arg_t *args);

    //INSTRUCTIONS FN
    int live_run(arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int ld_run(arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int st_run(arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int add_run(arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int sub_run(arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int and_run(arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int or_run(arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int xor_run(arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int zjmp_run(arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int ldi_run(arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int sti_run(arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int fork_run(arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int lld_run(arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int lldi_run(arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int lfork_run(arena_t *arena, pfork_t *player, instruction_arg_t *args);
    int aff_run(arena_t *arena, pfork_t *player, instruction_arg_t *args);
    void create_new_fork(pfork_t *player, int new_pc);

    //SCHEDULER
    void start_vm(vm_data_t *data);
    int referee_checking(vm_data_t* data);
    void print_player_status(int player_nb, const char *player_name,
        const char *player_status);

// ========================================================================== //
#endif /* !VM_H_ */
