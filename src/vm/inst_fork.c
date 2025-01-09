#include "corewar_instructions.h"

// fork 명령어: 주어진 주소를 기준으로 새로운 캐리지를 복제
void inst_fork(t_corewar *cw, t_carriage *carriage)
{
    int address;

    carriage->step += 1;  // 첫 번째 인자 처리
    address = get_inst_argument(carriage, 0, true, cw);  // 주소 값 가져오기
    // 새로운 캐리지를 추가
    add_carriage(&(cw->carriages), dup_carriage(carriage, address % IDX_MOD, cw));
    ++(cw->carriages_num);  // 캐리지 수 증가
    // verbose 출력: fork 명령어
    if (cw->verbose & OPS)
        printf("P %4d | fork %d (%d)\n", carriage->id, address, carriage->pc + address % IDX_MOD);
}
