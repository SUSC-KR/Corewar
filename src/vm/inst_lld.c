#include "corewar_instructions.h"

void	inst_lld(t_corewar *cw, t_carriage *carriage)
{
	int	reg;
	int	value;

	carriage->step += 2;
	value = get_inst_argument(carriage, 0, false, cw);
	carriage->carry = value ? 0 : 1;
	reg = cw->map[calculate_address(carriage->pc + carriage->step)];
	carriage->reg[reg - 1] = value;
	carriage->step += 1;
	if (cw->verbose & OPS)
		printf("P %4d | lld %d r%d\n", carriage->id, value, reg);
}
