#define TATE_SIZE 10
#define YOKO_SIZE 10
#define ENEMY_kazu
#ifndef GAMEDATA_H
#define GAMEDATA_H
#include "Picture.cpp"
#include<vector>
#include<random>

enum KIND_OF_FIELD {

	NON,
	ENEMY,
	MY_CHARACTOR,
	CHARACTOR_RIGHTWARD,
	CHARACTOR_LEFTWARD,
	KIND_SIZE//ç≈å„Ç…à íuÇ≥ÇπÇƒÇ®Ç≠

};

enum DIRECTION {
	RIGHT,
	LEFT
};

typedef std::vector<std::pair<KIND_OF_FIELD, Picture>> col_1;

const int moveKeys[] = { KEY_INPUT_RIGHT,KEY_INPUT_LEFT,KEY_INPUT_SPACE };


void FillAll(enum KIND_OF_FIELD num);
void Display(void);
void set_1line(col_1 write_data, int datas_index);
void Fill_1Line(enum KIND_OF_FIELD num, int datas_line_number);
bool IsHit();
void StepDown(col_1 topLine);
void CharaStep(int pushKey);

namespace {
	int windowSize_x;
	int windowSize_y;
	VECTOR charaPosition;
	int oneBlockSize_x;
	int oneBlockSize_y;
	col_1 newCol = col_1(YOKO_SIZE);
	std::random_device random;
	int fieldPattern[KIND_SIZE] = {0};
}

void init(void);

#endif