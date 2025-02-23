#include "corewar.h"

// 선수 정보를 출력하는 공통 함수
void print_player_info(t_corewar *cw, t_champ *champ, int row_offset)
{
    int color_pair = g_colors[(champ->id - 1) % 4 + 1];

    wattron(cw->visual->info, color_pair);
    mvwprintw(cw->visual->info, 22 + row_offset, 9, "Player number:");
    wattroff(cw->visual->info, color_pair);
    mvwprintw(cw->visual->info, 22 + row_offset, 24, "%d", champ->id);

    wattron(cw->visual->info, color_pair);
    mvwprintw(cw->visual->info, 23 + row_offset, 9, "Name:");
    wattroff(cw->visual->info, color_pair);
    mvwprintw(cw->visual->info, 23 + row_offset, 24, "%-.22s", champ->name);

    wattron(cw->visual->info, color_pair);
    mvwprintw(cw->visual->info, 24 + row_offset, 9, "Comment:");
    wattroff(cw->visual->info, color_pair);
    mvwprintw(cw->visual->info, 24 + row_offset, 24, "%-.22s", champ->comment);

    wattron(cw->visual->info, color_pair);
    mvwprintw(cw->visual->info, 25 + row_offset, 9, "Last live:");
    wattroff(cw->visual->info, color_pair);
    mvwprintw(cw->visual->info, 25 + row_offset, 24, "%d", champ->live);
}

// 게임 상태를 출력
void game_status(t_corewar *cw)
{
    mvwprintw(cw->visual->info, 2, 18, "=== INFO ===");
    mvwprintw(cw->visual->info, 5, 9, "Game status:\t");
    if (cw->carriages_num == 0)
    {
        wattron(cw->visual->info, COLOR_PAIR(RED));
        mvwprintw(cw->visual->info, 5, 32, "Finished");
        wattroff(cw->visual->info, COLOR_PAIR(RED));
    }
    else if (cw->visual->pause)
    {
        wattron(cw->visual->info, COLOR_PAIR(PINK));
        mvwprintw(cw->visual->info, 5, 32, "Paused");
        wattroff(cw->visual->info, COLOR_PAIR(PINK));
    }
    else
    {
        wattron(cw->visual->info, COLOR_PAIR(GRASS));
        mvwprintw(cw->visual->info, 5, 32, "Running");
        wattroff(cw->visual->info, COLOR_PAIR(GRASS));
    }
}

// 모든 선수 정보를 출력
void champs(t_corewar *cw)
{
    for (int i = 0; i < cw->champs_num; i++)
    {
        print_player_info(cw, cw->champs[i], 5 * i);
    }
}

// 승자 정보를 출력
void winner(t_corewar *cw)
{
    wattron(cw->visual->info, COLOR_PAIR(GRASS) | A_BOLD);
    mvwprintw(cw->visual->info, 23 + 5 * cw->champs_num, 18, "=== WINNER ===");
    wattroff(cw->visual->info, COLOR_PAIR(GRASS) | A_BOLD);
    
    print_player_info(cw, cw->last, 5 * cw->champs_num);
}

// 게임 정보를 출력
void visualize_info(t_corewar *cw)
{
    wattron(cw->visual->info, A_BOLD);
    game_status(cw);
    mvwprintw(cw->visual->info, 8, 9, "Speed:\t\t\t%d c.p.s.", cw->visual->speed);
    mvwprintw(cw->visual->info, 10, 9, "Cycles \t\t%d", cw->cycles);
    mvwprintw(cw->visual->info, 12, 9, "Carriages number:\t%d", cw->carriages_num);
    mvwprintw(cw->visual->info, 14, 9, "Cycles to die:\t\t%d", cw->cycles_to_die);
    mvwprintw(cw->visual->info, 16, 9, "Cycles delta:\t\t%d", CYCLE_DELTA);
    mvwprintw(cw->visual->info, 18, 9, "Cycles after check:\t%d", cw->cycles_after_check);
    mvwprintw(cw->visual->info, 20, 9, "Lives num:\t\t%d", cw->lives);

    champs(cw);

    if (cw->carriages_num == 0)
        winner(cw);
}
