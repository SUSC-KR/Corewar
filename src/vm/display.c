#include "corewar.h"


void display_usage(void)
{
    printf("Usage: ./corewar [options] <champion1.core> <champion2.core> ...\n\n");

    printf("Options:\n");
    
    printf("\033[0;33m-dump <nbr_cycles>\033[0m\n");
    printf("\tAt the end of <nbr_cycles> cycles, dump the memory to the standard output and \033[0;31mexit\033[0m the game.\n");
    printf("\tThe memory will be dumped in hexadecimal format with 32 or 64 octets per line.\n");

    printf("\033[0;33m-d <nbr_cycles>\033[0m\n");
    printf("\tSame as -dump, but using shorthand. Dumps memory after <nbr_cycles> and \033[0;31mexits\033[0m.\n");

    printf("\033[0;33m-debug32 <nbr_cycles>\033[0m or \033[0;33m-debug64 <nbr_cycles>\033[0m\n");
    printf("\tAt the end of <nbr_cycles> cycles, dump the memory and \033[0;31mpause\033[0m the game.\n");
    printf("\tYou can choose between 32 or 64 octets per line in the hexadecimal format.\n");

    printf("\033[0;33m-n <number>\033[0m\n");
    printf("\tSpecify the next player's ID. If not specified, the player will get the next available ID based on the input order.\n");
    printf("\tThis allows you to control the order of the players.\n");

    printf("\033[0;33m-verbose <nbr>\033[0m\n");
    printf("\tEnable detailed logging of actions during the execution. You can combine the following log levels by adding their values:\n");
    printf("\t\t1  : Log lives\n\t\t2  : Log cycles\n\t\t4  : Log instructions\n");
    printf("\t\t8  : Log deaths\n\t\t16 : Log PC movements\n");

    printf("\033[0;33m-visual\033[0m\n");
    printf("\tLaunch a graphical visualizer with music to watch the game execution.\n\n");

    printf("Examples:\n");
    printf("  ./corewar -dump 1000 -n 1 champion1.core champion2.core\n");
    printf("  ./corewar -debug32 5000 -verbose 1 champion1.core champion2.core\n");
    printf("  ./corewar -visual -n 2 champion1.core champion2.core\n");

    printf("\nFor more details, refer to the documentation or source code.\n");
    
    exit(1);
}

int display_start_message(t_champ **champ)
{
    int id;

    printf("Introducing contestants...\n");
    id = -1;
    while (champ[++id])
        printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", 
			id + 1, champ[id]->size, champ[id]->name, champ[id]->comment);
    return 1;
}

void display_map(int mode, uint8_t *map)
{
    int i;
    int j;

    i = -mode;
    while ((i += mode) < MEM_SIZE && (j = -1))
    {
        printf("%.4d : ", i);
        while ((i + ++j < MEM_SIZE) && j < mode)
            printf("%.2x ", map[i + j]);
        printf("\n");
    }
}

void display_result(t_corewar *cw)
{
    printf("Contestant %d, \"%s\", has won !\n", cw->last->id, cw->last->name);
}