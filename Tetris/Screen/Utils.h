#ifndef UTILS_H_
#define UTILS_H_
#define UI_WIDTH 30
#define UI_HEIGHT 35
#include <cstdio>
#include "GlobalValiable.h"

struct Position {
	int x;
	int y;
	Position(int x = 0, int y = 0) : x(x), y(y) {}

	Position(const Position& other) 
		: Position(other.x, other.y) {}
};

class Input {
	static INPUT_RECORD InputRecord[128];
	static DWORD Events;
	static bool evaluated;
	static bool gotMouseEvent;
	static bool gotKeyEvent;
	static Position mousePosition;
	static WORD vKeyCode;

	static void GetEvent()
	{
		evaluated = true;
		DWORD numEvents = 0;

		GetNumberOfConsoleInputEvents(GetStdHandle(STD_INPUT_HANDLE), &numEvents);
		if (!numEvents) return;

		ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), InputRecord, numEvents, &Events);
		for (int i = 0; i < Events; i++) {
			if (InputRecord[i].EventType == MOUSE_EVENT) {
				if (InputRecord[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
					COORD coord;
					coord.X = InputRecord[i].Event.MouseEvent.dwMousePosition.X;
					coord.Y = InputRecord[i].Event.MouseEvent.dwMousePosition.Y;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
					mousePosition.x = InputRecord[i].Event.MouseEvent.dwMousePosition.X;
					mousePosition.y = InputRecord[i].Event.MouseEvent.dwMousePosition.Y;
					gotMouseEvent = true;
				}
			}
			else if (InputRecord[i].EventType == KEY_EVENT) {
				if (InputRecord[i].Event.KeyEvent.bKeyDown) {
					vKeyCode = InputRecord[i].Event.KeyEvent.wVirtualKeyCode;
					gotKeyEvent = true;
				}
			}
		}
	}

public:

	static void EndOfFrame()
	{
		evaluated = false;
		gotMouseEvent = false;
		gotKeyEvent = false;
	}

	static void Initialize()
	{

		CONSOLE_CURSOR_INFO cci;
		cci.dwSize = 25;
		cci.bVisible = FALSE;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
		SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT );

		EndOfFrame();
	}
	static bool GetMouseEvent(Position& pos) {
		if (evaluated == false) GetEvent();

		if (gotMouseEvent == true) {
			pos = mousePosition;
			return true;
		}
		return false;}

	static bool GetKeyEvent(WORD& keyCode) {
		if (evaluated == false) GetEvent();

		if (gotKeyEvent == true) {
			keyCode = vKeyCode;
			return true;
		}
		return false;
	}
};
INPUT_RECORD Input::InputRecord[128];
DWORD Input::Events;

bool Input::evaluated = false;
bool Input::gotMouseEvent = false;
bool Input::gotKeyEvent = false;
Position Input::mousePosition{ -1, -1 };
WORD Input::vKeyCode{ 0 };

class Borland {

public:
	

	static int wherex()
	{
		CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
		return csbiInfo.dwCursorPosition.X;
	}
	static int wherey()
	{
		CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
		return csbiInfo.dwCursorPosition.Y;
	}
	static void gotoxy(int x, int y)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _COORD{ (SHORT)x, (SHORT)y });
	}
	static void gotoxy(const Position* pos)
	{
		if (!pos) return;
		gotoxy( (*pos).x, (*pos).y);
	}
	static void gotoxy(const Position& pos)
	{
		gotoxy( pos.x, pos.y);
	}
};

class Screen {
	int width;
	int height;
	char* canvas;
	char* tempCanvas;
	static Screen* instance;
	Screen(int width = 21, int height = 35)
		: width(width), height(height),
		canvas(new char[(width + 1)*height]),tempCanvas(new char[(width+1)*height])

	{
		memset(tempCanvas, '\xFA', (width + 1) * height);
		memset(&tempCanvas[(width + 1) * (height - 1)], '\xCD', width);
		tempCanvas[width + (height - 1) * (width + 1)] = '\0';
		Input::Initialize();
		for (int i = 0; i < height; i++) {
			tempCanvas[width + i * (width + 1)] = '\n';
			tempCanvas[width-1 + (i * (width+1))] = '\xBA';
			tempCanvas[i * (width + 1)] = '\xBA';
		}
	}
public:
	static Screen& getInstance() {
		if (instance == nullptr) {
			instance = new Screen();
		}
		return *instance;
	}

