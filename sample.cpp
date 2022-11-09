#include"Picture.cpp"
#include"Init.cpp"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	Init gameParams = Init();
	Picture fish = Picture(LoadGraph("hoge.png"));
	fish.set_size(100, 100);
	fish.show_offset(300, 0);
	fish.SetLimit(gameParams.windowSize_x, gameParams.windowSize_y);
	auto wall = Picture(fish.getHundle());
	wall.show(200,500);

	while (ScreenFlip() == 0 && ProcessMessage() == 0) {

		if (CheckHitKey(KEY_INPUT_RIGHT) != 0) {
			fish.move(10, 0);
			if (fish.IsCollision(wall))
				printfDx("HIT!!");
			fish.IsCollision(wall);
		}
		else if (CheckHitKey(KEY_INPUT_LEFT) != 0) {
			fish.move(-3, 0);
			if (fish.IsCollision(wall))
				printfDx("HIT!!");
		}
		else if (CheckHitKey(KEY_INPUT_D) != 0)
			fish.Delete();
		else if (CheckHitKey(KEY_INPUT_SPACE) != 0)
			break;
	}

	DxLib_End();
	return 0;
}

