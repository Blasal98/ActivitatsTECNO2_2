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
	std::string id;
	std::string text;
	Color color;
};

struct Font {
	
	std::string id;
	std::string path;
	int size;

};

enum buttonType { PLAY, SOUND, EXIT, COUNT };



