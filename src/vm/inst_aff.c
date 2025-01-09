#include "corewar_instructions.h"

void	inst_aff(t_corewar *cw, t_carriage *carriage)
{
	int	val;
	int	reg;

	carriage->step += 2;
	reg = cw->map[calculate_address(carriage->pc + carriage->step)];
	val = carriage->reg[reg - 1];
	++(carriage->step);
	if (cw->aff)
		printf("Aff: %c\n", (char)val);
}
