#include "corewar_instructions.h"

// sub 명령어: 두 레지스터의 값을 빼고 결과를 세 번째 레지스터에 저장
void inst_sub(t_corewar *cw, t_carriage *carriage)
{
    int val;
    int reg1;
    int reg2;
    int reg3;

    carriage->step += 2;  // 첫 번째 두 인자에 대한 스텝 증가
    reg1 = cw->map[calculate_address(carriage->pc + carriage->step)];
    ++(carriage->step);  // 스텝 증가
    reg2 = cw->map[calculate_address(carriage->pc + carriage->step)];
    ++(carriage->step);  // 스텝 증가
    reg3 = cw->map[calculate_address(carriage->pc + carriage->step)];
    val = carriage->reg[reg1 - 1] - carriage->reg[reg2 - 1];  // 레지스터 값 차이 계산
    carriage->carry = val ? false : true;  // carry 플래그 설정
    carriage->reg[reg3 - 1] = val;  // 결과를 세 번째 레지스터에 저장
    ++(carriage->step);  // 스텝 증가

    // verbose 출력: sub 명령어
    if (cw->verbose & OPS)
        printf("P %4d | sub r%d r%d r%d\n", carriage->id, reg1, reg2, reg3);
}