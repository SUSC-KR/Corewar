#include "corewar_instructions.h"

void	inst_lldi(t_corewar *cw, t_carriage *carriage)
{
	int	reg;
	int	address1;
	int	address2;

	carriage->step += 2;
	address1 = get_inst_argument(carriage, 0, true, cw);
	address2 = get_inst_argument(carriage, 1, true, cw);
	reg = cw->map[calculate_address(carriage->pc + carriage->step)];
	carriage->reg[reg - 1] = get_int(cw->map, carriage->pc + address1 + address2, DIR_SIZE);
	carriage->step += 1;
	printf("P %4d | lldi %d %d r%d\n", carriage->id, address1, address2, reg);
	printf("       | -> load from %d + %d = %d (with pc and mod %d)\n", address1, address2, address1 + address2, carriage->pc + address1 + address2);
}