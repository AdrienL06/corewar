/*
** EPITECH PROJECT, 2023
** bonus
** File description:
** nevents
*/

#include "vm.h"
#include "bonus.h"

bool check_events(ncurses_data_t *ndata, vm_data_t *vdata)
{
    MEVENT mevent;

    int ch = getch();
    //for (int ch = getch(), running = 0; running; ch = getch()) {
        switch (ch) {
            case KEY_F(1):
            case 'q':
                ndata->is_running = false;
                return ndata;
                break;
            case ' ':
                while (true)
                    if (getch() == ' ')
                        break;
            case KEY_UP:
                if (ndata->scroll_pos > 0)
                    ndata->scroll_pos--;
                break;
            case KEY_DOWN:
                ndata->scroll_pos++;
                break;
            case KEY_MOUSE:
                if (getmouse(&mevent) == OK) {
                    if (mevent.bstate & BUTTON4_PRESSED && mevent.bstate & BUTTON_SHIFT) {
                        if (ndata->scroll_pos > 3)
                            ndata->scroll_pos -= 3;
                        else
                            ndata->scroll_pos = 0; 
                    }
                    else if (mevent.bstate & BUTTON5_PRESSED && mevent.bstate & BUTTON_SHIFT)
                        ndata->scroll_pos += 3;
                    else if (mevent.bstate & BUTTON4_PRESSED) {
                        if (ndata->scroll_pos > 0)
                            ndata->scroll_pos--;
                    }
                    else if (mevent.bstate & BUTTON5_PRESSED)
                        ndata->scroll_pos++;
                }
        }
    //}
    display_arena_ncurses(vdata, vdata->ndata, vdata->ndata->scroll_pos);
    display_player_info(vdata, vdata->ndata);
    //while (true)
    //    if (getch() == ' ')
    //        break;
    //endwin();
    //exit(77);
    //ndata->is_running = true;
    return true;
}