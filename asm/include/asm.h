/*
** EPITECH PROJECT, 2023
** asm
** File description:
** asm
*/

#ifndef ASM_H_
    #define ASM_H_

// =============================== [INCLUDES] =============================== //

    #include <stdio.h>
    #include <stdbool.h>
    #include <sys/types.h>
    #include "../../lib/include/lib.h"
    #include "op.h"
    #include "linked_list.h"

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
    * @brief This macro defines the ANSI escape code for purple text.
    *  It is used to color output text to stderr.
    * @warning Private macro, should not be used
    */
    #define __PURPLE "\033[38;2;157;0;230m"

    /**
    * @brief This macro defines the ANSI escape code for blue text.
    *  It is used to color output text to stderr.
    * @warning Private macro, should not be used
    */
    #define __BLUE "\033[38;2;131;187;251m"

    /**
    * @brief This macro resets the ANSI color codes.
    *  It is used to reset the color of output text to stderr.
    * @warning Private macro, should not be used
    */
    #define __RESET "\033[0m"

    /**
    * @brief This macro writes the ANSI color code for purple to the specified
    *  output stream. It is used to change the color of output text to purple
    *  on stderr.
    * @warning Private macro, should not be used.
    * @param stream The output stream where to write the purple color code.
    */
    #define __W_PURPLE(stream) fwrite(__PURPLE, sizeof(char), 17, stream)

    /**
    * @brief This macro writes the ANSI color code for blue to the specified
    *  output stream. It is used to change the color of output text to blue on
    *  stderr.
    * @warning Private macro, should not be used.
    * @param stream The output stream where to write the blue color code.
    */
    #define __W_BLUE(stream) fwrite(__BLUE, sizeof(char), 19, stream)

    /**
    * @brief This macro resets the ANSI color codes to default. It is used to
    *  reset the color of output text to the default color on stderr.
    * @warning Private macro, should not be used.
    * @param stream The output stream where to reset the color code to default.
    */
    #define __W_DEFAULT(stream) fwrite(__RESET, sizeof(char), 4, stream)

    /**
    * @brief Macro to write an error message to stderr.
    *  This macro writes an error message to stderr with a purple "[ERROR]"
    *  label at the beginning and resets the color at the end.
    * @warning This macro contains multiple statements, so it should be used
    *  with brackets.
    * @param ptr The error message to be written.
    * @param n The length of the error message.
    */
    #define ERROR_WRITE(ptr, n) __W_PURPLE(stderr)__S \
        fwrite("[ERROR]\t", sizeof(char), 8, stderr)__S \
        fwrite(ptr, sizeof(char), n, stderr)__S \
        __W_DEFAULT(stderr)__S

    /**
    * @brief Macro to write a warning message to stderr.
    *  This macro writes a warning message to stderr with a purple "[WARNING]"
    *  label at the beginning, a blue color for the message and resets the color
    *  at the end.
    * @warning This macro contains multiple statements, so it should be used
    *  with brackets.
    * @param ptr The warning message to be written.
    * @param n The length of the warning message.
    */
    #define WARNING_WRITE(ptr, n) __W_PURPLE(stderr)__S \
        fwrite("[WARNING]\t", sizeof(char), 10, stderr)__S \
        __W_BLUE(stderr)__S fwrite(ptr, sizeof(char), n, stderr)__S \
        __W_DEFAULT(stderr)__S

    /**
    * @brief The exit status code for a program failure.
    */
    #define FAILURE 84

    /**
    * @brief The exit status code for a successful program execution.
    */
    #define SUCCESS 0

