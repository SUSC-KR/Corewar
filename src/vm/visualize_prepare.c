#include "corewar.h"

// 선수 이름에서 공백을 제거
void delete_whitespaces(t_corewar *cw)
{
    for (int i = 0; i < cw->champs_num; i++)
    {
        for (int j = 0; cw->champs[i]->name[j]; j++)
        {
            if (isspace(cw->champs[i]->name[j]))
                cw->champs[i]->name[j] = ' ';
        }
    }
}

// 초기화 함수
void prepare(t_corewar *cw)
{
    delete_whitespaces(cw);

    // ncurses 초기화
    initscr();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    refresh();
    cbreak();
    noecho();
    use_default_colors();
    start_color();
    set_colors();

    // 윈도우 설정
    cw->visual->menu = newwin(30, WIDTH / 3.5, 1, WIDTH + 2);
    cw->visual->win = newwin(HEIGHT, WIDTH, 1, 1);
    cw->visual->info = newwin(HEIGHT - 30, WIDTH / 3.5, 31, WIDTH + 2);

    // 맵과 캐리지 설정
    set_map(cw);
    set_carriages(cw);
}

// 색상 초기화
void set_colors(void)
{
    // ncurses 색상 초기화
    init_pair(DEFAULT, GREY_COLOR, COLOR_BLACK);
    init_pair(PINK, PINK_COLOR, COLOR_BLACK);
    init_pair(PEACH, PEACH_COLOR, COLOR_BLACK);
    init_pair(GRASS, GRASS_COLOR, COLOR_BLACK);
    init_pair(SKY, SKY_COLOR, COLOR_BLACK);
    init_pair(C_DEFAULT, COLOR_BLACK, GREY_COLOR);
    init_pair(C_PINK, COLOR_BLACK, PINK_COLOR);
    init_pair(C_PEACH, COLOR_BLACK, PEACH_COLOR);
    init_pair(C_GRASS, COLOR_BLACK, GRASS_COLOR);
    init_pair(C_SKY, COLOR_BLACK, SKY_COLOR);
    init_pair(L_PINK, COLOR_WHITE, PINK_COLOR);
    init_pair(L_PEACH, COLOR_WHITE, PEACH_COLOR);
    init_pair(L_GRASS, COLOR_WHITE, GRASS_COLOR);
    init_pair(L_SKY, COLOR_WHITE, SKY_COLOR);
    init_pair(RED, COLOR_RED, COLOR_BLACK);
}

void set_carriages(t_corewar *cw)
{
    for (t_carriage *carriage = cw->carriages; carriage; carriage = carriage->next)
    {
        highlight_carriage(carriage, cw);
    }
}

void set_map(t_corewar *cw)
{
    int pc = 0;
    int ind;

    for (int id = 0; id < cw->champs_num; id++)
    {
        ind = (id % 4) + 1;
        int pos = pc;

        // 해당 챔피언의 영역을 설정
        for (int i = 0; i < cw->champs[id]->size; i++)
        {
            cw->visual->map[pos + i].ind = ind;
        }

        pc += MEM_SIZE / cw->champs_num;
    }
}
