/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwinthei <jwinthei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 15:31:08 by hgysella          #+#    #+#             */
/*   Updated: 2019/07/30 20:48:03 by jwinthei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void			vs_audio(uint8_t mode)
{
	system("pkill afplay");
	(mode) ? system("afplay src/audio/win.mp3 &> /dev/null &") :\
			system("afplay src/audio/fail.mp3 &> /dev/null &");
}

void			vs_init(t_cw *cw)
{
	initscr();
	curs_set(0);
	start_color();
	init_pair(COL_CODE_CH1, COLOR_GREEN, COLOR_BLACK);
	init_pair(COL_CODE_CH2, COLOR_BLUE, COLOR_BLACK);
	init_pair(COL_CODE_CH3, COLOR_RED, COLOR_BLACK);
	init_pair(COL_CODE_CH4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(COL_CODE, COLOR_GRAY, COLOR_BLACK);
	init_pair(COL_BACK_CH1, COLOR_BLACK, COLOR_GREEN | COLOR_BRIGHT);
	init_pair(COL_BACK_CH2, COLOR_BLACK, COLOR_BLUE | COLOR_BRIGHT);
	init_pair(COL_BACK_CH3, COLOR_BLACK, COLOR_RED | COLOR_BRIGHT);
	init_pair(COL_BACK_CH4, COLOR_BLACK, COLOR_MAGENTA | COLOR_MAGENTA);
	init_pair(COL_BACK, COLOR_BLACK, COLOR_GRAY);
	init_pair(COL_LIVE_CODE_CH1, COLOR_GREEN, COLOR_WHITE);
	init_pair(COL_LIVE_CODE_CH2, COLOR_BLUE, COLOR_WHITE);
	init_pair(COL_LIVE_CODE_CH3, COLOR_RED, COLOR_WHITE);
	init_pair(COL_LIVE_CODE_CH4, COLOR_MAGENTA, COLOR_WHITE);
	init_pair(COL_GRAY_WHITE, COLOR_GRAY, COLOR_B_WHITE);
	init_pair(COL_LIVE_CAR_CH1, COLOR_WHITE, COLOR_GREEN | COLOR_BRIGHT);
	init_pair(COL_LIVE_CAR_CH2, COLOR_WHITE, COLOR_BLUE | COLOR_BRIGHT);
	init_pair(COL_LIVE_CAR_CH3, COLOR_WHITE, COLOR_RED | COLOR_BRIGHT);
	init_pair(COL_LIVE_CAR_CH4, COLOR_WHITE, COLOR_MAGENTA | COLOR_BRIGHT);
	init_pair(COL_TEXT, COLOR_WHITE, COLOR_BLACK);
	vs_print_windows(cw);
}
