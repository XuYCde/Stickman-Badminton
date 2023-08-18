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
#define Width 1080//定义画面长宽
#define G 5//定义重力加速度
int position_x1,position_y1;
int position_x2, position_y2;//小人1和小人2的位置
int ball_x, ball_y;//球的位置
int vx_player1, vy_player1;
int vx_player2, vy_player2;//小人1和小人2的速度
int ball_vx, ball_vy;
int is_onfloot1 = 1;
int is_onfloot2 = 1;//两火柴人的跳跃判定
int player1_width_发球 = 130;//角色1发球图片中第一个动作的宽度
int player1_high_发球 = 152;//角色1发球图片高度
int player2_width_发球 = 130;//角色2发球图片中第一个动作的宽度
int player2_high_发球 = 154;//角色1发球图片高度
int player1_拍_width = 144;//角色1拍图片宽度
int player1_拍_high = 172;//角色1拍图片高度
int player2_拍_width = 121;//角色2拍图片宽度
int player2_拍_high = 182;//角色2拍图片高度
int player1_拍 = 0;
int player2_拍 = 0;
int player1_拍_photo1_width=0;
int player2_拍_photo1_width=0;
int player1_发球_photo1_width = 0;
int player2_发球_photo1_width = 0;//控制图片动画放映
int isplayed = 1;
int k = 0;
int j = 0;//是否已发球
int score1 = 0;
int score2 = 0;//定义游戏分数
int state = 0;//判定游戏状态
static int player1_发球_photo2 = 0;
static int player2_发球_photo2 = 0;
IMAGE beginphoto;//定义开始图片
IMAGE bkphoto;//定义背景图片
IMAGE 发球_player1,发球_player1_mask;//定义角色一的发球动作
IMAGE 发球_player2_mask, 发球_player2;//定义角色二的发球动作
IMAGE ball_mask, ball;//定义羽毛球
IMAGE 拍_player1_mask;
IMAGE 拍_player1;//定义角色一拍球动作
IMAGE 拍_player2_mask;
IMAGE 拍_player2;//定义角色二拍球动作
IMAGE gameoverphoto;//定义游戏结束图片

