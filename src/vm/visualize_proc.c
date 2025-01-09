#include "corewar.h"

void play_sound(bool finish)
{
	static int i = 0;

	if (finish)
	{
		system("pkill afplay");
		system("afplay mp3/somemusic.mp3 &> /dev/null &");
	}
	else
	{
		i = (i + 1) % 5;
		if (i == 0)
			system("afplay mp3/somemusic.mp3 &> /dev/null &");
	}
}

void battle_vs(t_corewar *cw)
{
	int	carriages;

	if (cw->carriages_num)
	{
		execute_one_cycle(cw);
		if (cw->cycles_to_die <= 0
			|| cw->cycles_to_die == cw->cycles_after_check)
		{
			carriages = cw->carriages_num;
			update_cycles_to_die(cw);
			if (cw->carriages_num && carriages != cw->carriages_num)
				play_sound(false);
		}
		if (cw->carriages_num == 0)
		{
			play_sound(true);
			cw->visual->pause = true;
		}
	}
}

void proc_btn(t_visual *visual, int carriages)
{
    // Space 키로 게임 일시정지/재개
    if (visual->btn == SPACE)
        visual->pause = !visual->pause;

    // 방향키 왼쪽으로 속도 감소
    if (visual->btn == KEY_LEFT)
    {
        visual->speed = (visual->speed <= 200) ? visual->speed - 10 : visual->speed - 100;
    }

    // 방향키 오른쪽으로 속도 증가
    if (visual->btn == KEY_RIGHT)
    {
        visual->speed = (visual->speed < 200) ? visual->speed + 10 : visual->speed + 100;
    }

    // 캐리지가 없으면 자동으로 일시정지
    if (carriages == 0)
        visual->pause = true;

    // 속도 제한
    if (visual->speed < 10)
        visual->speed = 10;
    if (visual->speed > 1000)
        visual->speed = 1000;
}


void visualize_all(t_corewar *cw)
{
	werase(cw->visual->win);
	werase(cw->visual->info);
	visualize_win(cw);
	visualize_menu(cw);
	visualize_info(cw);
	box(cw->visual->win, 0, 0);
	box(cw->visual->menu, 0, 0);
	box(cw->visual->info, 0, 0);
	wrefresh(cw->visual->win);
	wrefresh(cw->visual->info);
	wrefresh(cw->visual->menu);
}

int	upd_map_ind(t_corewar *cw, t_carriage *carriage, int address, int size)
{
	int	ind;

	ind = 1 + ((carriage->champ->id - 1) % 4);
	while (size)
	{
		cw->visual->map[calculate_address(address + size - 1)].ind = ind;
		cw->visual->map[calculate_address(address +
				size - 1)].wait_cycle_st = 50;
		--size;
	}
	return (1);
}
