#pragma once

struct VEC2 {
	int x;
	int y;
}; 

struct RECT {
	int x;
	int y;
	int w;
	int h;
};

struct Color {
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};

struct Text {
	std::string text;
	std::string id;
	Color color;
};

struct Font {
	int size;
	std::string path;
	std::string id;

};

enum buttonType { PLAY, SOUND, EXIT, COUNT };



