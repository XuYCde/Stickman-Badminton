#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<tchar.h>
#include <Windows.h>
#include<stdlib.h>
#pragma comment(lib,"Winmm.lib")
#include <mmsystem.h>
#include<cstdlib>
#define High 716
#define Width 1080//���廭�泤��
#define G 5//�����������ٶ�
int position_x1,position_y1;
int position_x2, position_y2;//С��1��С��2��λ��
int ball_x, ball_y;//���λ��
int vx_player1, vy_player1;
int vx_player2, vy_player2;//С��1��С��2���ٶ�
int ball_vx, ball_vy;
int is_onfloot1 = 1;
int is_onfloot2 = 1;//������˵���Ծ�ж�
int player1_width_���� = 130;//��ɫ1����ͼƬ�е�һ�������Ŀ��
int player1_high_���� = 152;//��ɫ1����ͼƬ�߶�
int player2_width_���� = 130;//��ɫ2����ͼƬ�е�һ�������Ŀ��
int player2_high_���� = 154;//��ɫ1����ͼƬ�߶�
int player1_��_width = 144;//��ɫ1��ͼƬ���
int player1_��_high = 172;//��ɫ1��ͼƬ�߶�
int player2_��_width = 121;//��ɫ2��ͼƬ���
int player2_��_high = 182;//��ɫ2��ͼƬ�߶�
int player1_�� = 0;
int player2_�� = 0;
int player1_��_photo1_width=0;
int player2_��_photo1_width=0;
int player1_����_photo1_width = 0;
int player2_����_photo1_width = 0;//����ͼƬ������ӳ
int isplayed = 1;
int k = 0;
int j = 0;//�Ƿ��ѷ���
int score1 = 0;
int score2 = 0;//������Ϸ����
int state = 0;//�ж���Ϸ״̬
static int player1_����_photo2 = 0;
static int player2_����_photo2 = 0;
IMAGE beginphoto;//���忪ʼͼƬ
IMAGE bkphoto;//���屳��ͼƬ
IMAGE ����_player1,����_player1_mask;//�����ɫһ�ķ�����
IMAGE ����_player2_mask, ����_player2;//�����ɫ���ķ�����
IMAGE ball_mask, ball;//������ë��
IMAGE ��_player1_mask;
IMAGE ��_player1;//�����ɫһ������
IMAGE ��_player2_mask;
IMAGE ��_player2;//�����ɫ��������
IMAGE gameoverphoto;//������Ϸ����ͼƬ