// ============================== [STRUCTURES] ============================== //

    /**
    * @brief An instruction in the assembly code.
    *  This struct contains the instruction code, coding byte, types and
    *  arguments of an instruction in the assembly code.
    */
    typedef struct instruction_s {
        /** The code of the instruction */
        int8_t instruction_code;
        /** The coding byte */
        int coding_byte;
        /** The types of the arguments */
        args_type_t args_type[4];
        /** The values of the arguments */
        int args[4];
        /** The labels associated with each argument */
        char *labels_array[4];
        /** The total number of bytes used by the instruction */
        int total_bytes;
    } instruction_t;

    /**
    * @brief A temporary instruction in the assembly code.
    *  This struct is used to hold temporary data while parsing instructions
    *  in the assembly code.
    */
    typedef struct temp_instruction_s {
        /** The operation associated with the instruction */
        op_t op;
        /** The index of the instruction */
        int ind;
    } temp_instruction_t;

    /**
    * @brief Struct representing a temporary split of a string.
    * The `temp_split_t` struct holds information about a temporary split of a
    * string including the original string and its split representation.
    */
    typedef struct temp_split_s {
        /** Pointer to the original string. */
        char *str;
        /** Pointer to the split string array. */
        char **split;
    } temp_split_t;

    /**
    * @brief A label in the assembly code
    *  This struct contains the name and position of a label in the assembly
    *  code.
    */
    typedef struct label_s {
        /** The name of the label */
        char *name;
        /** The position of the label (as an integer) */
        int int_pos;
        /** The position of the label (as a byte offset) */
        int byte_pos;
    } label_t;

    /**
    * @brief Data used for the assembly process.
    *  This struct contains data used during the assembly process, including
    *  file input/output information, the loaded file, the file size, the file
    *  header, the labels, the instructions, and the current/total instruction
    *  count.
    */
    typedef struct asm_data_s {
        /** The input file */
        FILE *fd_input;
        /** The name of the output file */
        char *output_file_name;
        /** The loaded file */
        char **loaded_file;
        /** The size of the file */
        int file_size;
        /** The index of the file */
        int file_ind;
        /** Flag indicating whether the file has a comment. */
        bool has_comment;
        /** The header of the file */
        header_t *file_header;
        /** The labels in the file */
        linked_list_t *labels;
        /** The instructions in the file */
        linked_list_t *instructions;
        /** The current instruction number */
        int curr_instr_nbr;
        /**< The total number of instructions */
        int tot_instr_nbr;
    } asm_data_t;

// ============================= [DECLARATIONS] ============================= //

    asm_data_t *init_asm_data(void);
    void destructor_label(void *data);
    void destructor_instruction(void *data);

    void check_arguments_type(asm_data_t *asm_data, int ac, char **av);
    char *get_output_file_name(char *filename);
    char **load_file(asm_data_t *asm_data);
    void check_input_and_output_files(asm_data_t *asm_data, int ac, char **av);
    void clean_loaded_file(asm_data_t *data);
    char *trim_string(char *str);

    void fill_header_fields(asm_data_t *asm_data);
    void fill_name_field(asm_data_t *asm_data);
    void fill_comment_filed(asm_data_t *asm_data);

    void fill_instructions_field(asm_data_t *asm_data);
    void try_add_label(asm_data_t *asm_data, char **split, int instruction_nbr);
    bool is_valid_label(char *label);

    void check_instruction(asm_data_t *asm_data, char **split,
        int instruction_code, int ind);
    bool has_index_asm(const char *mnemonique);
    bool is_register(bool *is_arg_valid, char *arg);
    int try_adding_register_value(asm_data_t *asm_data, temp_split_t info,
        instruction_t *instruction);
    void save_register(args_type_t args[4], int *args_ind);
    bool is_direct(bool *is_arg_valid, char *arg);
    int try_adding_direct_value(asm_data_t *asm_data, temp_split_t info,
        instruction_t *instruction, char **unknown_label);
    void save_direct(args_type_t args[4], int *args_ind);
    bool is_indirect(bool *is_arg_valid, char *arg);
    int try_adding_indirect_value(asm_data_t *asm_data, temp_split_t info,
        instruction_t *instruction, char **unknown_label);
    void save_indirect(args_type_t args[4], int *args_ind);
    void create_instruction(asm_data_t *asm_data, char **split,
        temp_instruction_t instruction_info, args_type_t args[4]);
    bool has_coding_byte_asm(const char *mnemonique);
    int8_t get_coding_byte(op_t op, args_type_t args[4]);
    void set_total_bytes(instruction_t *instruction, op_t op);
    void update_label(asm_data_t *asm_data, instruction_t *instruction,
        linked_list_t *labels);
    void assign_labels(header_t *header, instruction_t *instruction,
        linked_list_t *labels);

    void print_into_output_file(asm_data_t *asm_data);

    void exit_asm(asm_data_t *asm_data, const char *message, int exit_code);
    void exit_asm_arr(asm_data_t *asm_data, const char *message, int exit_code,
        char **array);
    void free_array(char **array);

// ========================================================================== //
#endif /* !ASM_H_ */
