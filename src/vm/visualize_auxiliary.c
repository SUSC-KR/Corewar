#include "corewar.h"

int get_attr(t_corewar *cw, t_attr *attr, int cycles)
{
    if (cw->cycles != cycles && cw->cycles_to_die > 0)
    {
        if (attr->wait_cycle_live > 0)
            --(attr->wait_cycle_live);
        if (attr->wait_cycle_st > 0)
            --(attr->wait_cycle_st);
    }

    if (attr->wait_cycle_live)
        return (g_colors[(attr->champ->id - 1) % 4 + 10] | A_BOLD);
    if (attr->wait_cycle_st)
        return (g_colors[attr->ind] | A_BOLD);
    
    return g_colors[attr->ind];
}

// highlight와 dull의 공통된 로직을 함수로 묶음
void change_carriage_color(t_carriage *carriage, t_corewar *cw, int offset)
{
    int ind = cw->visual->map[carriage->pc].ind;
    if (ind >= 0 && ind <= 4 && offset > 0)
        cw->visual->map[carriage->pc].ind = ind + offset;
    else if (ind >= 5 && ind <= 9 && offset < 0)
        cw->visual->map[carriage->pc].ind = ind + offset;
}

// carriage의 색을 강조&흐리게하는 함수
void highlight_carriage(t_carriage *carriage, t_corewar *cw)
{
    change_carriage_color(carriage, cw, 5);
}
void dull_carriage(t_carriage *carriage, t_corewar *cw)
{
    change_carriage_color(carriage, cw, -5);
}

// visual 종료시 리소스 해제
void exit_visual(t_corewar *cw)
{
    delwin(cw->visual->win);
    delwin(cw->visual->info);
    delwin(cw->visual->menu);
    
    free(cw->visual->map);
    free(cw->visual);
    
    endwin();
}
