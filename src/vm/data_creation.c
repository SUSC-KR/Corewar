#include "corewar.h"

t_corewar *new_corewar(void)
{
    t_corewar *corewar;

    corewar = (t_corewar *)malloc(sizeof(t_corewar));
    if (!corewar)
        terminate("Memory allocation failed for corewar");

    corewar->map = (uint8_t *)malloc(sizeof(uint8_t) * MEM_SIZE);
    if (!corewar->map)
        terminate("Memory allocation failed for map");

    corewar->champs = (t_champ **)malloc(sizeof(t_champ*) * (MAX_PLAYERS + 1));
    if (!corewar->champs)
        terminate("Memory allocation failed for champs");

    corewar->cycles_to_die = CYCLE_TO_DIE;
    corewar->dump_cycles = -1;
    corewar->debug_cycles = -1;

    return corewar;
}

t_champ *new_champ(char *file, int id)
{
    int fd;
    t_champ *champ;

    champ = (t_champ *)malloc(sizeof(t_champ));
    if (!champ)
        terminate("Memory allocation failed for champ");

    champ->id = id;

    fd = open(file, O_RDONLY);
    if (fd == -1)
        terminate("File opening failed");

    if (read_from_bytecode(fd) != COREWAR_EXEC_MAGIC)
        terminate("Invalid magic in bytecode");

    champ->name = read_str_from_bytecode(fd, PROG_NAME_LENGTH);
    if (read_from_bytecode(fd))
        terminate("Null bytes detected in bytecode");

    champ->size = read_from_bytecode(fd);
    if (champ->size > CHAMP_MAX_SIZE || champ->size < 0)
        terminate("Invalid code size");

    champ->comment = read_str_from_bytecode(fd, COMMENT_LENGTH);
    if (read_from_bytecode(fd))
        terminate("Null bytes detected in bytecode");

    champ->code = read_code(fd, champ->size);

    return champ;
}

t_carriage *new_carriage(t_champ *champ, int pc, t_corewar *cw)
{
    t_carriage *carriage;
    static int carriage_id = 0;

    carriage = (t_carriage *)malloc(sizeof(t_carriage));
    if (!carriage)
        terminate("Memory allocation failed for carriage");

    carriage->id = ++carriage_id;
    carriage->pc = pc;
    carriage->reg[0] = -(champ->id);
    carriage->champ = champ;

    if (carriage_id > cw->carriages_max)
    {
        cw->carriages_max += 1000;
        cw->all_carriages = (t_carriage **)realloc(cw->all_carriages, sizeof(t_carriage*) * cw->carriages_max);
        if (!cw->all_carriages)
            terminate("Memory allocation failed for all_carriages");
    }

    cw->all_carriages[carriage_id - 1] = carriage;

    return carriage;
}

t_carriage *dup_carriage(t_carriage *carriage, int address, t_corewar *cw)
{
    int i;
    t_carriage *new;

    address += carriage->pc;
    new = new_carriage(carriage->champ, calculate_address(address), cw);

    new->carry = carriage->carry;
    new->live_cycle = carriage->live_cycle;

    for (i = 0; i < REG_NUMBER; ++i)
        new->reg[i] = carriage->reg[i];

    return new;
}

t_visual *new_visual(void)
{
    t_visual *visual;

    visual = (t_visual *)malloc(sizeof(t_visual));
    if (!visual)
        terminate("Memory allocation failed for visual");

    visual->speed = SPEED;
    visual->pause = false;

    visual->map = (t_attr *)malloc(sizeof(t_attr) * MEM_SIZE);
    if (!visual->map)
        terminate("Memory allocation failed for visual map");

    return visual;
}
