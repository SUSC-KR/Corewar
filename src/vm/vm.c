#include "corewar.h"

// 게임의 초기 데이터를 설정하고 챔피언의 코드와 캐리지를 추가하는 함수
void create_start_data(t_corewar *cw)
{
    uint32_t pc = 0;
    int id;

    for (id = 0; id < cw->champs_num; ++id)
    {
        memcpy(&(cw->map[pc]), cw->champs[id]->code, cw->champs[id]->size);
        add_carriage(&(cw->carriages), new_carriage(cw->champs[id], pc, cw));
        ++(cw->carriages_num);
        pc += MEM_SIZE / cw->champs_num;
    }
}

// 시각화 모드일 때 불필요한 인자를 초기화하는 함수
void cancel_args(t_corewar *cw)
{
    cw->aff = false;
    cw->debug_cycles = -1;
    cw->dump_cycles = -1;
    cw->verbose = 0;
}

// 프로그램의 시작점
int main(int argc, char **argv)
{
    t_corewar *cw;

    if (argc < 2)
    {
        display_usage();
        return 1;
    }

    // 인자 파싱 후 새로운 corewar 객체 생성
    cw = new_corewar();
    parse_args(argc, argv, cw);

    create_start_data(cw);

    if (cw->visual)
    {
        cancel_args(cw);
        visualize(cw);
    }
    else
    {
        display_start_message(cw->champs);
        run_battle(cw);
        display_result(cw);
    }

    return 0;
}
