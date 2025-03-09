#pragma once

typedef unsigned long HFont;	
typedef unsigned long FontDrawType_t;
enum EFontDrawType
{
	FONT_DRAW_DEFAULT = 0,
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE
};
class i_surface {
public:

	unsigned long font_create() {
		using original_fn = unsigned int(__thiscall*)(i_surface*);
		return (*(original_fn**)this)[66](this);
	}
	void set_font_glyph(unsigned long font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags) {
		using original_fn = void(__thiscall*)(i_surface*, unsigned long, const char*, int, int, int, int, int, int, int);
		return (*(original_fn**)this)[67](this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
	}

	void draw_line(int x1, int y1, int x2, int y2) {
		using original_fn = void(__thiscall*)(i_surface*, int, int, int, int);
		return (*(original_fn**)this)[15](this, x1, y1, x2, y2);
	}


	void draw_render_text(const wchar_t* text, int textLen) {
		using original_fn = void(__thiscall*)(i_surface*, const wchar_t*, int, int);
		return (*(original_fn**)this)[22](this, text, textLen, 0);
	}

	void set_text_color(int r, int g, int b, int a = 255) {
		using original_fn = void(__thiscall*)(i_surface*, int, int, int, int);
		return (*(original_fn**)this)[19](this, r, g, b, a);
	}

	void set_drawing_color(int r, int g, int b, int a = 255) {
		using original_fn = void(__thiscall*)(i_surface*, int, int, int, int);
		return (*(original_fn**)this)[11](this, r, g, b, a);
	}

	void draw_filled_rectangle(int x, int y, int w, int h) {
		using original_fn = void(__thiscall*)(i_surface*, int, int, int, int);
		return (*(original_fn**)this)[12](this, x, y, x + w, y + h);
	}
	void draw_outlined_rect(int x, int y, int w, int h) {
		using original_fn = void(__thiscall*)(i_surface*, int, int, int, int);
		return (*(original_fn**)this)[14](this, x, y, x + w, y + h);
	}
	void draw_text_pos(int x, int y) {
		using original_fn = void(__thiscall*)(i_surface*, int, int);
		return (*(original_fn**)this)[20](this, x, y);
	}
	void get_text_size(unsigned long font, const wchar_t* text, int& wide, int& tall) {
		using original_fn = void(__thiscall*)(i_surface*, unsigned long, const wchar_t*, int&, int&);
		return (*(original_fn**)this)[75](this, font, text, wide, tall);
	}

	void draw_text_font(unsigned long font) {
		using original_fn = void(__thiscall*)(i_surface*, unsigned long);
		return (*(original_fn**)this)[17](this, font);
	}
};