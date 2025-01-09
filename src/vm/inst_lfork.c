#include "corewar_instructions.h"

void	inst_lfork(t_corewar *cw, t_carriage *carriage)
{
	int			address;

	carriage->step += 1;
	address = get_inst_argument(carriage, 0, true, cw);
	add_carriage(&(cw->carriages), dup_carriage(carriage, address, cw));
	++(cw->carriages_num);
	if (cw->verbose & OPS)
		printf("P %4d | lfork %d (%d)\n", carriage->id, address, carriage->pc + address);
}