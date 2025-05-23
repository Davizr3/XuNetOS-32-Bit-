///////////////////////////////////////////
// XuNet OS BY:INBORA 2025
// COPYRIGHT (C) 2019-2025 INBORA
// 何乐源码旗下
// INBORA/PENGZZEKAI/XuNet
// 
// =================================
//
// XuNet OS Help Alokads06@gmail.com
////////////////////////////////////////////

/*
 |--|  |--|             |--|
 |  |  |  |             |  |
 |  |--|  |    _____    |  |    ______
 |        |   //---\\   |  |   //---\ \
 |  |--|  |  | |___| |  |  |   ||   | |
 |  |  |  |  | |___/-\  |  |   ||   | |
 |--|  |--|   \_____/   |--|   \\___/ /
*/

#include "bootpack.h"
void make_window8(unsigned char *buf, int xsize, int ysize, char *title, char act)
{
	boxfill8(buf, xsize, COL8_FFFFFF, 0,         0,         xsize - 1, 0        );
	boxfill8(buf, xsize, 16+(30/51)+(144/51)*6+(255/51)*36, 0,         0,         xsize - 1, 0        );
	boxfill8(buf, xsize, 16+(30/51)+(144/51)*6+(255/51)*36, 1,         1,         xsize - 2, 1        );
	boxfill8(buf, xsize, 16+(30/51)+(144/51)*6+(255/51)*36, 0,         0,         0,         ysize - 1);
	boxfill8(buf, xsize, 16+(30/51)+(144/51)*6+(255/51)*36, 1,         1,         1,         ysize - 2);
	boxfill8(buf, xsize, 16+(30/51)+(144/51)*6+(255/51)*36, xsize - 2, 1,         xsize - 2, ysize - 2);
	boxfill8(buf, xsize, 16+(30/51)+(144/51)*6+(255/51)*36, xsize - 1, 0,         xsize - 1, ysize - 1);
	boxfill8(buf, xsize, COL8_FFFFFF, 2,         2,         xsize - 3, ysize - 3);
	boxfill8(buf, xsize, COL8_FFFFFF, 3,         3,         xsize - 4, 20       );
	boxfill8(buf, xsize, 16+(30/51)+(144/51)*6+(255/51)*36, 1,         ysize - 2, xsize - 2, ysize - 2);
	boxfill8(buf, xsize, 16+(30/51)+(144/51)*6+(255/51)*36, 0,         ysize - 1, xsize - 1, ysize - 1);
	make_wtitle8(buf, xsize, title, act);
	return;
}

void make_wtitle8(unsigned char *buf, int xsize, char *title, char act)
{
	static char closebtn[14][16] = {
		"QQQQQQ$$$$QQQQQQ",
		"QQQQ$$$$$$$$QQQQ",
		"QQQ$$$$$$$$$$QQQ",
		"QQ$$@@$$$$@@$$QQ",
		"QQ$$$@@$$@@$$$QQ",
		"Q$$$$$@@@@$$$$$Q",
		"Q$$$$$$@@$$$$$$Q",
		"Q$$$$$@@@@$$$$$Q",
		"Q$$$$@@$$@@$$$$Q",
		"QQ$$@@$$$$@@$$QQ",
		"QQ$$$$$$$$$$$$QQ",
		"QQQ$$$$$$$$$$QQQ",
		"QQQQ$$$$$$$$QQQQ",
		"QQQQQQ$$$$QQQQQQ"
	};
	int x, y;
	char c, tc, tbc;
	if (act != 0) {
		tc = COL8_C6C6C6;
		tbc = 255;
	} else {
		tc = COL8_000000;
		tbc = 255;
	}
	boxfill8(buf, xsize, tbc, 3, 3, xsize - 4, 20);
	putfonts8_asc(buf, xsize, 24, 4, tc, title);
	for (y = 0; y < 14; y++) {
		for (x = 0; x < 16; x++) {
			c = closebtn[y][x];
			if (c == '@') {
				c = COL8_FFFFFF;
			} else if (c == '$') {
				c = COL8_FF0000;
			} else if (c == 'Q') {
				c = 255;
			} else {
				c = 255;
			}
			buf[(5 + y) * xsize + (xsize - 21 + x)] = c;
		}
	}
	return;
}

void putfonts8_asc_sht(struct SHEET *sht, int x, int y, int c, int b, char *s, int l)
{
	struct TASK *task = task_now();
	boxfill8(sht->buf, sht->bxsize, b, x, y, x + l * 8 - 1, y + 15);
	if (task->langmode != 0 && task->langbyte1 != 0) {
		putfonts8_asc(sht->buf, sht->bxsize, x, y, c, s);
		sheet_refresh(sht, x - 8, y, x + l * 8, y + 16);
	} else {
		putfonts8_asc(sht->buf, sht->bxsize, x, y, c, s);
		sheet_refresh(sht, x, y, x + l * 8, y + 16);
	}
	return;
}

void make_textbox8(struct SHEET *sht, int x0, int y0, int sx, int sy, int c)
{
	int x1 = x0 + sx, y1 = y0 + sy;
	boxfill8(sht->buf, sht->bxsize, COL8_000000, x0 - 1, y0 - 2, x1 + 0, y0 - 2);
	boxfill8(sht->buf, sht->bxsize, COL8_000000, x0 - 2, y0 - 2, x0 - 2, y1 + 0);
	boxfill8(sht->buf, sht->bxsize, COL8_000000, x0 - 2, y1 + 1, x1 + 0, y1 + 1);
	boxfill8(sht->buf, sht->bxsize, COL8_000000, x1 + 1, y0 - 2, x1 + 1, y1 + 1);
	boxfill8(sht->buf, sht->bxsize, c,           x0 - 1, y0 - 1, x1 + 0, y1 + 0);
	return;
}

void change_wtitle8(struct SHEET *sht, char act)
{
	int x, y, xsize = sht->bxsize;
	char c, tc_new, tbc_new, tc_old, tbc_old, *buf = sht->buf;
	if (act != 0) {
		tc_new  = COL8_FFFFFF;
		tbc_new = 255;
		tc_old  = COL8_C6C6C6;
		tbc_old = 255;
	} else {
		tc_new  = COL8_C6C6C6;
		tbc_new = 255;
		tc_old  = COL8_FFFFFF;
		tbc_old = 255;
	}
	for (y = 3; y <= 20; y++) {
		for (x = 3; x <= xsize - 4; x++) {
			c = buf[y * xsize + x];
			if (c == tc_old && x <= xsize - 22) {
				c = tc_new;
			} else if (c == tbc_old) {
				c = tbc_new;
			}
			buf[y * xsize + x] = c;
		}
	}
	sheet_refresh(sht, 1, 1, xsize, 25);
	return;
}
