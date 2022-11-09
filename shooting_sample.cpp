#include"gameData.h"
#include<random>

//#define EXE

auto fieldData = std::vector<col_1>(TATE_SIZE);
std::random_device random;
col_1 topCol = col_1(YOKO_SIZE);

void StepDown(col_1 topLine);
bool IsHit();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	init();

	for (int i = 0; i < fieldData.size(); i++) {
		fieldData[i] = col_1(YOKO_SIZE);
	}

	DrawBox(0, 0, windowSize_x, windowSize_y, GetColor(255, 255, 255), TRUE);
	FillAll(NON);
#ifndef EXE

	auto field = col_1(10);

	fieldData[TATE_SIZE - 1][(int)(YOKO_SIZE / 2)].first = MY_CHARACTOR;
	/*
	fieldData[0][4].first = ENEMY;
	display();
	WaitKey();

	field[2].first = ENEMY;
	StepDown(field);
	//set_1line(field, 0);

	display();
	WaitKey();

	for (int i = 0; i < 10; i++) {
		field[i].first = NON;
	}

	field[1].first = ENEMY;
	field[2].first = ENEMY;
	StepDown(field);
	display();
	fieldData[0][2].second.move(0, oneBlockSize_y);
*/

	while (!IsHit()) {
		for (int i = 0; i < YOKO_SIZE; i++) {
			field[i].first = NON;
		}

		int enemy_1 = ((unsigned int)random()) % YOKO_SIZE;
		field[enemy_1].first = ENEMY;
		while (true) {
			int enemy_2 = ((unsigned int)random()) % YOKO_SIZE;
			if (enemy_2 != enemy_1) {
				field[enemy_2].first = ENEMY;
				break;
			}
		}

		StepDown(field);
		Display();
		WaitKey();

		int pushKey = -1;
		for (int key : checkKeys) {
			if (CheckHitKey(key)) {
				pushKey = key;
				break;
			}
		}

		switch (pushKey) {
		case KEY_INPUT_SPACE: return 0;
		case KEY_INPUT_RIGHT: break;


		}

	}


#endif 

#ifdef EXE

	fieldData[TATE_SIZE - 1][4].first = MY_CHARACTOR;
	fieldData[0][4].first = ENEMY;
	std::random_device random;

	while (true) {
		/*
		for (int i = 0; i < YOKO_SIZE; i++) {
			if (fieldData[TATE_SIZE - 2][i].first == ENEMY &&
				fieldData[TATE_SIZE - 1][i].first == MY_CHARACTOR)
			{
				return 0;
			}
			else if (fieldData[TATE_SIZE - 1][i].first != MY_CHARACTOR) {
				fieldData[TATE_SIZE - 1][i] = fieldData[TATE_SIZE - 2][i];
			}
		}
*/
		for (int i = 0; i < YOKO_SIZE; i++) {
			if (fieldData[0][i].first != NON && fieldData[0][i].first != MY_CHARACTOR) {
				fieldData[0][i].second.move(0, oneBlockSize_y);
			}
		}

		for (int cnt = TATE_SIZE - 1; cnt > 0; cnt--) {
			for (int i = 0; i < YOKO_SIZE; i++) {
				if (fieldData[cnt][i].first != NON && fieldData[cnt][i].first != MY_CHARACTOR) {
					fieldData[cnt][i].second.move(0, oneBlockSize_y);
				}
			}
			set_1line(fieldData[cnt - 1], cnt);
		}

		for (int i = 0; i < YOKO_SIZE; i++) {
			if (fieldData[0][i].first != NON)
				fieldData[0][i].second.Delete();
			field[i].first = NON;
		}
		putsDx("");
		int enemy_1 = ((unsigned int)random()) % YOKO_SIZE;
		field[enemy_1].first = ENEMY;
		while (true) {
			int enemy_2 = ((unsigned int)random()) % YOKO_SIZE;
			if (enemy_2 != enemy_1) {
				field[enemy_2].first = ENEMY;
				break;
			}
		}
		set_1line(field, 0);


		WaitKey();

		Display();
		for (int i = 0; i < 10; i++) {
			fieldData[0][i].second.show_offset(oneBlockSize_x * i, 0);
		}

		if (CheckHitKey(KEY_INPUT_SPACE) != 0)
			break;
	}
#endif

	return 0;
}

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
		if (fieldData[TATE_SIZE - 1][i].first != NON && fieldData[TATE_SIZE - 1][i].first != MY_CHARACTOR) {
			fieldData[TATE_SIZE - 1][i].second.Delete();
		}
	}

	for (int cnt = TATE_SIZE - 2; cnt >= 0; cnt--) {
		for (int i = 0; i < YOKO_SIZE; i++) {
			if (fieldData[cnt][i].first != NON && fieldData[cnt][i].first != MY_CHARACTOR) {
				fieldData[cnt][i].second.move(0, oneBlockSize_y);
				if (fieldData[cnt + 1][i].first != MY_CHARACTOR)
					fieldData[cnt + 1][i] = fieldData[cnt][i];
			}
		}
	}
	set_1line(topLine, 0);
}

bool IsHit()
{
	for (int i = 0; i < YOKO_SIZE; i++) {
		if (fieldData[TATE_SIZE - 2][i].first == ENEMY &&
			fieldData[TATE_SIZE - 1][i].first == MY_CHARACTOR)
		{
			return true;
		}
	}
	return false;
}

