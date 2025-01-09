#include "corewar_instructions.h"

// xor 명령어: 두 값을 XOR 연산하고 결과를 레지스터에 저장
void inst_xor(t_corewar *cw, t_carriage *carriage)
{
    int res;
    int reg;
    int val1;
    int val2;

    carriage->step += 2;  // 첫 번째 두 인자에 대한 스텝 증가
    val1 = get_inst_argument(carriage, 0, true, cw);  // 첫 번째 인자 가져오기
    val2 = get_inst_argument(carriage, 1, true, cw);  // 두 번째 인자 가져오기
    res = val1 ^ val2;  // XOR 연산
    carriage->carry = res ? false : true;  // carry 플래그 설정
    reg = cw->map[calculate_address(carriage->pc + carriage->step)];
    carriage->reg[reg - 1] = res;  // 결과를 해당 레지스터에 저장
    carriage->step += 1;  // 스텝 증가

    // verbose 출력: xor 명령어
    if (cw->verbose & OPS)
        printf("P %4d | xor %d %d r%d\n", carriage->id, val1, val2, reg);
}
