#include"gameData.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	init();
	Picture picture = Picture(LoadGraph("ê¬ãÖ.png"));
	picture.set_size(155, 155);
	picture.setColor(0);
	auto picture2 = Picture(picture, std::vector<Picture::PARAMETE>{Picture::PARAMETE::HUNDLE});
	auto picture3 = Picture(picture, std::vector<Picture::PARAMETE>{Picture::PARAMETE::SIZE});

	picture2.show_offset(0, 0);

	auto k = Picture(picture3);
	class Picture f;
	f = k;
	col_1 a = col_1(10);
	a[1].second = k;
	WaitKey();

	return 0;
}
