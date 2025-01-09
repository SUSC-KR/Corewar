#include "corewar.h"

void	visualize_menu(t_corewar *cw)
{
	wattron(cw->visual->menu, A_BOLD);
	mvwprintw(cw->visual->menu, 2, 15, " _____  _   _  _____  _____ ");
    mvwprintw(cw->visual->menu, 2 + 1, 15, "/  ___|| | | |/  ___|/  __ \\");
    mvwprintw(cw->visual->menu, 2 + 2, 15, "\\ `--. | | | |\\ `--. | /  \\/");
    mvwprintw(cw->visual->menu, 2 + 3, 15, " `--. \\| | | | `--. \\| |    ");
    mvwprintw(cw->visual->menu, 2 + 4, 15, "/\\__/ /| |_| |/\\__/ /| \\__/\\");
    mvwprintw(cw->visual->menu, 2 + 5, 15, "\\____/  \\___/ \\____/  \\____/ ");


    mvwprintw(cw->visual->menu, 9, 9, " _____                  _    _            ");
    mvwprintw(cw->visual->menu, 9 + 1, 9, "/  __ \\                | |  | |           ");
    mvwprintw(cw->visual->menu, 9 + 2, 9, "| /  \\/ ___  _ __ ___  | |  | | __ _ _ __ ");
    mvwprintw(cw->visual->menu, 9 + 3, 9, "| |    / _ \\| '__/ _ \\ | |/\\| |/ _` | '__|");
    mvwprintw(cw->visual->menu, 9 + 4, 9, "| \\__/\\ (_) | | |  __/ \\  /\\  / (_| | |   ");
    mvwprintw(cw->visual->menu, 9 + 5, 9, "\\____/ \\___/|_|  \\___|  \\/  \\/ \\__,_|_|   ");

	mvwprintw(cw->visual->menu, 18, 9, "Start / Pause\t\tSPACE");
	mvwprintw(cw->visual->menu, 20, 9, "Increase speed\t\tARROW Right");
	mvwprintw(cw->visual->menu, 21, 9, "Decrease speed\t\tARROW Left");
	mvwprintw(cw->visual->menu, 23, 9, "Exit\t\t\tCTRL + Z");
}