void startup();//设定初始量
void show();//展示图像
void updatewithoutinput();//无需输入的更新
void updatewithinput();//需要输入的更新
void main() {
	initgraph(Width, High);
	startup();//数据的初始化
	while (1){
		show();//画面显示
		updatewithoutinput();
		updatewithinput();
	
	}
	_getch();
}
void startup()//数据的初始化 
{
	mciSendString(_T("open D:\\游戏素材\\bk0.mp3 alias bkmusic"), NULL, 0, NULL);
	mciSendString(_T("play bkmusic"), NULL, 0, NULL);//添加背景音乐
	loadimage(&beginphoto, _T("D:\\游戏素材\\begin_photo.png"));//导入开始图片
	loadimage(&bkphoto, _T("D:\\游戏素材\\bkphoto.jpg"));//导入背景图片
	loadimage(&发球_player1_mask, _T("D:\\游戏素材\\发球_player1_mask.bmp"));
	loadimage(&发球_player1, _T("D:\\游戏素材\\发球_player1.bmp"));//导入角色一发球图片
	loadimage(&发球_player2_mask, _T("D:\\游戏素材\\发球_player2_mask.bmp"));
	loadimage(&发球_player2, _T("D:\\游戏素材\\发球_player2.bmp"));//导入角色二发球图片
	loadimage(&ball_mask, _T("D:\\游戏素材\\ball_mask.bmp"));
	loadimage(&ball, _T("D:\\游戏素材\\ball.bmp"));//导入羽毛球的图片
	loadimage(&拍_player1_mask, _T("D:\\游戏素材\\拍_player1_mask.bmp"));
	loadimage(&拍_player1, _T("D:\\游戏素材\\拍_player1.bmp"));//导入角色一拍球图片
	loadimage(&拍_player2_mask, _T("D:\\游戏素材\\拍_player2_mask.bmp"));
	loadimage(&拍_player2, _T("D:\\游戏素材\\拍_player2.bmp"));//导入角色二拍球图片
	loadimage(&gameoverphoto, _T("D:\\游戏素材\\end.jpg"));//加载图像素材
	position_x1 = 100;
	position_y1 = 520;
	position_x2 = 750;
	position_y2 = 520;//初始化两个小人位置
	ball_x = position_x1+110;
	ball_y = 560;//初始化羽毛球位置
	vx_player1 = 20;
	vy_player1 = 0;
	vx_player2 = 20;
	vy_player2 = 0;//初始化火柴人的移动速度
	ball_vx = 0;
	ball_vy = 0;//初始化羽毛球速度
	
	
}
void show() {
	
	if (state == 0) {
		putimage(0, 0, &beginphoto);//当状态为0时，显示开始图片
	}
	if (state == 1) {
		putimage(0, 0, &bkphoto);//当状态为一时，显示背景图片
		outtextxy(500, 30, "比分");//在画面上方显示比分二字
		TCHAR s[20];//定义字符串数组，用来表示比分
		TCHAR a[20];//定义字符串数组，用来显示比分
		sprintf_s(a, _T("%d"), score2);
		sprintf_s(s, _T("%d"), score1);
		settextstyle(40, 0, _T("宋体"));
		outtextxy(500, 90, s);
		outtextxy(540, 90, ":");
		outtextxy(570, 90, a);//显示比分
		putimage(ball_x, ball_y, &ball_mask, SRCAND);
		putimage(ball_x, ball_y, &ball, SRCPAINT);//显示羽毛球
		if (ball_y > position_y1) {
			putimage(position_x1, position_y1, player1_width_发球, player1_high_发球, &发球_player1_mask, player1_发球_photo1_width, 0, SRCAND);
			putimage(position_x1, position_y1, player1_width_发球, player1_high_发球, &发球_player1, player1_发球_photo1_width, 0, SRCPAINT);
		}
		if (ball_y > position_y2) {
			putimage(position_x2, position_y2, player2_width_发球, player2_high_发球, &发球_player2_mask, player2_发球_photo1_width, 0, SRCAND);
			putimage(position_x2, position_y2, player2_width_发球, player2_high_发球, &发球_player2, player2_发球_photo1_width, 0, SRCPAINT);
		}//当球在人下方时，展示第一张图片
		if (ball_y <= position_y1) {
			putimage(position_x1, position_y1, player1_拍_width, player1_拍_high, &拍_player1_mask, player1_发球_photo1_width, 0, SRCAND);
			putimage(position_x1, position_y1, player1_拍_width, player1_拍_high, &拍_player1, player1_发球_photo1_width, 0, SRCPAINT);
		}
		if (ball_y <= position_y2) {
			putimage(position_x2, position_y2, player2_拍_width, player2_拍_high, &拍_player2_mask, player2_发球_photo1_width, 0, SRCAND);
			putimage(position_x2, position_y2, player2_拍_width, player2_拍_high, &拍_player2, player2_发球_photo1_width, 0, SRCPAINT);
		}//当球在人上方时，展示第二张图片

	}
	
	if (state == 2) {
		
		putimage(0, 0, &bkphoto);
		outtextxy(500, 30, "比分");
		TCHAR s[20];//定义字符串数组
		TCHAR a[20];//定义字符串数组
		sprintf_s(a, _T("%d"), score2);
		sprintf_s(s, _T("%d"), score1);
		settextstyle(40, 0, _T("宋体"));
		outtextxy(500, 90, s);
		outtextxy(540, 90, ":");
		outtextxy(570, 90, a);
		putimage(ball_x, ball_y, &ball_mask, SRCAND);
		putimage(ball_x, ball_y, &ball, SRCPAINT);//显示小球
		if (ball_y > position_y1) {
			putimage(position_x1, position_y1, player1_width_发球, player1_high_发球, &发球_player1_mask, player1_发球_photo1_width, 0, SRCAND);
			putimage(position_x1, position_y1, player1_width_发球, player1_high_发球, &发球_player1, player1_发球_photo1_width, 0, SRCPAINT);
		}
		if (ball_y > position_y2) {
			putimage(position_x2, position_y2, player2_width_发球, player2_high_发球, &发球_player2_mask, player2_发球_photo1_width, 0, SRCAND);
			putimage(position_x2, position_y2, player2_width_发球, player2_high_发球, &发球_player2, player2_发球_photo1_width, 0, SRCPAINT);
		}//当球在人下方时，展示第一张图片
		if (ball_y <= position_y1) {
			putimage(position_x1, position_y1, player1_拍_width, player1_拍_high, &拍_player1_mask, player1_发球_photo1_width, 0, SRCAND);
			putimage(position_x1, position_y1, player1_拍_width, player1_拍_high, &拍_player1, player1_发球_photo1_width, 0, SRCPAINT);
		}
		if (ball_y <= position_y2) {
			putimage(position_x2, position_y2, player2_拍_width, player2_拍_high, &拍_player2_mask, player2_发球_photo1_width, 0, SRCAND);
			putimage(position_x2, position_y2, player2_拍_width, player2_拍_high, &拍_player2, player2_发球_photo1_width, 0, SRCPAINT);
		}//当球在人上方时，展示第二张图片
		
	}
	if (state == 3) {
		putimage(0, 0, &gameoverphoto);
	}//当状态为3时，显示结束图片
	system("cls");//清屏
}
void updatewithoutinput() //不需要输入的更新
{
	char input;
	if (score1 == 7 || score2 == 7) {
		state = 3;
	}
	if (state == 1) {
		ball_x = ball_x + ball_vx;
		ball_y = ball_y + ball_vy;//球的移动
		position_y1 = position_y1 + vy_player1;
		position_y2 = position_y2 + vy_player2;//小人的移动
		if (ball_y >= 610 && ball_x <= 380) {
			ball_vx = 0;
			ball_vy = 0;
			k = 0;
			score2++;
			ball_x = position_x1 + 110;
			isplayed = 1;
			ball_y = 560;
		}//小球撞到墙壁后反弹，同时落地后停止移动
		if (ball_y >= 610 && ball_x >=560 ) {
			ball_vx = 0;
			ball_vy = 0;
			k = 0;
			j = 0;
			isplayed = 1;
			score1++;
			ball_x = position_x1+110 ;
			ball_y = 560;
		}//小球撞到墙壁后反弹，同时落地后停止移动
		if (ball_x > Width - 50 || ball_x < 50) {
			ball_vx = -ball_vx;
		}//当球碰到墙壁时反弹
		if (ball_y <= 0) {
			ball_vy = -ball_vy;
		}//球碰到顶部时反弹
		if (ball_y >= 610) {
			ball_y = 610;
			//ball_vx = 0;
		}//球碰到地板时，停滞
		if (position_y1 > 520) {
			is_onfloot1 = 1;
			position_y1 = 520;
		}
		if (position_y2 > 520) {
			is_onfloot2 = 1;
			position_y2 = 520;
		}//小人落到地面上时才能起跳
		vy_player1 = vy_player1 + G;
		vy_player2 = vy_player2 + G;//小人受到重力影响
		if (player1_发球_photo1_width == player1_width_发球)
			player1_发球_photo2++;
		if (player1_发球_photo2 == 5) {
			player1_发球_photo1_width = 0;
			player1_发球_photo2 = 0;
		}//显示player1第一张图的第二部分

		if (player2_发球_photo1_width == player2_width_发球)
			player2_发球_photo2++;
		if (player2_发球_photo2 == 5) {
			player2_发球_photo1_width = 0;
			player2_发球_photo2 = 0;
		}//显示第player2第一张图的第二部分
		if (player1_发球_photo2 != 0 && isplayed) {
			if (ball_y > position_y1 + 10 && ball_x > position_x1 + 55 && ball_x < position_x1 + 150 && ball_y < position_y1 + 145)
			{
				ball_x = ball_x + 10;
				ball_y = ball_y - 10;
				ball_vx = 10+rand()%10;
				ball_vy = -70;
				isplayed = 0;
			}
		}//当player1挥动球拍时，进行击打判定
		if (player2_发球_photo2 != 0 && !isplayed) {
			if (ball_y > position_y2 + 10 && ball_x > position_x2 && ball_x < position_x2 + 46 && ball_y < position_y2 + 145) {
				ball_x = ball_x + 10;
				ball_y = ball_y - 10;
				ball_vx = -10-rand()%10;
				ball_vy = -70;
				isplayed = 1;
			}
		}//当player2挑球时，进行击打判定
		if (player1_发球_photo2 != 0 && isplayed) {
			if (ball_y < position_y1 && ball_x > position_x1 && ball_x < position_x1 + 150 && ball_y > position_y1 - 50)
			{
				ball_x = ball_x + 10;
				ball_y = ball_y - 10;
				ball_vx = 10+rand()%10;
				ball_vy = -70;
				isplayed = 0;
			}
		}//当player1挑球时，进行击打判定
		if (player2_发球_photo2 != 0 && !isplayed) {
			if (ball_y < position_y2 && ball_x > position_x2 - 10 && ball_x < position_x2 + 130 && ball_y > position_y2 - 50) {
				ball_x = ball_x + 10;
				ball_y = ball_y - 10;
				ball_vx = -10-rand()%10;
				ball_vy = -70;
				isplayed = 1;
			}
		}//当player2挑球时，进行击打判定
		if (ball_y < position_y2 && ball_x > position_x2 - 10 && ball_x < position_x2 + 130 && ball_y > position_y2 - 50||
			ball_y > position_y2 + 10 && ball_x > position_x2 && ball_x < position_x2 + 100 && ball_y < position_y2 + 145) {
			player2_发球_photo1_width = player2_width_发球;
			//player2_拍_photo1_width = player2_拍_width;
		}//电脑自动挥拍
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
		}//限制player1,player2活动范围
		if (position_x2 > ball_x+30) {
			position_x2 = position_x2 - vx_player2;
		}
		if (position_x2 <= ball_x-30) {
			position_x2 = position_x2 + vx_player2;
		}//电脑跟踪羽毛球位置
		if (k) {
			if (ball_vy < 15)
				ball_vy = ball_vy + 5;
		}//当发球后，羽毛球开始受到重力作用
		if (!k) {
			ball_x = position_x1 + 110;
		}
	}
	

	if (state == 2) {
		ball_x = ball_x + ball_vx;
		ball_y = ball_y + ball_vy;//球的移动
		position_y1 = position_y1 + vy_player1;
		position_y2 = position_y2 + vy_player2;//小人的移动
		if (ball_y >= 610 && ball_x <= 380) {
			ball_vx = 0;
			ball_vy = 0;
			k = 0;
			score2++;
			ball_x = position_x1 + 110;
			isplayed = 1;
			ball_y = 560;
		}//小球撞到墙壁后反弹，同时落地后停止移动
		if (ball_y >= 610 && ball_x >= 560) {
			ball_vx = 0;
			ball_vy = 0;
			k = 0;
			j = 0;
			isplayed = 1;
			score1++;
			ball_x = position_x1 + 110;
			ball_y = 560;
		}//小球撞到墙壁后反弹，同时落地后停止移动
		if (ball_x > Width - 50 || ball_x < 50) {
			ball_vx = -ball_vx;
		}//当球碰到墙壁时反弹
		if (ball_y <= 0) {
			ball_vy = -ball_vy;
		}//球碰到顶部时反弹
		if (ball_y >= 610) {
			ball_y = 610;
			//ball_vx = 0;
		}//球碰到地板时，停滞
		if (position_y1 > 520) {
			is_onfloot1 = 1;
			position_y1 = 520;
		}
		if (position_y2 > 520) {
			is_onfloot2 = 1;
			position_y2 = 520;
		}//小人落到地面上时才能起跳
		vy_player1 = vy_player1 + G;
		vy_player2 = vy_player2 + G;//小人受到重力影响
		if (player1_发球_photo1_width == player1_width_发球)
			player1_发球_photo2++;
		if (player1_发球_photo2 == 5) {
			player1_发球_photo1_width = 0;
			player1_发球_photo2 = 0;
		}//显示player1第一张图的第二部分

		if (player2_发球_photo1_width == player2_width_发球)
			player2_发球_photo2++;
		if (player2_发球_photo2 == 5) {
			player2_发球_photo1_width = 0;
			player2_发球_photo2 = 0;
		}//显示第player2第一张图的第二部分
		if (player1_发球_photo2 != 0 && isplayed) {
			if (ball_y > position_y1 + 10 && ball_x > position_x1 + 55 && ball_x < position_x1 + 150 && ball_y < position_y1 + 145)
			{
				ball_x = ball_x + 10;
				ball_y = ball_y - 10;
				ball_vx = 10 + rand() % 10;
				ball_vy = -70;
				isplayed = 0;
			}
		}//当player1挥动球拍时，进行击打判定
		if (player2_发球_photo2 != 0 && !isplayed) {
			if (ball_y > position_y2 + 10 && ball_x > position_x2 && ball_x < position_x2 + 46 && ball_y < position_y2 + 145) {
				ball_x = ball_x + 10;
				ball_y = ball_y - 10;
				ball_vx = -10 - rand() % 10;
				ball_vy = -70;
				isplayed = 1;
			}
		}//当player2挑球时，进行击打判定
		if (player1_发球_photo2 != 0 && isplayed) {
			if (ball_y < position_y1 && ball_x > position_x1 && ball_x < position_x1 + 150 && ball_y > position_y1 - 50)
			{
				ball_x = ball_x + 10;
				ball_y = ball_y - 10;
				ball_vx = 10 + rand() % 10;
				ball_vy = -70;
				isplayed = 0;
			}
		}//当player1挑球时，进行击打判定
		if (player2_发球_photo2 != 0 && !isplayed) {
			if (ball_y < position_y2 && ball_x > position_x2 - 10 && ball_x < position_x2 + 130 && ball_y > position_y2 - 50) {
				ball_x = ball_x + 10;
				ball_y = ball_y - 10;
				ball_vx = -10 - rand() % 10;;
				ball_vy = -70;
				isplayed = 1;
			}
		}//当player2挑球时，进行击打判定
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
		}//限制player1,player2活动范围
		if (k) {
			if (ball_vy < 15)
				ball_vy = ball_vy + 5;
		}//当发球后，羽毛球开始受到重力作用
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
		}//按‘1’进入单人模式，按‘2’进入双人模式
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
		}//按‘1’进入单人模式，按‘2’进入双人模式
	}
	if (state == 1) {
		if ((GetAsyncKeyState(0x41) & 0x8000))//a
			position_x1 -= vx_player1;
		if ((GetAsyncKeyState(0x44) & 0x8000))//d
			position_x1 += vx_player1;
		if ((GetAsyncKeyState(0x53) & 0x8000))//s
		{
			player1_发球_photo1_width = player1_width_发球;
			player1_拍_photo1_width = player1_拍_width;
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
			player1_发球_photo1_width = player1_width_发球;
			player1_拍_photo1_width = player1_拍_width;
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
			player2_发球_photo1_width = player2_width_发球;
			player2_拍_photo1_width = player2_拍_width;
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
		}//按‘1’进入单人模式，按‘2’进入双人模式
	}
}