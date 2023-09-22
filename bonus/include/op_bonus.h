/*
** EPITECH PROJECT, 2023
** asm
** File description:
** New version of op.h edited by Fowdre <virgile.legros@epitech.eu> and
** AdrienL06 <adrien.lachambre@epitech.eu>
** Original description:
** op.h for  korewar
** Made by Astek
** Login   <astek@epitech.net>
** Started on  Mon Mar 30 11:14:31 2009 Astek
** Last update Tue Mar 22 16:44:20 2011 Astek
*/

#ifndef OP_H_
    #define OP_H_
    #include <sys/types.h>

// =============================== [DEFINES] ================================ //

    #define SEPARATOR_CHAR ','
    #define COMMENT_CHAR '#'
    #define LABEL_CHAR ':'
    #define DIRECT_CHAR '%'
    #define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"
    #define COREWAR_EXEC_MAGIC 0xea83f3
    #define NAME_CMD_STRING ".name"
    #define PROG_NAME_LENGTH 128
    #define COMMENT_CMD_STRING ".comment"
    #define COMMENT_LENGTH 2048
    #define MAX_ARGS_NUMBER 4 /* This may not be changed 2^*IND_SIZE */
    #define T_REG 1 /* register */
    #define T_DIR 2 /* direct (ld #1, r1 | put 1 into r1) */
    #define T_IND 4 /* indirect always relative (ld 1, r1 | put what's in the
                        address (1+pc) into r1 (4 bytes)) */
    #define T_IDX 8 /* index */
    #define REG_NUMBER 16 /* r2 to rREG_NUMBER | r1 is reserved */
    #define IND_SIZE 2
    #define DIR_SIZE 4

    #define IDX_MOD 512
    #define MEM_SIZE (6 * 1024)
    #define REG_SIZE DIR_SIZE

    #define CYCLE_TO_DIE 1536 /* number of cycle before being declared dead */
    #define CYCLE_DELTA 5
    #define NBR_LIVE 40

    #if REG_SIZE == 1
        typedef int8_t reg_t;
    #elif REG_SIZE == 2
        typedef int16_t reg_t;
    #elif REG_SIZE == 4
        typedef int32_t reg_t;
    #elif REG_SIZE == 8
        typedef int64_t reg_t;
    #else
        #error "Invalid reg size"
    #endif

// ============================== [STRUCTURES] ============================== //

    typedef char args_type_t;
    typedef struct arena_s arena_t;
    typedef struct pfork_s pfork_t;
    typedef struct instruction_arg_s instruction_arg_t;
    typedef struct vm_data_s vm_data_t;

    typedef struct op_s {
        const char *mnemonique;
        char nbr_args;
        args_type_t type[MAX_ARGS_NUMBER];
        char code;
        int nbr_cycles;
        int (*exec)(vm_data_t *, arena_t *, pfork_t *, instruction_arg_t *);
        const char *comment;
    } op_t;

    extern op_t op_tab[];

    enum instruction_type_e {
        I_LIVE,
        I_LD,
        I_ST,
        I_ADD,
        I_SUB,
        I_AND,
        I_OR,
        I_XOR,
        I_ZJMP,
        I_LDI,
        I_STI,
        I_FORK,
        I_LLD,
        I_LLDI,
        I_LFORK,
        I_AFF,
        I_UNKNOWN
    };

    /**
    * @brief The header of the .cor file.
    *  This struct contains the magic number, program name, program size and
    *  comment of the .cor file.
    */
    typedef struct header_s {
        /** The magic number of the .cor file */
        int magic;
        /** The name of the program (up to 128 bytes) */
        char prog_name[PROG_NAME_LENGTH + 1];
        /** The size of the program */
        int prog_size;
        /** The comment (up to 2048 bytes) */
        char comment[COMMENT_LENGTH + 1];
    } header_t;

// ========================================================================== //
#endif /* !OP_H_ */
