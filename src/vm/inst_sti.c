#include "corewar_instructions.h"

// sti 명령어: 레지스터의 값을 계산된 주소에 저장
void inst_sti(t_corewar *cw, t_carriage *carriage)
{
    int reg;
    int address1;
    int address2;
    int val;

    carriage->step += 2;  // 첫 번째 두 인자 처리
    reg = cw->map[calculate_address(carriage->pc + carriage->step)];
    val = carriage->reg[reg - 1];  // 레지스터 값 가져오기
    ++(carriage->step);  // 스텝 증가
    address1 = get_inst_argument(carriage, 1, true, cw);  // 첫 번째 주소 값 가져오기
    address2 = get_inst_argument(carriage, 2, true, cw);  // 두 번째 주소 값 가져오기
    // 메모리 위치에 값 쓰기
    write_to_bytecode(cw->map, carriage->pc + (address1 + address2) % IDX_MOD, val, DIR_SIZE);
    // 비주얼 모드에서 해당 위치 업데이트
    if (cw->visual)
        upd_map_ind(cw, carriage, carriage->pc + (address1 + address2) % IDX_MOD, DIR_SIZE);
    // verbose 출력: sti 명령어
    if (cw->verbose & OPS)
    {
        printf("P %4d | sti r%d %d %d\n", carriage->id, reg, address1, address2);
        printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", address1, address2, address1 + address2, carriage->pc + ((address1 + address2) % IDX_MOD));
    }
}
