#include "corewar_instructions.h"

// zjmp 명령어: carry 플래그가 참일 경우, 주어진 주소로 PC를 이동시킴
void inst_zjmp(t_corewar *cw, t_carriage *carriage)
{
    int address;

    carriage->step += 1;  // 첫 번째 인자 처리
    address = get_inst_argument(carriage, 0, true, cw);  // 주소 값 가져오기
    // carry 플래그가 true일 때만 jump 수행
    if (carriage->carry == true)
    {
        if (cw->visual)
            dull_carriage(carriage, cw);  // 비주얼 모드에서 캐리지를 흐리게 표시
        carriage->pc = calculate_address(carriage->pc + (address % IDX_MOD));  // 주소 계산하여 pc 이동
        carriage->step = 0;  // 스텝 리셋
        if (cw->visual)
            highlight_carriage(carriage, cw);  // 비주얼 모드에서 캐리지를 강조
    }
    // verbose 출력: zjmp 명령어
    if (cw->verbose & OPS)
        printf("P %4d | zjmp %d %s\n", carriage->id, address, (carriage->carry) ? "OK" : "FAILED");
}
