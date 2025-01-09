#include "corewar_instructions.h"

// ldi 명령어: 주소1과 주소2의 값을 더한 후, 그 위치에서 값을 읽어 레지스터에 저장
void inst_ldi(t_corewar *cw, t_carriage *carriage)
{
    int reg;
    int address1;
    int address2;

    carriage->step += 2;  // 첫 번째 두 인자 처리
    address1 = get_inst_argument(carriage, 0, true, cw);  // 첫 번째 인자 값 가져오기
    address2 = get_inst_argument(carriage, 1, true, cw);  // 두 번째 인자 값 가져오기
    reg = cw->map[calculate_address(carriage->pc + carriage->step)];  // 해당 레지스터를 가져오기
    // 지정된 주소에서 값 읽기
    carriage->reg[reg - 1] = get_int(cw->map, carriage->pc + (address1 + address2) % IDX_MOD, DIR_SIZE);  
    carriage->step += 1;  // 스텝 증가

    // verbose 출력: ldi 명령어
    if (cw->verbose & OPS)
    {
        printf("P %4d | ldi %d %d r%d\n", carriage->id, address1, address2, reg);
        printf("       | -> load from %d + %d = %d (with pc and mod %d)\n", address1, address2, address1 + address2, carriage->pc + (address1 + address2) % IDX_MOD);
    }
}
