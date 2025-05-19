#include "apilib.h"

int _main()
{
	int win, i, j, k, dis;
	char buf[216 * 237];
	struct POINT {
		int x, y;
	};
	static struct POINT table[16] = { //绘制点，线
		{ 204, 129 }, { 195,  90 }, { 172,  58 }, { 137,  38 }, {  98,  34 },
		{  61,  46 }, {  31,  73 }, {  15, 110 }, {  15, 148 }, {  31, 185 },
		{  61, 212 }, {  98, 224 }, { 137, 220 }, { 172, 200 }, { 195, 168 },
		{ 204, 129 }
	};

	win = api_openwin(buf, 216, 237, 255, "2dBall");//准备窗口
	api_boxfilwin(win, 8, 29, 207, 228, 0);
	
	//循环计数（来回循环）
	for (;;) { 
		k++;
		for (i = 0; i <= 14; i++) {
			for (j = i + 1; j <= 15; j++) {
				dis = j - i;			 // 两点间的距离
				if (dis >= 8)
					dis = 15 - dis;		 // 逆向计数
				if (dis != 0)
					api_linewin(win, table[i].x, table[i].y, table[j].x, table[j].y, k - dis);
			}
		}
	}
	
	return 0;
}
