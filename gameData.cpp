#include"gameData.h"

auto fieldData = std::vector<col_1>(TATE_SIZE);
bool isMove;


void Display() {

	for (int j = 0; j < TATE_SIZE; j++) {
		for (int i = 0; i < YOKO_SIZE; i++) {
			if (fieldData[j][i].first != NON && fieldData[j][i].second.getHundle() == -1) {
				Picture picture = Picture(fieldPattern[fieldData[j][i].first]);
				picture.set_size(oneBlockSize_x - 10, oneBlockSize_y - 10);
				picture.setColor(0xffffffff);
				fieldData[j][i].second = picture;
				fieldData[j][i].second.show_offset(oneBlockSize_x * i, oneBlockSize_y * j);
			}
		}
	}
}

void FillAll(KIND_OF_FIELD num) {

	for (int i = 0; i < TATE_SIZE; i++) {
		for (int j = 0; j < YOKO_SIZE; j++) {
			fieldData[i][j].first = num;
		}
	}
}

void set_1line(col_1 write_data, int datas_index) {

	for (int i = 0; i < YOKO_SIZE; i++) {
		if (write_data[i].first >= KIND_SIZE) {
			printfDx("%d は定義されていないフィールドの種類です。\n", write_data[i]);
			continue;
		}
		fieldData[datas_index][i] = write_data[i];
	}
}


void Fill_1Line(enum KIND_OF_FIELD num, int line_number) {

	int max = YOKO_SIZE;
	for (int i = 0; i < max; i++)
		fieldData[line_number][i].first = num;
}

void StepDown(col_1 topLine) {
	for (int i = 0; i < 10; i++) {
		if (fieldData[TATE_SIZE - 1][i].first == ENEMY) {
			//(fieldData[TATE_SIZE - 1][i].first != NON && fieldData[TATE_SIZE - 1][i].first != MY_CHARACTOR) {
			fieldData[TATE_SIZE - 1][i].second.Delete();
		}
	}

	for (int cnt = TATE_SIZE - 2; cnt >= 0; cnt--) {
		for (int i = 0; i < YOKO_SIZE; i++) {
			if (fieldData[cnt][i].first == ENEMY) {

				//if (fieldData[cnt][i].first != NON && fieldData[cnt][i].first != MY_CHARACTOR) {
				fieldData[cnt][i].second.move(0, oneBlockSize_y);
			}
			if (fieldData[cnt + 1][i].first != MY_CHARACTOR &&
				fieldData[cnt + 1][i].first != CHARACTOR_LEFTWARD &&
				fieldData[cnt + 1][i].first != CHARACTOR_RIGHTWARD)
				fieldData[cnt + 1][i] = fieldData[cnt][i];

		}
	}
	set_1line(topLine, 0);
}

bool IsHit()
{
	for (int i = 0; i < YOKO_SIZE; i++) {
		if (fieldData[TATE_SIZE - 2][i].first == ENEMY &&
			(fieldData[TATE_SIZE - 1][i].first == MY_CHARACTOR ||
				fieldData[TATE_SIZE - 1][i].first == CHARACTOR_RIGHTWARD ||
				fieldData[TATE_SIZE - 1][i].first == CHARACTOR_LEFTWARD))
		{
			return true;
		}
	}
	return false;
}

void CharaStep(int pushKey)
{
	auto cp = charaPosition;
	
	switch (pushKey) {

	case NON:
		if (fieldData[cp.y][cp.x].first != MY_CHARACTOR) {
			fieldData[cp.y][cp.x].first = MY_CHARACTOR;
			fieldData[cp.y][cp.x].second.setHundle(fieldPattern[MY_CHARACTOR]);
			fieldData[cp.y][cp.x].second.move(0, 0);
		}
		break;
	case KEY_INPUT_RIGHT:
		if (cp.x < YOKO_SIZE - 1) {
			//fieldData[cp.y][cp.x + 1] =
			//	fieldData[cp.y][cp.x];
			auto rightWard = Picture(fieldData[cp.y][cp.x].second, std::vector<Picture::PARAMETE>(Picture::HUNDLE));
			//rightWard.setColor = 
			rightWard.setHundle(fieldPattern[CHARACTOR_RIGHTWARD]);
			fieldData[cp.y][cp.x + 1].second = rightWard;
			fieldData[cp.y][cp.x + 1].first = CHARACTOR_RIGHTWARD;
			fieldData[cp.y][cp.x] = std::pair<KIND_OF_FIELD, Picture>(NON, Picture());
			fieldData[cp.y][cp.x + 1].second.move(oneBlockSize_x, 0);
			charaPosition.x += 1;
			isMove = true;
		}
		break;

	case KEY_INPUT_LEFT:
		if (cp.x > 0) {
			//fieldData[cp.y][cp.x + 1] =
			//	fieldData[cp.y][cp.x];
			auto rightWard = Picture(fieldData[cp.y][cp.x].second, std::vector<Picture::PARAMETE>(Picture::HUNDLE));
			//rightWard.setColor = 
			rightWard.setHundle(fieldPattern[CHARACTOR_LEFTWARD]);
			fieldData[cp.y][cp.x - 1].second = rightWard;
			fieldData[cp.y][cp.x - 1].first = CHARACTOR_LEFTWARD;
			fieldData[cp.y][cp.x] = std::pair<KIND_OF_FIELD, Picture>(NON, Picture());
			fieldData[cp.y][cp.x - 1].second.move(-oneBlockSize_x, 0);
			charaPosition.x -= 1;
			isMove = true;
		}
		break;
	}
}

void init() {

	charaPosition = VECTOR();
	charaPosition.x = 4;
	charaPosition.y = YOKO_SIZE - 1;
	fieldData = std::vector<col_1>(TATE_SIZE);
	newCol = col_1(YOKO_SIZE);
	std::random_device random;
	isMove = false;
	
	RECT windowSize;
	ChangeWindowMode(TRUE);
	DxLib_Init();
	GetDrawArea(&windowSize);
	windowSize_x = windowSize.right - windowSize.left;
	windowSize_y = windowSize.bottom - windowSize.top;
	oneBlockSize_x = windowSize_x / TATE_SIZE;
	oneBlockSize_y = windowSize_y / YOKO_SIZE;
	fieldPattern[ENEMY] = LoadGraph("青球.png");
	fieldPattern[MY_CHARACTOR] = LoadGraph("自機_正面.png");
	fieldPattern[CHARACTOR_RIGHTWARD] = LoadGraph("自機_右向き.png");
	fieldPattern[CHARACTOR_LEFTWARD] = LoadGraph("自機_左向き.png");

	for (int i = 1; i < KIND_SIZE; i++) {
		if (fieldPattern[i] == -1)
			printfDx("%d個めの画像が読み取れませんでした", i);
	}

	for (unsigned int i = 0; i < fieldData.size(); i++) {
		fieldData[i] = col_1(YOKO_SIZE);
	}

	DrawBox(0, 0, windowSize_x, windowSize_y, GetColor(255, 255, 255), TRUE);
	FillAll(NON);

	fieldData[charaPosition.y][charaPosition.x].first = MY_CHARACTOR;


}