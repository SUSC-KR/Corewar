#include "corewar.h"

void visualize(t_corewar *cw)
{
    prepare(cw);  // 게임 초기화

    // 게임 루프
    while ((cw->visual->btn = getch()) != ESCAPE)
    {
        proc_btn(cw->visual, cw->carriages_num);

        // 게임 진행 및 화면 업데이트
        if (cw->visual->pause == false &&
            (cw->visual->time + CLOCKS_PER_SEC / cw->visual->speed <= clock()))
        {
            cw->visual->time = clock();  // 시간 업데이트
            battle_vs(cw);  // 게임 진행
        }

        visualize_all(cw);
    }

    system("pkill afplay");
    exit_visual(cw);
}
