#include "corewar_instructions.h"

void inst_ld(t_corewar *cw, t_carriage *carriage)
{
    int reg;
    int value;

    carriage->step += 2;  // LD 명령어는 2단계가 필요
    value = get_inst_argument(carriage, 0, true, cw);  // 첫 번째 인자 값 추출
    carriage->carry = value ? false : true;  // carry 플래그 업데이트
    reg = cw->map[calculate_address(carriage->pc + carriage->step)];  // 레지스터 번호 추출
    carriage->reg[reg - 1] = value;  // 해당 레지스터에 값을 저장
    carriage->step += 1;  // 스텝 증가

    if (cw->verbose & OPS)
        printf("P %4d | ld %d r%d\n", carriage->id, value, reg);
}