void startup();//�趨��ʼ��
void show();//չʾͼ��
void updatewithoutinput();//��������ĸ���
void updatewithinput();//��Ҫ����ĸ���
void main() {
	initgraph(Width, High);
	startup();//���ݵĳ�ʼ��
	while (1){
		show();//������ʾ
		updatewithoutinput();
		updatewithinput();
	
	}
	_getch();
}
void startup()//���ݵĳ�ʼ�� 
{
	mciSendString(_T("open D:\\��Ϸ�ز�\\bk0.mp3 alias bkmusic"), NULL, 0, NULL);
	mciSendString(_T("play bkmusic"), NULL, 0, NULL);//��ӱ�������
	loadimage(&beginphoto, _T("D:\\��Ϸ�ز�\\begin_photo.png"));//���뿪ʼͼƬ
	loadimage(&bkphoto, _T("D:\\��Ϸ�ز�\\bkphoto.jpg"));//���뱳��ͼƬ
	loadimage(&����_player1_mask, _T("D:\\��Ϸ�ز�\\����_player1_mask.bmp"));
	loadimage(&����_player1, _T("D:\\��Ϸ�ز�\\����_player1.bmp"));//�����ɫһ����ͼƬ
	loadimage(&����_player2_mask, _T("D:\\��Ϸ�ز�\\����_player2_mask.bmp"));
	loadimage(&����_player2, _T("D:\\��Ϸ�ز�\\����_player2.bmp"));//�����ɫ������ͼƬ
	loadimage(&ball_mask, _T("D:\\��Ϸ�ز�\\ball_mask.bmp"));
	loadimage(&ball, _T("D:\\��Ϸ�ز�\\ball.bmp"));//������ë���ͼƬ
	loadimage(&��_player1_mask, _T("D:\\��Ϸ�ز�\\��_player1_mask.bmp"));
	loadimage(&��_player1, _T("D:\\��Ϸ�ز�\\��_player1.bmp"));//�����ɫһ����ͼƬ
	loadimage(&��_player2_mask, _T("D:\\��Ϸ�ز�\\��_player2_mask.bmp"));
	loadimage(&��_player2, _T("D:\\��Ϸ�ز�\\��_player2.bmp"));//�����ɫ������ͼƬ
	loadimage(&gameoverphoto, _T("D:\\��Ϸ�ز�\\end.jpg"));//����ͼ���ز�
	position_x1 = 100;
	position_y1 = 520;
	position_x2 = 750;
	position_y2 = 520;//��ʼ������С��λ��
	ball_x = position_x1+110;
	ball_y = 560;//��ʼ����ë��λ��
	vx_player1 = 20;
	vy_player1 = 0;
	vx_player2 = 20;
	vy_player2 = 0;//��ʼ������˵��ƶ��ٶ�
	ball_vx = 0;
	ball_vy = 0;//��ʼ����ë���ٶ�
	
	
}
void show() {
	
	if (state == 0) {
		putimage(0, 0, &beginphoto);//��״̬Ϊ0ʱ����ʾ��ʼͼƬ
	}
	if (state == 1) {
		putimage(0, 0, &bkphoto);//��״̬Ϊһʱ����ʾ����ͼƬ
		outtextxy(500, 30, "�ȷ�");//�ڻ����Ϸ���ʾ�ȷֶ���
		TCHAR s[20];//�����ַ������飬������ʾ�ȷ�
		TCHAR a[20];//�����ַ������飬������ʾ�ȷ�
		sprintf_s(a, _T("%d"), score2);
		sprintf_s(s, _T("%d"), score1);
		settextstyle(40, 0, _T("����"));
		outtextxy(500, 90, s);
		outtextxy(540, 90, ":");
		outtextxy(570, 90, a);//��ʾ�ȷ�
		putimage(ball_x, ball_y, &ball_mask, SRCAND);
		putimage(ball_x, ball_y, &ball, SRCPAINT);//��ʾ��ë��
		if (ball_y > position_y1) {
			putimage(position_x1, position_y1, player1_width_����, player1_high_����, &����_player1_mask, player1_����_photo1_width, 0, SRCAND);
			putimage(position_x1, position_y1, player1_width_����, player1_high_����, &����_player1, player1_����_photo1_width, 0, SRCPAINT);
		}
		if (ball_y > position_y2) {
			putimage(position_x2, position_y2, player2_width_����, player2_high_����, &����_player2_mask, player2_����_photo1_width, 0, SRCAND);
			putimage(position_x2, position_y2, player2_width_����, player2_high_����, &����_player2, player2_����_photo1_width, 0, SRCPAINT);
		}//���������·�ʱ��չʾ��һ��ͼƬ
		if (ball_y <= position_y1) {
			putimage(position_x1, position_y1, player1_��_width, player1_��_high, &��_player1_mask, player1_����_photo1_width, 0, SRCAND);
			putimage(position_x1, position_y1, player1_��_width, player1_��_high, &��_player1, player1_����_photo1_width, 0, SRCPAINT);
		}
		if (ball_y <= position_y2) {
			putimage(position_x2, position_y2, player2_��_width, player2_��_high, &��_player2_mask, player2_����_photo1_width, 0, SRCAND);
			putimage(position_x2, position_y2, player2_��_width, player2_��_high, &��_player2, player2_����_photo1_width, 0, SRCPAINT);
		}//���������Ϸ�ʱ��չʾ�ڶ���ͼƬ

	}
	
	if (state == 2) {
		
		putimage(0, 0, &bkphoto);
		outtextxy(500, 30, "�ȷ�");
		TCHAR s[20];//�����ַ�������
		TCHAR a[20];//�����ַ�������
		sprintf_s(a, _T("%d"), score2);
		sprintf_s(s, _T("%d"), score1);
		settextstyle(40, 0, _T("����"));
		outtextxy(500, 90, s);
		outtextxy(540, 90, ":");
		outtextxy(570, 90, a);
		putimage(ball_x, ball_y, &ball_mask, SRCAND);
		putimage(ball_x, ball_y, &ball, SRCPAINT);//��ʾС��
		if (ball_y > position_y1) {
			putimage(position_x1, position_y1, player1_width_����, player1_high_����, &����_player1_mask, player1_����_photo1_width, 0, SRCAND);
			putimage(position_x1, position_y1, player1_width_����, player1_high_����, &����_player1, player1_����_photo1_width, 0, SRCPAINT);
		}
		if (ball_y > position_y2) {
			putimage(position_x2, position_y2, player2_width_����, player2_high_����, &����_player2_mask, player2_����_photo1_width, 0, SRCAND);
			putimage(position_x2, position_y2, player2_width_����, player2_high_����, &����_player2, player2_����_photo1_width, 0, SRCPAINT);
		}//���������·�ʱ��չʾ��һ��ͼƬ
		if (ball_y <= position_y1) {
			putimage(position_x1, position_y1, player1_��_width, player1_��_high, &��_player1_mask, player1_����_photo1_width, 0, SRCAND);
			putimage(position_x1, position_y1, player1_��_width, player1_��_high, &��_player1, player1_����_photo1_width, 0, SRCPAINT);
		}
		if (ball_y <= position_y2) {
			putimage(position_x2, position_y2, player2_��_width, player2_��_high, &��_player2_mask, player2_����_photo1_width, 0, SRCAND);
			putimage(position_x2, position_y2, player2_��_width, player2_��_high, &��_player2, player2_����_photo1_width, 0, SRCPAINT);
		}//���������Ϸ�ʱ��չʾ�ڶ���ͼƬ
		
	}
	if (state == 3) {
		putimage(0, 0, &gameoverphoto);
	}//��״̬Ϊ3ʱ����ʾ����ͼƬ
	system("cls");//����
}
void updatewithoutinput() //����Ҫ����ĸ���
{
	char input;
	if (score1 == 7 || score2 == 7) {
		state = 3;
	}
	if (state == 1) {
		ball_x = ball_x + ball_vx;
		ball_y = ball_y + ball_vy;//����ƶ�
		position_y1 = position_y1 + vy_player1;
		position_y2 = position_y2 + vy_player2;//С�˵��ƶ�
		if (ball_y >= 610 && ball_x <= 380) {
			ball_vx = 0;
			ball_vy = 0;
			k = 0;
			score2++;
			ball_x = position_x1 + 110;
			isplayed = 1;
			ball_y = 560;
		}//С��ײ��ǽ�ں󷴵���ͬʱ��غ�ֹͣ�ƶ�
		if (ball_y >= 610 && ball_x >=560 ) {
			ball_vx = 0;
			ball_vy = 0;
			k = 0;
			j = 0;
			isplayed = 1;
			score1++;
			ball_x = position_x1+110 ;
			ball_y = 560;
		}//С��ײ��ǽ�ں󷴵���ͬʱ��غ�ֹͣ�ƶ�
		if (ball_x > Width - 50 || ball_x < 50) {
			ball_vx = -ball_vx;
		}//��������ǽ��ʱ����
		if (ball_y <= 0) {
			ball_vy = -ball_vy;
		}//����������ʱ����
		if (ball_y >= 610) {
			ball_y = 610;
			//ball_vx = 0;
		}//�������ذ�ʱ��ͣ��
		if (position_y1 > 520) {
			is_onfloot1 = 1;
			position_y1 = 520;
		}
		if (position_y2 > 520) {
			is_onfloot2 = 1;
			position_y2 = 520;
		}//С���䵽������ʱ��������
		vy_player1 = vy_player1 + G;
		vy_player2 = vy_player2 + G;//С���ܵ�����Ӱ��
		if (player1_����_photo1_width == player1_width_����)
			player1_����_photo2++;
		if (player1_����_photo2 == 5) {
			player1_����_photo1_width = 0;
			player1_����_photo2 = 0;
		}//��ʾplayer1��һ��ͼ�ĵڶ�����

		if (player2_����_photo1_width == player2_width_����)
			player2_����_photo2++;
		if (player2_����_photo2 == 5) {
			player2_����_photo1_width = 0;
			player2_����_photo2 = 0;
		}//��ʾ��player2��һ��ͼ�ĵڶ�����
		if (player1_����_photo2 != 0 && isplayed) {
			if (ball_y > position_y1 + 10 && ball_x > position_x1 + 55 && ball_x < position_x1 + 150 && ball_y < position_y1 + 145)
			{
				ball_x = ball_x + 10;
				ball_y = ball_y - 10;
				ball_vx = 10+rand()%10;
				ball_vy = -70;
				isplayed = 0;
			}
		}//��player1�Ӷ�����ʱ�����л����ж�
		if (player2_����_photo2 != 0 && !isplayed) {
			if (ball_y > position_y2 + 10 && ball_x > position_x2 && ball_x < position_x2 + 46 && ball_y < position_y2 + 145) {
				ball_x = ball_x + 10;
				ball_y = ball_y - 10;
				ball_vx = -10-rand()%10;
				ball_vy = -70;
				isplayed = 1;
			}
		}//��player2����ʱ�����л����ж�
		if (player1_����_photo2 != 0 && isplayed) {
			if (ball_y < position_y1 && ball_x > position_x1 && ball_x < position_x1 + 150 && ball_y > position_y1 - 50)
			{
				ball_x = ball_x + 10;
				ball_y = ball_y - 10;
				ball_vx = 10+rand()%10;
				ball_vy = -70;
				isplayed = 0;
			}
		}//��player1����ʱ�����л����ж�
		if (player2_����_photo2 != 0 && !isplayed) {
			if (ball_y < position_y2 && ball_x > position_x2 - 10 && ball_x < position_x2 + 130 && ball_y > position_y2 - 50) {
				ball_x = ball_x + 10;
				ball_y = ball_y - 10;
				ball_vx = -10-rand()%10;
				ball_vy = -70;
				isplayed = 1;
			}
		}//��player2����ʱ�����л����ж�
		if (ball_y < position_y2 && ball_x > position_x2 - 10 && ball_x < position_x2 + 130 && ball_y > position_y2 - 50||
			ball_y > position_y2 + 10 && ball_x > position_x2 && ball_x < position_x2 + 100 && ball_y < position_y2 + 145) {
			player2_����_photo1_width = player2_width_����;
			//player2_��_photo1_width = player2_��_width;
		}//�����Զ�����
		if (position_x1 <= 75) {
			position_x1 = 75;
		}
		if (position_x2 >= 905) {
			position_x2 = 905;
		}
		
		if (position_x1 >= 380) {
			position_x1 = 380;
		}
		if (position_x2 <= 560) {
			position_x2 = 560;
		}//����player1,player2���Χ
		if (position_x2 > ball_x+30) {
			position_x2 = position_x2 - vx_player2;
		}
		if (position_x2 <= ball_x-30) {
			position_x2 = position_x2 + vx_player2;
		}//���Ը�����ë��λ��
		if (k) {
			if (ball_vy < 15)
				ball_vy = ball_vy + 5;
		}//���������ë��ʼ�ܵ���������
		if (!k) {
			ball_x = position_x1 + 110;
		}
	}
	

	if (state == 2) {
		ball_x = ball_x + ball_vx;
		ball_y = ball_y + ball_vy;//����ƶ�
		position_y1 = position_y1 + vy_player1;
		position_y2 = position_y2 + vy_player2;//С�˵��ƶ�
		if (ball_y >= 610 && ball_x <= 380) {
			ball_vx = 0;
			ball_vy = 0;
			k = 0;
			score2++;
			ball_x = position_x1 + 110;
			isplayed = 1;
			ball_y = 560;
		}//С��ײ��ǽ�ں󷴵���ͬʱ��غ�ֹͣ�ƶ�
		if (ball_y >= 610 && ball_x >= 560) {
			ball_vx = 0;
			ball_vy = 0;
			k = 0;
			j = 0;
			isplayed = 1;
			score1++;
			ball_x = position_x1 + 110;
			ball_y = 560;
		}//С��ײ��ǽ�ں󷴵���ͬʱ��غ�ֹͣ�ƶ�
		if (ball_x > Width - 50 || ball_x < 50) {
			ball_vx = -ball_vx;
		}//��������ǽ��ʱ����
		if (ball_y <= 0) {
			ball_vy = -ball_vy;
		}//����������ʱ����
		if (ball_y >= 610) {
			ball_y = 610;
			//ball_vx = 0;
		}//�������ذ�ʱ��ͣ��
		if (position_y1 > 520) {
			is_onfloot1 = 1;
			position_y1 = 520;
		}
		if (position_y2 > 520) {
			is_onfloot2 = 1;
			position_y2 = 520;
		}//С���䵽������ʱ��������
		vy_player1 = vy_player1 + G;
		vy_player2 = vy_player2 + G;//С���ܵ�����Ӱ��
		if (player1_����_photo1_width == player1_width_����)
			player1_����_photo2++;
		if (player1_����_photo2 == 5) {
			player1_����_photo1_width = 0;
			player1_����_photo2 = 0;
		}//��ʾplayer1��һ��ͼ�ĵڶ�����

		if (player2_����_photo1_width == player2_width_����)
			player2_����_photo2++;
		if (player2_����_photo2 == 5) {
			player2_����_photo1_width = 0;
			player2_����_photo2 = 0;
		}//��ʾ��player2��һ��ͼ�ĵڶ�����
		if (player1_����_photo2 != 0 && isplayed) {
			if (ball_y > position_y1 + 10 && ball_x > position_x1 + 55 && ball_x < position_x1 + 150 && ball_y < position_y1 + 145)
			{
				ball_x = ball_x + 10;
				ball_y = ball_y - 10;
				ball_vx = 10 + rand() % 10;
				ball_vy = -70;
				isplayed = 0;
			}
		}//��player1�Ӷ�����ʱ�����л����ж�
		if (player2_����_photo2 != 0 && !isplayed) {
			if (ball_y > position_y2 + 10 && ball_x > position_x2 && ball_x < position_x2 + 46 && ball_y < position_y2 + 145) {
				ball_x = ball_x + 10;
				ball_y = ball_y - 10;
				ball_vx = -10 - rand() % 10;
				ball_vy = -70;
				isplayed = 1;
			}
		}//��player2����ʱ�����л����ж�
		if (player1_����_photo2 != 0 && isplayed) {
			if (ball_y < position_y1 && ball_x > position_x1 && ball_x < position_x1 + 150 && ball_y > position_y1 - 50)
			{
				ball_x = ball_x + 10;
				ball_y = ball_y - 10;
				ball_vx = 10 + rand() % 10;
				ball_vy = -70;
				isplayed = 0;
			}
		}//��player1����ʱ�����л����ж�
		if (player2_����_photo2 != 0 && !isplayed) {
			if (ball_y < position_y2 && ball_x > position_x2 - 10 && ball_x < position_x2 + 130 && ball_y > position_y2 - 50) {
				ball_x = ball_x + 10;
				ball_y = ball_y - 10;
				ball_vx = -10 - rand() % 10;;
				ball_vy = -70;
				isplayed = 1;
			}
		}//��player2����ʱ�����л����ж�
		if (position_x1 <= 75) {
			position_x1 = 75;
		}
		if (position_x2 >= 905) {
			position_x2 = 905;
		}

		if (position_x1 >= 380) {
			position_x1 = 380;
		}
		if (position_x2 <= 560) {
			position_x2 = 560;
		}//����player1,player2���Χ
		if (k) {
			if (ball_vy < 15)
				ball_vy = ball_vy + 5;
		}//���������ë��ʼ�ܵ���������
		if (!k) {
			ball_x = position_x1 + 110;
		}
	}
	if (state == 3) {
		if (_kbhit()) {
			input = _getch();
			if (input == '1') {
				state = 1;
			}
			if (input == '2') {
				state = 2;
			}
		}//����1�����뵥��ģʽ������2������˫��ģʽ
	}
}
void updatewithinput() {
	char input;
	if (state == 0) {
		score1 = score2 = 0;
		if (_kbhit()) {
			input = _getch();
			if (input == '1') {
				state = 1;
			}
			if (input == '2') {
				state = 2;
			}
		}//����1�����뵥��ģʽ������2������˫��ģʽ
	}
	if (state == 1) {
		if ((GetAsyncKeyState(0x41) & 0x8000))//a
			position_x1 -= vx_player1;
		if ((GetAsyncKeyState(0x44) & 0x8000))//d
			position_x1 += vx_player1;
		if ((GetAsyncKeyState(0x53) & 0x8000))//s
		{
			player1_����_photo1_width = player1_width_����;
			player1_��_photo1_width = player1_��_width;
			k = 1;


		}
		if ((GetAsyncKeyState(0x57) & 0x8000))//w
		{
			if (is_onfloot1 == 1) {
				is_onfloot1 = 0;
				vy_player1 = -40;
			}
		}
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000))//left
			position_x2 -= vx_player2;
		if ((GetAsyncKeyState(VK_RIGHT) & 0x8000))//right
			position_x2 += vx_player2;
	}
	if (state == 2) {
		if ((GetAsyncKeyState(0x41) & 0x8000))//a
			position_x1 -= vx_player1;
		if ((GetAsyncKeyState(0x44) & 0x8000))//d
			position_x1 += vx_player1;
		if ((GetAsyncKeyState(0x53) & 0x8000))//s
		{
			player1_����_photo1_width = player1_width_����;
			player1_��_photo1_width = player1_��_width;
			k = 1;
		}
		if ((GetAsyncKeyState(0x57) & 0x8000))//w
		{
			if (is_onfloot1 == 1) {
				is_onfloot1 = 0;
				vy_player1 = -40;
			}
		}
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000))//left
			position_x2 -= vx_player2;
		if ((GetAsyncKeyState(VK_RIGHT) & 0x8000))//right
			position_x2 += vx_player2;
		if ((GetAsyncKeyState(VK_UP) & 0x8000))//up
		{
			if (is_onfloot2 == 1) {
				is_onfloot2 = 0;
				vy_player2 = -40;
			}
		}
		if ((GetAsyncKeyState(VK_DOWN) & 0x8000))//down
		{
			player2_����_photo1_width = player2_width_����;
			player2_��_photo1_width = player2_��_width;
			j = 1;
		}
	}
	if (state == 3) {
		score1 = score2 = 0;
		if (_kbhit()) {
			input = _getch();
			if (input == '1') {
				state = 1;
			}
			if (input == '2') {
				state = 2;
			}
		}//����1�����뵥��ģʽ������2������˫��ģʽ
	}
}