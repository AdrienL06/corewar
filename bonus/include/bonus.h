#ifndef BONUS_H_
    #define BONUS_H_

    #include <ncurses.h>

    #define PLAYER_WIN_SIZE 37

    enum colors {
        C_DEFAULT = 0,
        C_RED,
        C_GREEN,
        C_YELLOW,
        C_BLUE,
        C_MAGENTA,
        C_BLACK,
        C_CYAN,
        C_WHITE,
        C_MAX,
    };

    typedef struct cwindow_s {
        WINDOW *win;
        int x;
        int y;
        int width;
        int height;
    } cwindow_t;

    typedef struct ncurses_data_s {
        bool is_running;
        cwindow_t *arena;
        cwindow_t *players;
        int scroll_pos;
    } ncurses_data_t;

    /* UTILS */
    typedef struct vm_data_s vm_data_t;
    void display_arena_ncurses(vm_data_t *data, ncurses_data_t *ndata, int start_x);
    void display_player_info(vm_data_t *vdata, ncurses_data_t *ndata);

    /* EVENTS */
    bool check_events(ncurses_data_t *ndata, vm_data_t *vdata);
#endif /* !BONUS_H_ */
