// Screen.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#define _CRT_SECURE_NO_WARNINGS
#include "Utils.h"
#include "GlobalValiable.h"

class GameObject {
protected:
	char*		shape;
	int			width;
	int			height;
	Position	pos;
	Screen&		screen;

public:
	GameObject(const char* shape, int width, int height, const Position& pos = Position{ 0, 0 } )
		: height(height), width(width), 
		shape(nullptr), pos(pos), 
		screen(Screen::getInstance()) {
		if (!shape || strlen(shape) == 0 || width == 0 || height == 0)
		{
			this->shape = new char[1];
			this->shape[0] = 'x';
			width = 1;
			height = 1;
		} else {
			this->shape = new char[width*height];
			strncpy(this->shape, shape, width*height);
		}
		this->width = width;
		this->height = height;
	}

	virtual ~GameObject() {
		if (shape) { delete[] shape; }
		width = 0, height = 0;
	}

	void setShape(const char* shape) {
		if (!shape) return;
		strncpy(this->shape, shape, width*height);
	}
	char* getShape() {
		return shape;
	}

	void setPos(int x, int y) { this->pos.x = x; this->pos.y = y; }

	Position& getPos() { return pos; }
		
	virtual void draw() 
	{
		screen.draw(shape, width, height, pos);
	}

	int changePosToScreenPos()
	{
		return pos.x + (pos.y) * (screen.getWidth() + 1);
	}
	int getWidth()
	{
		return width;
	}
	int getHeight() {
		return height;
	}
	virtual void update() 
	{	
	}
};

class Block : public GameObject {	

	vector<string> sprites;
	int current;

public:
	Block(vector<string>& sprites, int w, int h, 
		const Position& pos = Position{ 0,0 } )
		: sprites(sprites), current(0), 
		GameObject(sprites[current].c_str(), w, h, pos) {}
	
	bool moveDown()//블럭을 쌓을지 안쌓을지
	{
		Screen& screen = Screen::getInstance();
		int screenPos = changePosToScreenPos();
		for (int i = 0; i < width*height; i++)
		{
			int underPos = screenPos + ((screen.getWidth() + 1) * ((i/width)+1)) + (i % width);//아래칸
			if (shape[i] != '\xB1') 
				continue;
			else
			{
				if (screen.getChar(underPos) == '\xCD'||
					screen.getChar(underPos) == '\xB1')//블럭아래가 쌓여있거나 맵의끝인경우
				{
					return false;
				}
			}
		}
		return true;
	}
	void removeBlock()
	{
		for (int y = 0; y < screen.getHeight()-1; y++)
		{
			for (int x = 1; x < screen.getWidth()-1; x++)
			{
				if (screen.getChar(y * (screen.getWidth() + 1) + x) != '\xB1') break;//그줄에 한개라도 블럭이아니면 브레이크

				if (x == screen.getWidth() - 2)
				{
					screen.lineDown(y);
					removeLineNum++;
					return;
				}
			}
		}
	}
	bool bulidBlock()
	{
		srand((unsigned int)time(NULL));
		Screen& screen = Screen::getInstance();
		if (!moveDown()) {
			
			screen.tempDraw(shape, width, height, pos);
			getPos().y = 0;
			getPos().x = screen.getWidth() / 2;
			blockNum = nextBlockNum;
			nextBlockNum = rand() % 7;
			hold = false;
			return true;
		}
		return false;
	}
	bool moveRight() {
		int screenPos = changePosToScreenPos();
		for (int i = 0; i < width * height; i++)
		{
			int rightPos = screenPos + ((screen.getWidth() + 1)* ((i / width))) + (i % width)+1;//오른쪽칸
			if (shape[i] != '\xB1')
				continue;
			else
			{
				if (screen.getChar(rightPos) == '\xB1'|| screen.getChar(rightPos)=='\xBA')//블럭오른쪽에 쌓여진 블럭이있음
				{
					return false;
				}
			}
		}
		return true;
	}
	bool moveLeft() {
		int screenPos = changePosToScreenPos();
		for (int i = 0; i < width * height; i++)
		{
			int leftPos = screenPos + ((screen.getWidth() + 1) * ((i / width))) + (i % width) - 1;//오른쪽칸
			if (shape[i] != '\xB1')
				continue;
			else
			{
				if (screen.getChar(leftPos) == '\xB1'|| screen.getChar(leftPos) == '\xBA')//블럭왼쪽에 쌓여진 블럭이있음
				{
					return false;
				}
			}
		}
		return true;
	}
	void holdBlock() {
		if (hold) return;
		getPos().y = 0;
		getPos().x = screen.getWidth() / 2;
		int tempNum = blockNum;
		blockNum = holdBlockNum;
		holdBlockNum = tempNum;
		hold = true;

	}
	void update() {
		WORD keyCode;
		removeBlock();
		if (bulidBlock()) return;

		if (Input::GetKeyEvent(keyCode)) {
			switch (keyCode) {
			case VK_RIGHT:
				if(moveRight())
				getPos().x++;
				break;

			case VK_LEFT:
				if(moveLeft())
				getPos().x--;
				break;

			case VK_UP:
				current = (current + 1) % sprites.size();
				setShape(sprites[current].c_str());
				break;
				break;

			case VK_DOWN:
				if (moveDown())
				getPos().y++;
				break;

			case 0x41: //'a'
				holdBlock();
				break;

			case 0x44: //'d'
				current = (current + 3) % sprites.size();
				setShape(sprites[current].c_str());
				break;
			}
		}
		if(moveDown())
		getPos().y++;
		
	}
};

int main()
{
	UI& ui = UI::getInstance();
	Screen&	 screen = Screen::getInstance();
	vector<GameObject *> gameObjects;

	string mode{ "mode con cols="
		+ to_string(screen.getWidth()+10+UI_HEIGHT)
		+ " lines=" + to_string(screen.getHeight() + 5) };
	system(mode.c_str());
	system("chcp 437");

	auto block = new Block{ blockShape1, 3,3,
		Position{screen.getWidth()/2, 0} };
	auto block2 = new Block{ blockShape2 , 3,3,
		Position{screen.getWidth() / 2, 0} };
	auto block3 = new Block{ blockShape3, 3,3,
		Position{screen.getWidth() / 2, 0} };
	auto block4 = new Block{ blockShape4 , 3,3,
		Position{screen.getWidth() / 2, 0} };
	auto block5 = new Block{ blockShape5, 3,3,
		Position{screen.getWidth() / 2, 0} };
	auto block6 = new Block{ blockShape6 , 3,3,
		Position{screen.getWidth() / 2, 0} };
	auto block7 = new Block{ blockShape7, 4, 4,
		Position{ screen.getWidth() / 2, 0 } };

	gameObjects.push_back(block);
	gameObjects.push_back(block2);
	gameObjects.push_back(block3);
	gameObjects.push_back(block4);
	gameObjects.push_back(block5);
	gameObjects.push_back(block6);
	gameObjects.push_back(block7);
	
	auto obj = gameObjects[blockNum];
	screen.clear(); screen.render();
	while (true)
	{
		screen.clear();
	
		obj = gameObjects[blockNum];
		obj->update();
		obj->draw();	

		screen.render();	
		ui.draw(gameObjects[nextBlockNum]->getShape(), gameObjects[nextBlockNum]->getWidth(), gameObjects[nextBlockNum]->getHeight()
		, gameObjects[holdBlockNum]->getShape(), gameObjects[holdBlockNum]->getWidth(), gameObjects[holdBlockNum]->getHeight());
		ui.render();
		Sleep(150);

		Input::EndOfFrame();		
	}

	return 0;
}