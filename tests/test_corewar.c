/*
** EPITECH PROJECT, 2023
** B-CPE-200-NCE-2-1-corewar-virgile.legros
** File description:
** test_corewar
*/

#include "tests.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test (corewar, display_help, .init = redirect_all_std)
{
    char *argv[] = {"./corewar", "-h", NULL};
    int result = run_corewar(argv);

    cr_assert_eq(result, 0);
}

Test (corewar, unrecognized_option, .init = redirect_all_std)
{
    char *argv[] = {"./corewar", "-niko", NULL};
    int result = run_corewar(argv);

    cr_assert_eq(result, 84);
}

Test (corewar, not_enought_argument, .init = redirect_all_std)
{
    char *argv[] = {"./corewar", NULL};
    int result = run_corewar(argv);

    cr_assert_eq(result, 84);
}

Test (corewar, too_few_players, .init = redirect_all_std)
{
    char *argv[] = {"./corewar", "tests/test_files/corewar/niko_empty.cor", NULL};
    int result = run_corewar(argv);

    cr_assert_eq(result, 84);
}

Test (corewar, too_much_players, .init = redirect_all_std)
{
    char const niko_empty[] = "tests/test_files/corewar/niko_empty.cor";
    char *argv[] = {"./corewar", niko_empty, niko_empty, niko_empty, niko_empty, niko_empty, NULL};
    int result = run_corewar(argv);

    cr_assert_eq(result, 84);
}

Test (corewar, invalid_n_no_player, .init = redirect_all_std)
{
    char const niko_empty[] = "tests/test_files/corewar/niko_empty.cor";
    char *argv[] = {"./corewar", "-n", "10", NULL};
    int result = run_corewar(argv);

    cr_assert_eq(result, 84);
}


Test (corewar, invalid_n_number, .init = redirect_all_std)
{
    char const niko_empty[] = "tests/test_files/corewar/niko_empty.cor";
    char *argv[] = {"./corewar", "-n", "sun", niko_empty, niko_empty, NULL};
    int result = run_corewar(argv);

    cr_assert_eq(result, 84);
}

Test (corewar, invalid_n_number_2, .init = redirect_all_std)
{
    char const niko_empty[] = "tests/test_files/corewar/niko_empty.cor";
    char *argv[] = {"./corewar", "-n", "10", niko_empty, niko_empty, NULL};
    int result = run_corewar(argv);

    cr_assert_eq(result, 84);
}

Test (corewar, invalid_n_arlready_set, .init = redirect_all_std)
{
    char const niko_empty[] = "tests/test_files/corewar/niko_empty.cor";
    char *argv[] = {"./corewar", "-n", "1", niko_empty, "-n", "1", niko_empty, NULL};
    int result = run_corewar(argv);

    cr_assert_eq(result, 84);
}

Test (corewar, invalid_a_no_player, .init = redirect_all_std)
{
    char const niko_empty[] = "tests/test_files/corewar/niko_empty.cor";
    char *argv[] = {"./corewar", "-a", "10", NULL};
    int result = run_corewar(argv);

    cr_assert_eq(result, 84);
}


Test (corewar, invalid_a_number, .init = redirect_all_std)
{
    char const niko_empty[] = "tests/test_files/corewar/niko_empty.cor";
    char *argv[] = {"./corewar", "-a", "sun", niko_empty, niko_empty, NULL};
    int result = run_corewar(argv);

    cr_assert_eq(result, 84);
}

Test (corewar, invalid_a_number_2, .init = redirect_all_std)
{
    char const niko_empty[] = "tests/test_files/corewar/niko_empty.cor";
    char *argv[] = {"./corewar", "-a", "-10", niko_empty, niko_empty, NULL};
    int result = run_corewar(argv);

    cr_assert_eq(result, 84);
}

Test (corewar, invalid_dump_number_1, .init = redirect_all_std)
{
    char const niko_empty[] = "tests/test_files/corewar/niko_empty.cor";
    char *argv[] = {"./corewar", "-dump", "sun", niko_empty, NULL};
    int result = run_corewar(argv);

    cr_assert_eq(result, 84);
}

Test (corewar, invalid_dump_number_2, .init = redirect_all_std)
{
    char const niko_empty[] = "tests/test_files/corewar/niko_empty.cor";
    char *argv[] = {"./corewar", "-dump", "-10", niko_empty, NULL};
    int result = run_corewar(argv);

    cr_assert_eq(result, 84);
}

Test (corewar, overlap, .init = redirect_all_std)
{
    char const abel[] = "tests/test_files/corewar/abel.cor";
    char *argv[] = {"./corewar", "-a", "0", abel, "-a", "5", abel, NULL};
    int result = run_corewar(argv);

    cr_assert_eq(result, 84);
}

Test (corewar, invalid_file, .init = redirect_all_std)
{
    char const e6[] = "tests/test_files/corewar/e621.cor";
    char *argv[] = {"./corewar", e6, e6, NULL};
    int result = run_corewar(argv);

    cr_assert_eq(result, 84);
}

Test (corewar, invalid_instruction, .init = redirect_all_std)
{
    char const inv_in[] = "tests/test_files/corewar/invalid_instruction.cor";
    char *argv[] = {"./corewar", inv_in, inv_in, NULL};
    int result = run_corewar(argv);

    cr_assert_eq(result, 84);
}

Test (corewar, too_small, .init = redirect_all_std)
{
    char const empty[] = "tests/test_files/corewar/empty.cor";
    char *argv[] = {"./corewar", empty, empty, NULL};
    int result = run_corewar(argv);

    cr_assert_eq(result, 84);
}

Test (corewar, invalid_magic, .init = redirect_all_std)
{
    char const magic[] = "tests/test_files/corewar/invalid_magic.cor";
    char *argv[] = {"./corewar", magic, magic, NULL};
    int result = run_corewar(argv);

    cr_assert_eq(result, 84);
}

Test (corewar, invalid_size, .init = redirect_all_std)
{
    char const size[] = "tests/test_files/corewar/invalid_size.cor";
    char *argv[] = {"./corewar", size, size, NULL};
    int result = run_corewar(argv);

    cr_assert_eq(result, 84);
}

Test (corewar, all, .init = redirect_all_std)
{
    char const all[] = "tests/test_files/corewar/all.cor";
    char const lfork[] = "tests/test_files/corewar/lfork.cor";
    char *argv[] = {"./corewar", all, lfork, NULL};
    int result = run_corewar(argv);

    cr_assert_eq(result, 0);
}

Test (corewar, dump, .init = redirect_all_std)
{
    char const file[] = "tests/test_files/corewar/all.cor";
    char *argv[] = {"./corewar", "-dump", "10", file, file, NULL};
    int result = run_corewar(argv);

    cr_assert_eq(result, 0);
}
