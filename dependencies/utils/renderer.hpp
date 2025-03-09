#pragma once
#include <string>
#include <array>
#include "../interfaces/interfaces.hpp"
#include "../../sdk/color.hpp"
#include <stdio.h>
#include <corecrt_wstring.h>
#define fw_dontcare         0
#define fw_thin             100
#define fw_extralight       200
#define fw_light            300
#define fw_normal           400
#define fw_medium           500
#define fw_semibold         600
#define fw_bold             700
#define fw_extrabold        800
#define fw_heavy            900

#define fw_ultralight       fw_extralight
#define fw_regular          fw_normal
#define fw_demibold         fw_semibold
#define fw_ultrabold        fw_extrabold
#define fw_black            fw_heavy
enum font_flags
{
	ff_none,
	ff_italic = 0x001,
	ff_underline = 0x002,
	ff_strikeout = 0x004,
	ff_symbol = 0x008,
	ff_antialias = 0x010,
	ff_gaussianblur = 0x020,
	ff_rotary = 0x040,
	ff_dropshadow = 0x080,
	ff_additive = 0x100,
	ff_outline = 0x200,
	ff_custom = 0x400,		// custom generated font - never fall back to asian compatibility mode
	ff_bitmap = 0x800,		// compiled bitmap font - no fallbacks
};

class c_renderer {
public:
	unsigned long watermark_font;
	unsigned long name_font;
	unsigned long name_font_big;
	unsigned long icon_font;
	unsigned long verdana;

public:
	void setup_fonts() {
		watermark_font = interfaces::surface->font_create();
		name_font = interfaces::surface->font_create();
		name_font_big = interfaces::surface->font_create();
		icon_font = interfaces::surface->font_create();
		verdana = interfaces::surface->font_create();

		interfaces::surface->set_font_glyph(watermark_font, "Tahoma", 12, 500, 0, 0, font_flags::ff_dropshadow);
		interfaces::surface->set_font_glyph(name_font, "Verdana", 12, 500, 0, 0, font_flags::ff_antialias | font_flags::ff_dropshadow);
		interfaces::surface->set_font_glyph(name_font_big, "Verdana", 15, 500, 0, 0, font_flags::ff_antialias | font_flags::ff_dropshadow);
		interfaces::surface->set_font_glyph(icon_font, "AstriumWep", 15, 300, 0, 0, font_flags::ff_antialias | font_flags::ff_dropshadow);
		interfaces::surface->set_font_glyph(verdana, "Veradana Bold", 15, 300, 0, 0, font_flags::ff_antialias | font_flags::ff_dropshadow);
		//interfaces::surface->set_font_glyph(icon_font, "Counter-Strike", 24, 400, 0, 0, font_flags::fontflag_antialias | font_flags::fontflag_dropshadow);

		printf("Render initialized!\n");
	}
	void draw_outline(int x, int y, int w, int h, color colour) {
		interfaces::surface->set_drawing_color(colour.r, colour.g, colour.b, colour.a);
		interfaces::surface->draw_outlined_rect(x, y, w, h);
	}
	void draw_rect(int x, int y, int w, int h, color color) {
		interfaces::surface->set_drawing_color(color.r, color.g, color.b, color.a);
		interfaces::surface->draw_outlined_rect(x, y, w, h);
	}
	void draw_filled_rect(int x, int y, int w, int h, color colour) {
		interfaces::surface->set_drawing_color(colour.r, colour.g, colour.b, colour.a);
		interfaces::surface->draw_filled_rectangle(x, y, w, h);
	}
	void draw_line(int x1, int y1, int x2, int y2, color colour) {
		interfaces::surface->set_drawing_color(colour.r, colour.g, colour.b, colour.a);
		interfaces::surface->draw_line(x1, y1, x2, y2);
	}
	void draw_text(int x, int y, unsigned long font, const wchar_t* string, color colour) {
		interfaces::surface->set_text_color(colour.r, colour.g, colour.b, colour.a);
		interfaces::surface->draw_text_font(font);
		interfaces::surface->draw_text_pos(x, y);
		interfaces::surface->draw_render_text(string, wcslen(string));
	}
	void draw_text(int x, int y, unsigned long font, std::string string, bool text_centered, color colour) {
		std::wstring text = std::wstring(string.begin(), string.end());
		const wchar_t* converted_text = text.c_str();

		int width, height;
		interfaces::surface->get_text_size(font, converted_text, width, height);

		interfaces::surface->set_text_color(colour.r, colour.g, colour.b, colour.a);
		interfaces::surface->draw_text_font(font);
		if (text_centered)
			interfaces::surface->draw_text_pos(x - (width / 2), y);
		else
			interfaces::surface->draw_text_pos(x, y);
		interfaces::surface->draw_render_text(converted_text, wcslen(converted_text));
	}
};

inline std::unique_ptr<c_renderer> g_renderer = std::make_unique<c_renderer>();