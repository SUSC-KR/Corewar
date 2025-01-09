#include "corewar.h"

void visualize_win(t_corewar *cw)
{
    static int cycles = 0;
    int attr;

    // 메모리 맵을 출력
    for (int i = 0; i < 64; i++)
    {
        wmove(cw->visual->win, i + 2, 3);
        for (int j = 0; j < 64; j++)
        {
            attr = get_attr(cw, &(cw->visual->map[i * 64 + j]), cycles);
            wattron(cw->visual->win, attr);
            wprintw(cw->visual->win, "%.2x ", cw->map[i * 64 + j]);
            wattroff(cw->visual->win, attr);
        }
        wprintw(cw->visual->win, "\n");
    }

    cycles = cw->cycles;
}
