#include<DxLib.h>
#include<iostream>
#include"picture.cpp"
int PhotoSizeChange(int, double, double);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	ChangeWindowMode(TRUE);
	DxLib_Init();
	//LoadGraphScreen(0, 0, "hoge.png", TRUE);
	int Photo_Hundle = LoadGraph("hoge.png");

	//DrawRotaGraph(300, 0, 0.2, 0, Photo_Hundle, FALSE);
	int x_size = 0;
	int y_size = 0;
	GetGraphSize(Photo_Hundle, &x_size, &y_size);
	printfDx("x = %d   y = %d", x_size, y_size);
	x_size *= 0.1;
	y_size *= 0.1;
	DrawExtendGraph(200, 0, 200 + x_size , y_size , Photo_Hundle, FALSE);
	DrawExtendGraph(400, 0, 400 + x_size, y_size , Photo_Hundle, FALSE);
	
	
	int count = 0;
	while (ScreenFlip() == 0 && ProcessMessage() == 0) {
		WaitKey();
		if (CheckHitKey(KEY_INPUT_RIGHT) != 0)
			break;
		else if (CheckHitKey(KEY_INPUT_J) != 0) {
			DrawBox(200, 0, 200 + x_size, y_size, GetColor(0, 0, 0), TRUE);
		}
		else if (CheckHitKey(KEY_INPUT_K) != 0) {
			DrawExtendGraph(200, 0, 200 + x_size, y_size, Photo_Hundle, FALSE);
		}
		else {
			DrawString(0, count++ * 50, "No", GetColor(0xff, 0xff, 0xff));
		}
	}
	DxLib_End();
	return 0;
}

int PhotoSizeChange(int PhotoHundle,double x, double y) {
	if (PhotoHundle == -1)
		return -1;
	int x_size = 0;
	int y_size = 0;
	GetGraphSize(PhotoHundle, &x_size, &y_size);
	DrawExtendGraph(0, x_size * x, 0, y_size * y, PhotoHundle, TRUE);
}