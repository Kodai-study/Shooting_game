#include"gameData.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	init();
	extern std::vector<col_1> fieldData;
	extern bool isMove;
#pragma region INIT

#pragma endregion

	/* 自機が弾に当たるまで、メインループ */
	while (!IsHit()) {

		windowSize_x;

		for (int i = 0; i < YOKO_SIZE; i++) {
			newCol[i].first = NON;
		}
		int enemy_1 = ((unsigned int)random()) % YOKO_SIZE;
		newCol[enemy_1].first = ENEMY;
		while (true) {
			int enemy_2 = ((unsigned int)random()) % YOKO_SIZE;
			if (enemy_2 != enemy_1) {
				newCol[enemy_2].first = ENEMY;
				break;
			}
		}
		StepDown(newCol);
		Display();
		//WaitKey();

		isMove = false;
		for (int key : moveKeys) {
			if (CheckHitKey(key)) {
				CharaStep(key);
				break;
			}
			if (CheckHitKey(KEY_INPUT_SPACE)) {
				fieldData[0][0].first = NON;
				return 0;
			}
		}
		if (!isMove)
			CharaStep(NON);

		WaitTimer(500);

	}
	WaitKey();
	return 0;
}


