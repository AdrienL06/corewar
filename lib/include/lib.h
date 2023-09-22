/*
** EPITECH PROJECT, 2022
** my.h
** File description:
** my_header
*/

#ifndef MY_HEADER_
    #define MY_HEADER_

// =============================== [INCLUDES] =============================== //

    #include <sys/types.h>
    #include <stdbool.h>

// ============================= [DECLARATIONS] ============================= //

    int my_strlen(const char *str);
    int my_arrlen(char **arr);
    void *my_memset(void *s, int c, size_t n);
    int my_put_nbr(int nb);
    char *my_strcat(char *dest, const char *src);
    char *my_strncat(char *dest, char *src, int nb);
    char *my_mstrcat(char *left, const char *right);
    char *my_strcat_delim(char *left, char *delim, char *right);
    int my_strcmp(const char *s1, const char *s2);
    int my_strncmp(const char *s1, const char *s2, int n);
    char *my_strcpy(char *dest, const char *src);
    char *my_strncpy(char *dest, const char *src, int n);
    char *my_strdup(char *str);
    char *my_strstr(char *str, const char *to_find);
    char **str_to_array(char *str, const char *delim);
    int is_char_in_str(char c, const char *str);
    int my_atoi(const char *str, char *endptr);
    bool does_str_contain_only_chars(char *str, const char *chars);

// ========================================================================== //
#endif
