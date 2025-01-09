#include "corewar.h"

// verbose_death: 프로세스가 생존하지 못한 주기를 출력하는 함수
void verbose_death(t_carriage *del, t_corewar *cw)
{
    int live_duration = cw->cycles - del->live_cycle;

    printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
           del->id, live_duration, cw->cycles_to_die);
}

// verbose_cycles: 현재 'Cycle to die' 값 출력 함수
void verbose_cycles(int cycles)
{
    printf("Cycle to die is now %d\n", cycles);
}

// verbose_pc: 캐리지의 PC 값과 그에 해당하는 메모리 상태를 출력하는 함수
void verbose_pc(t_carriage *carriage, uint8_t *map)
{
    printf("ADV %d (%p -> %p) ",
           carriage->step, (void *)(intptr_t)carriage->pc, (void *)(intptr_t)(carriage->pc + carriage->step));
    
    // 0 < carriage->step이면 진행
    if (carriage->step > 0)
    {
        for (int i = 0; i < carriage->step; ++i)
        {
            // 메모리에서 해당 주소의 값을 출력
            printf("%02x ", map[calculate_address(carriage->pc + i)]);
        }
    }
    printf("\n");
}