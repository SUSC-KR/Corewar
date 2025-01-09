#include "corewar.h"
#include "corewar_instructions.h"

int calculate_address(int address)
{
    address %= MEM_SIZE;
    if (address < 0)
        address += MEM_SIZE;
    return address;
}

uint32_t arg_size(uint8_t arg, t_inst *inst)
{
    if (arg & T_REG)
        return 1;
    else if (arg & T_DIR)
        return inst->t_dir_size;
    else if (arg & T_IND)
        return 2;
    else
        return 0;
}

uint32_t step(t_carriage *carriage, t_inst *inst)
{
    uint32_t step = 1 + (inst->args_types_code);
    for (int i = 0; i < g_inst[carriage->instruction - 1].args_num; ++i)
    {
        step += arg_size(carriage->args_types[i], inst);
    }
    return step;
}
