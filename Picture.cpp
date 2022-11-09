#include<DxLib.h>
#include<list>
#include<vector>
class Picture {

public :
	enum PARAMETE {
		HUNDLE,
		OFFSET,
		SIZE,
		LIMIT,
		COLOR,
		ALL
	};


private:
	int hundle = -1;
	int offset_x = 0;
	int offset_y = 0;
	int size_x = 0;
	int size_y = 0;
	int limit_x = -1;
	int limit_y = -1;
	bool deleteFlag = true;
	unsigned int color = GetColor(0, 0, 0);
	const std::list<PARAMETE> allParams =
	{ HUNDLE , OFFSET , SIZE , LIMIT , COLOR};
	


public : 
	Picture(int hundle) {
		this->hundle = hundle;
		GetGraphSize(this->hundle, &size_x, &size_y);
	};
	Picture() {
		this->hundle = -1;
	}

	Picture(const Picture& other) {
		this->hundle = other.hundle;
		this->offset_x = other.offset_x;
		this->offset_y = other.offset_y;
		this->size_x = other.size_x;
		this->size_y = other.size_y;
		this->limit_x = other.limit_x;
		this->limit_y = other.limit_y;

		this->color = other.color;
		
	}

	
	Picture& operator=(const Picture& other){
		this->hundle = other.hundle;
		this->offset_x = other.offset_x;
		this->offset_y = other.offset_y;
		this->size_x = other.size_x;
		this->size_y = other.size_y;
		this->limit_x = other.limit_x;
		this->limit_y = other.limit_y;

		this->color = other.color;
		return *this;
	}

	Picture(const Picture& other,std::vector<PARAMETE> notCopy) {
		auto copyParams = this->allParams;
		for (auto e : notCopy) {
			copyParams.remove(e);
		}
		for (auto e : copyParams) {
			switch (e) {
			case HUNDLE: this->hundle = other.hundle; break;
			case OFFSET: this->offset_x = other.offset_x;
				this->offset_y = other.offset_y;
				break;
			case SIZE: this->size_x = other.size_x;
				this->size_y = other.size_y;
				break;
			case LIMIT: this->limit_x = other.limit_x;
				this->limit_y = other.limit_y;
				break;
			case COLOR: this->color = other.color; break;
			}
		}
	}

	void set_size(int x, int y) {
		size_x = x;
		size_y = y;
	}

	void show(int x_size, int y_size) {
		if (!deleteFlag) {
			putsDx("‰æ‘œ‚Í‚·‚Å‚É•\Ž¦‚³‚ê‚Ä‚¢‚Ü‚·");
			return;
		}
		DrawExtendGraph(offset_x, offset_y, offset_x + x_size, offset_y + y_size, hundle, FALSE);
		this->size_x = x_size;
		size_y = y_size;
		deleteFlag = false;
	}

	void show_offset(int off_x, int off_y) {
		if (limit_x < 0 ||
			(this->size_x < limit_x - off_x && this->offset_x + off_x > 0))
			this->offset_x = off_x;

		if (limit_y < 0 ||
			(this->size_y < limit_y - off_y && this->offset_y + off_y > 0))
			this->offset_y = off_y;

		DrawExtendGraph(offset_x, offset_y, offset_x + size_x, offset_y + size_y, hundle, FALSE);
	}

	void Delete() {
		DrawBox(offset_x, offset_y, offset_x + size_x, offset_y + size_y, color, TRUE);
		deleteFlag = true;
	}
	void Delete(unsigned int color) {
		DrawBox(offset_x, offset_y, size_x, size_y, color, TRUE);
		deleteFlag = true;
	}

	void move(int x, int y) {
		Delete();
		show_offset(offset_x + x, offset_y + y);
	}

	void setColor(unsigned int color) {
		this->color = color;
	}

	void SetLimit(int x, int y) {
		limit_x = x;
		limit_y = y;
	}

	void setHundle(int newHundle) {
		this->hundle = newHundle;
	}

	int getHundle() { return hundle; }

	bool IsCollision(Picture other) {

		bool result = (offset_x > other.offset_x) && (offset_x < other.offset_x + other.size_x);

		if (!result) {
			result = (offset_x + size_x > other.offset_x) && (offset_x + size_x < other.offset_x + other.size_x);
		}

		if (result) {
			result = (offset_y > other.offset_y) && (offset_y < other.offset_y + other.size_y);
			if (!result)
				result = (offset_y + size_y > other.offset_y) && (offset_y + size_y < other.offset_y + other.size_y);
		}
		return result;
	}
};