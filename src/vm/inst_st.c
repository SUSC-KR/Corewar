#include "corewar_instructions.h"

void inst_st(t_corewar *cw, t_carriage *carriage)
{
    int value;
    int address;
    int reg;

    carriage->step += 2;  // ST 명령어는 2단계가 필요
    reg = cw->map[calculate_address(carriage->pc + carriage->step)];  // 레지스터 번호 추출
    value = carriage->reg[reg - 1];  // 해당 레지스터에서 값 추출
    carriage->step += 1;  // 스텝 증가

    if (carriage->args_types[1] != T_REG)
    {
        address = get_int(cw->map, carriage->step + carriage->pc, IND_SIZE);  // 주소 추출
        write_to_bytecode(cw->map, carriage->pc + (address % IDX_MOD), value, DIR_SIZE);  // 메모리에 값 기록
        carriage->step += 2;  // 스텝 증가

        if (cw->visual)
            upd_map_ind(cw, carriage, carriage->pc + (address % IDX_MOD), DIR_SIZE);
    }
    else
    {
        address = cw->map[calculate_address(carriage->pc + carriage->step)];  // 레지스터 주소 추출
        carriage->reg[address - 1] = value;  // 해당 레지스터에 값 저장
        carriage->step += 1;  // 스텝 증가
    }

    if (cw->verbose & OPS)
        printf("P %4d | st r%d %d\n", carriage->id, reg, address);
}