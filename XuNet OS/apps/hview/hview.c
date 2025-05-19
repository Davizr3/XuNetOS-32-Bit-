/*��ֲ��ink oINBORAȨ��ston��ink os����������*/
#include "apilib.h"
#include <string.h>
#include <stdio.h>

int strtol(char *s, char **endp, int base);	 /*��׼����<stdlib.h> */
void waittimer(int timer, int time);

int _main()
{
	char winbuf[400 * 300], win2buf[500 * 420], txtbuf[100 * 1024];
	char s[32], *p, *r;
	int win, win2, wide = 48, winstr_a = 32, winstr_b = 32, timer, i, j;
	/*׼������*/
	win = api_openwin(winbuf, 400, 300, 255, "Hview ---- HTML�鿴��");
	/*�����н���*/
	api_cmdline(s, 30);
	for (p = s; *p > ' '; p++) { }	//һֱ�����ո�Ϊֹ
	for (; *p == ' '; p++) { }	//�����ո�
	i = strlen(p);
	if (i > 12 || i == 0) 
	{
file_error:
	api_putstrwin(win, 5/*����λ��*/, 26/*����λ��*/, 0/*��ɫ:��*/, 50/*���ֿ���*/, "ϵͳ�Ҳ���ָ���ļ����ļ�����");/*��������*/
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
	
	for (p = txtbuf; *p != 0; p++) {	//Ϊ�˷��㴦������ע�ͺͿհ�ɾȥ
		if (i == 0 && *p > ' ') {		//���ǿո���з�
			if (*p == '/') {
				if (p[1] == '*') {
					i = 1;
				} else if (p[1] == '/') {
					i = 2;
				} else {
					*r = *p;
					if ('A' <= *p && *p <= 'Z') {
						*r += 'a' - 'A';	//����д��ĸת��ΪСд��ĸ
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
		p++;
		if (p[0] == '<' && p[1] == 'h' && p[2] == 'e' && p[3] == 'a' && p[4] == 'd' && p[5] == '>') 
		{
			p++;
			for (;; p++)
			{
				if (*p == 0 || *p == '<') {
					break;
				}
			}
			p++;
			for (i = 0; i < 48; i++)
			{
				if (*p == '<' && p[1] == '/' && p[2] == 't' && p[3] == 'i' && p[4] == 't' && p[5] == 'l' && p[6] == 'e' && p[7] == '>') {
					goto MAINA;
				}
				if (*p == '%') {
					s[i] = p[1];
					p += 2;
				} else {
					s[i] = *p;
					p++;
				}
			}
			s[i] = 0;
			if (i != 0) 
			{
				api_putstrwin(win + 1, 16, wide, 0, i, s);
			}
			api_refreshwin(win, 8, wide, 296, wide + 16);
			wide+=16;
			goto MAINA;
		}
	}
MAINA:
	for (;;) {}
	
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
