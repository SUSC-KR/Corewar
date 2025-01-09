#include "corewar.h"
#include "corewar_instructions.h"

bool args_valid(t_carriage *carriage, t_inst *inst, t_corewar *cw)
{
	uint32_t	step;

	if (!(args_types_valid(carriage, inst)))
		return (false);

	step = 1 + inst->args_types_code;
	for (int i = 0; i < inst->args_num; ++i)
	{
		if ((inst->args_types[i] == T_REG) && !t_reg(carriage->pc, step, cw))
			return (false);
		// 인자 타입에 맞는 크기만큼 step 증가
		step += arg_size(carriage->args_types[i], inst);
	}

	return (true);
}

bool args_types_valid(t_carriage *carriage, t_inst *inst)
{
	for (int i = 0; i < inst->args_num; ++i)
		if (!(carriage->args_types[i] & inst->args_types[i]))
			return (false);
	return (true);
}

bool t_reg(int pc, int step, t_corewar *cw)
{
	int8_t	byte;

	byte = cw->map[calculate_address(pc + step)];
	return (byte > 0 && byte <= REG_NUMBER);
}
