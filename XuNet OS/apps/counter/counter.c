#include <stdio.h>
#include "apilib.h"

void _main()
{
	char *buf, s[12];
	int win, timer, sec = 0, min = 0, hou = 0;
	api_initmalloc();
	buf = api_malloc(150 * 50);
	win = api_openwin(buf, 150, 50, 255, "���");
	timer = api_alloctimer();
	api_inittimer(timer, 128);
	for (;;) {
		sprintf(s, "%02d:%02d:%02d", hou, min, sec);
		api_boxfilwin(win, 28, 27, 115, 41, 7);
		api_putstrwin(win, 28, 27, 0 , 11, s);
		api_settimer(timer, 100);
		if (api_getkey(1) != 128) {
			break;
		}
		sec++;
		if (sec == 60) {
			sec = 0;
			min++;
			if (min == 60) {
				min = 0;
				hou++;
			}
		}
	}
	api_end();
}
