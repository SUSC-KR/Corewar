#include "corewar_instructions.h"

void inst_add(t_corewar *cw, t_carriage *carriage)
{
    int val;
    int reg1, reg2, reg3;

    carriage->step += 2;  // ADD 명령어는 3개의 인자를 처리하므로 2단계 증가
    reg1 = cw->map[calculate_address(carriage->pc + carriage->step)];  // 첫 번째 레지스터 번호 추출
    ++(carriage->step);  // 스텝 증가
    reg2 = cw->map[calculate_address(carriage->pc + carriage->step)];  // 두 번째 레지스터 번호 추출
    ++(carriage->step);  // 스텝 증가
    reg3 = cw->map[calculate_address(carriage->pc + carriage->step)];  // 세 번째 레지스터 번호 추출
    val = carriage->reg[reg1 - 1] + carriage->reg[reg2 - 1];  // 두 레지스터 값의 합 계산
    carriage->carry = val ? false : true;  // carry 플래그 업데이트
    carriage->reg[reg3 - 1] = val;  // 결과 값을 세 번째 레지스터에 저장
    ++(carriage->step);  // 스텝 증가

    if (cw->verbose & OPS)
        printf("P %4d | add r%d r%d r%d\n", carriage->id, reg1, reg2, reg3);
}
