#include "apilib.h"

#include <string.h>	/* strlen */
#include <stdio.h>

int strtol(char *s, char **endp, int base);	 /*��׼����<stdlib.h> */

void waittimer(int timer, int time);

int _main()
{
	char winbuf[400 * 300], txtbuf[100 * 1024];
	char s[32], *p, *r;
	int win, x = 64, y = 64, timer, i, j;
	
	/*׼������*/
	win = api_openwin(winbuf, 400, 300, 255, "��Ƶ");

	/*�����н���*/
	api_cmdline(s, 30);

	for (p = s; *p > ' '; p++) { }	//һֱ�����ո�Ϊֹ
	for (; *p == ' '; p++) { }	//�����ո�
	i = strlen(p);
	if (i > 12 || i == 0) 
	{
file_error:
	api_putstrwin(win, 5/*����λ��*/, 26/*����λ��*/, 0/*��ɫ:��*/, 50/*���ֿ��*/, "ϵͳ�Ҳ���ָ���ļ����ļ�����");/*��������*/
		for (;;) {}
	}
	
	/*�����ļ�*/
	i = api_fopen(p);
	if (i == 0) 
	{
		goto file_error;
	}
	j = api_fsize(i, 0);
	if (j >= 100 * 1024)
	{
		j = 100 * 1024 - 1;
	}
	api_fread(txtbuf, j, i);
	api_fclose(i);
	txtbuf[j] = 0;
	r = txtbuf;
	i = 0; /*ͨ��ģʽ*/
	
	api_putstrwin(win, 16, 24, 3, 12, p);
	
	for (p = txtbuf; *p != 0; p++) {	//Ϊ�˷��㴦����ע�ͺͿհ�ɾȥ
		if (i == 0 && *p > ' ') {		//���ǿո���з�
			if (*p == '/') {
				if (p[1] == '*') {
					i = 1;
				} else if (p[1] == '/') {
					i = 2;
				} else {
					*r = *p;
					if ('a' <= *p && *p <= 'z') {
						*r += 'A' - 'a';	//��Сд��ĸת��Ϊ��д��ĸ
					}
					r++;
				}
			}
			else if (*p == 0x22) 
			{
				*r = *p;
				r++;
				i = 3;
			}
			else 
			{
				*r = *p;
				r++;
			}
		}
		else if (i == 1 && *p == '*' && p[1] == '/') 
		{	//��ע��
			p++;
			i = 0;
		} 
		else if (i == 2 && *p == 0x0a) 
		{	//��ע��
			i = 0;
		}
		else if (i == 3) 
		{	//�ַ���
			*r = *p;
			r++;
			if (*p == 0x22) {
				i = 0;
			}
			else if (*p == '%')
			{
				p++;
				*r = *p;
				r++;
			}
		}
	}
	*r = 0;

	/*��ʱ��׼��*/
	timer = api_alloctimer();
	api_inittimer(timer, 128);

	/*����*/
	p = txtbuf;
	for (;;) {
		if (*p == '&') 
		{
			for (;;) {}
		}
		else if (*p == '.')
		{
			if (y > 128) {
				y = 64;
			}
			if (x < 127) {
				x++;
			} else {
				y++;
				x = 64;
			}
			api_point(win, x, y, 7);
		}
		else if (*p == '0')
		{
			if (y > 128) {
				y = 64;
			}
			if (x < 127) {
				x++;
			} else {
				y++;
				x = 64;
			}
			api_point(win, x, y, 0);
		}
		else if (*p == 0) 
		{
			x = 64;
			p = txtbuf;
		} 
		p++;
	}
	return 0;
}

void waittimer(int timer, int time)
{
	int i;
	api_settimer(timer, time);
	for (;;) 
	{
		i = api_getkey(1);
		if (i == 128) 
		{
			return;
		}
	}
}