	~Screen() {
		if (instance) {
			delete[] canvas;
			delete[] tempCanvas;
			instance = nullptr;
		}
	}
	void tempDraw(const char* shape, int w, int h, const Position& pos)
	{
		if (!shape) return;
		for (int i = 0; i < w*h; i++)
		{
			if (shape[i] == '\xB1')
				tempCanvas[pos.x + (pos.y + (i / w)) * (width + 1) + i % w] = shape[i];
		}
	}

	void lineDown(int lineNumber)
	{
		for (int i = lineNumber; i>0; i--)
		{
			strncpy(&tempCanvas[(width + 1) * i], &tempCanvas[(width + 1) * (i - 1)], width);
		}
		memset(tempCanvas, '\xFA', width);
		tempCanvas[width + (height - 1) * (width + 1)] = '\0';
	}
	void draw(const char* shape, int w, int h, const Position& pos)
	{
		if (!shape) return;
		for (int i = 0; i < w * h; i++)
		{
			if (shape[i] == '\xB1')
				canvas[pos.x + (pos.y + (i / w)) * (width + 1) + i % w] = shape[i];
		}
	}

	void render()
	{
		tempCanvas[width + (height - 1) * (width + 1)] = '\0';
		canvas[width + (height - 1) * (width + 1)] = '\0';
		Borland::gotoxy(0, 0);
		cout << canvas;
	}

	void clear()
	{
		//memset(canvas, '\xFA', (width + 1)*height);
		strcpy(canvas, tempCanvas);
		canvas[width + (height - 1)*(width + 1)] = '\0';
	}
	int getHeight() const { return height;  }
	int getWidth() const { return width;  }
	int getSize() const { return ((width + 1) * height); } //스크린 사이즈 반환함수
	char getChar(const int pos)//지정위치 칸의 문자를 반환
	{
		return tempCanvas[pos];
	}
};

Screen* Screen::instance = nullptr;


class UI {
	char** canvas;
	static UI* instance;
	UI()
	{
		canvas = new char* [UI_HEIGHT];
		for (int i = 0; i < UI_HEIGHT; ++i)
			canvas[i] = new char[UI_WIDTH];

		for (int i = 0; i < UI_WIDTH; i++) {
			memset(canvas[i], ' ', UI_HEIGHT-1);
		}

		//canvas[UI_WIDTH - 1][UI_HEIGHT - 1] = '\0';
	}
public:
	static UI& getInstance() {
		if (instance == nullptr) {
			instance = new UI();
		}
		return *instance;
	}
	~UI() {
		if (instance) {
			delete[] canvas;
			instance = nullptr;
		}
	}
	void render()
	{
		canvas[UI_WIDTH - 1][UI_HEIGHT - 1] = '\0';

		for (int i = 0; i < UI_WIDTH; i++)
		{
			Borland::gotoxy(Screen::getInstance().getWidth()+5, i);
			cout << canvas[i];
		}
		clear();
	}

	void clear() {
		for (int i = 14; i < 18; i++) {
			memset(canvas[i], ' ', UI_HEIGHT);
		}
		for (int i = 20; i < 24; i++) {
			memset(canvas[i], ' ', UI_HEIGHT);
		}
		canvas[UI_WIDTH - 1][UI_HEIGHT - 1] = '\0';
	}
	void draw(const char* shape, int w, int h
	,const char* holdShape, int holdW,int holdH)
	{
		canvas[3] = " Key Description";
		canvas[4] = " \xC1 : Rotation Block";
		canvas[5] = " \xB4 : Left Move";
		canvas[6] = " \xC3 : Right Move";
		canvas[7] = " \xC2 : Down Move";
		canvas[8] = " Space Bar : Drop Block";
		canvas[9] = " 'a'Key : Hold Block";

		canvas[13] = "Next Block is ";
		for (int i = 0; i < w * h; i++)
		{
			if (shape[i] == '\xB1')
				canvas[14+i/w][i%w] = shape[i];
		}
		canvas[19] = "Hold Block is";
		for (int i = 0; i < holdW * holdH; i++)
		{
			if (holdShape[i] == '\xB1')
				canvas[20 + i / holdW][i % holdW] = holdShape[i];
		};

	
	}
};
UI* UI::instance = nullptr;
#endif 
