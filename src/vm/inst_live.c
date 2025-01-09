#include "corewar_instructions.h"

void inst_live(t_corewar *cw, t_carriage *carriage)
{
    t_champ *champ = NULL;
    int id;

    ++(cw->lives);
    carriage->step += 1;  // 라이브 명령어의 스텝 추가
    id = get_inst_argument(carriage, 0, false, cw);
    carriage->live_cycle = cw->cycles;  // 라이브 사이클 업데이트

    if (id >= -(cw->champs_num) && id <= -1)
    {
        champ = cw->champs[-id - 1];
        cw->last = champ;
        champ->live = cw->cycles;  // 해당 챔피언의 마지막 라이브 업데이트
        if (cw->visual)
        {
            cw->visual->map[carriage->pc].wait_cycle_live = 50;
            cw->visual->map[carriage->pc].champ = champ;
        }
    }

    if (cw->verbose & OPS)
        printf("P %4d | live %d\n", carriage->id, id);

    if ((cw->verbose & LIVES) && champ)
        printf("Player %d (%s) is said to be alive\n", -id, champ->name);
}