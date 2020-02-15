/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) Aadalie 2019
 * Authors:
 *  - Sorunome
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <string.h>
#include <Gamebuino-Meta.h>
#include "common-hal/analogio/AnalogOut.h"

namespace Gamebuino_Meta {
extern const uint16_t buttonsIconsData[];
}

extern "C" {
void common_hal_analogio_analogout_construct(analogio_analogout_obj_t* self, const mcu_pin_obj_t *pin);
void common_hal_analogio_analogout_set_value(analogio_analogout_obj_t *self,
        uint16_t value);
void* gbptr = nullptr;
}

analogio_analogout_obj_t sound_pin;
Gamebuino_Meta::Gamebuino* ptr = nullptr;
Gamebuino_Meta::Gamebuino* gb() {
	if (gbptr) {
		return (Gamebuino_Meta::Gamebuino*)gbptr;
	}
	gbptr = new Gamebuino_Meta::Gamebuino;
	((Gamebuino_Meta::Gamebuino*)gbptr)->begin();
	
	// set sound to low
	hri_dac_write_CTRLA_ENABLE_bit(DAC, false);
	common_hal_analogio_analogout_construct(&sound_pin, &pin_PA02);
	common_hal_analogio_analogout_set_value(&sound_pin, 0);
	return (Gamebuino_Meta::Gamebuino*)gbptr;
}

extern "C" {

void gamebuino_meta_reset() {
	/*
	if (gbptr) {
		delete ((Gamebuino_Meta::Gamebuino*)gbptr);
	}*/
	gbptr = nullptr;
}

bool gamebuino_meta_collide_rect_rect(const int16_t x1, const int16_t y1, const int16_t w1, const int16_t h1, const int16_t x2, const int16_t y2, const int16_t w2, const int16_t h2) {
	return gb()->collide.rectRect((int16_t)x1, (int16_t)y1, (int16_t)w1, (int16_t)h1, (int16_t)x2, (int16_t)y2, (int16_t)w2, (int16_t)h2);
}

bool gamebuino_meta_collide_point_rect(const int16_t pointX, const int16_t pointY, const uint16_t rectX, const uint16_t rectY, const uint16_t rectW, const uint16_t rectH) {
	return gb()->collide.pointRect((int16_t)pointX, (int16_t)pointY, (uint16_t)rectX, (uint16_t)rectY, (uint16_t)rectW, (uint16_t)rectH);
}

bool gamebuino_meta_collide_circle_circle(const int16_t centerX1, const int16_t centerY1, const int16_t r1, const int16_t centerX2, const int16_t centerY2, const int16_t r2) {
	return gb()->collide.circleCircle((int16_t)centerX1, (int16_t)centerY1, (int16_t)r1, (int16_t)centerX2, (int16_t)centerY2, (int16_t)r2);
}

bool gamebuino_meta_collide_point_circle(const int16_t pointX, const int16_t pointY, const int16_t centerX, const int16_t centerY, const int16_t r) {
	return gb()->collide.pointCircle((int16_t)pointX, (int16_t)pointY, (int16_t)centerX, (int16_t)centerY, (int16_t)r);
}

void gamebuino_meta_display_clear() {
	gb()->display.clear();
}
void gamebuino_meta_display_clear_color(const uint16_t c) {
	gb()->display.clear((Gamebuino_Meta::Color)c);
}
void gamebuino_meta_display_fill() {
	gb()->display.fill();
}
void gamebuino_meta_display_fill_color(const uint16_t c) {
	gb()->display.fill((Gamebuino_Meta::Color)c);
}
void gamebuino_meta_display_print_int(const int str) {
	gb()->display.print((int)str);
}
void gamebuino_meta_display_print_int_xy(const int16_t x, const int16_t y, const int str) {
	gb()->display.print(x, y, (int)str);
}
void gamebuino_meta_display_print(const char* str) {
	gb()->display.print(str);
}
void gamebuino_meta_display_print_xy(const int16_t x, const int16_t y, const char* str) {
	gb()->display.print(x, y, str);
}
void gamebuino_meta_display_println_int(const int str) {
	gb()->display.println((int)str);
}
void gamebuino_meta_display_println_int_xy(const int16_t x, const int16_t y, const int str) {
	gb()->display.println(x, y, (int)str);
}
void gamebuino_meta_display_println(const char* str) {
	gb()->display.println(str);
}
void gamebuino_meta_display_println_xy(const int16_t x, const int16_t y, const char* str) {
	gb()->display.println(x, y, str);
}
void gamebuino_meta_display_draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
	gb()->display.drawLine(x0, y0, x1, y1);
}
void gamebuino_meta_display_draw_rect(int16_t x, int16_t y, int16_t w, int16_t h) {
	gb()->display.drawRect(x, y, w, h);
}
void gamebuino_meta_display_fill_rect(int16_t x, int16_t y, int16_t w, int16_t h) {
	gb()->display.fillRect(x, y, w, h);
}
void gamebuino_meta_display_draw_pixel(int16_t x, int16_t y) {
	gb()->display.drawPixel(x, y);
}
void gamebuino_meta_display_draw_pixel_color(int16_t x, int16_t y, uint16_t c) {
	gb()->display.drawPixel(x, y, (Gamebuino_Meta::Color)c);
}
void gamebuino_meta_display_draw_circle(int16_t x, int16_t y, int16_t r) {
	gb()->display.drawCircle(x, y, r);
}
void gamebuino_meta_display_fill_circle(int16_t x, int16_t y, int16_t r) {
	gb()->display.fillCircle(x, y, r);
}
void gamebuino_meta_display_draw_triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
	gb()->display.drawTriangle(x0, y0, x1, y1, x2, y2);
}
void gamebuino_meta_display_fill_triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
	gb()->display.fillTriangle(x0, y0, x1, y1, x2, y2);
}
void gamebuino_meta_display_draw_round_rect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t r) {
	gb()->display.drawRoundRect(x0, y0, w, h, r);
}
void gamebuino_meta_display_fill_round_rect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t r) {
	gb()->display.fillRoundRect(x0, y0, w, h, r);
}
void gamebuino_meta_display_set_color(uint16_t c) {
	gb()->display.setColor((Gamebuino_Meta::Color)c);
}
void gamebuino_meta_display_draw_bitmap(int8_t x, int8_t y, const uint8_t *bitmap) {
	gb()->display.drawBitmap(x, y, bitmap);
}
void gamebuino_meta_display_draw_bitmap_scale(int8_t x, int8_t y, const uint8_t *bitmap, int8_t scale) {
	gb()->display.drawBitmap(x, y, bitmap, scale);
}
void gamebuino_meta_display_draw_image(int8_t x, int8_t y, const uint8_t *buf) {
	gb()->display.drawImage(x, y, buf);
}
void gamebuino_meta_display_set_font_size(uint8_t s) {
	gb()->display.setFontSize(s);
}

void gamebuino_meta_lights_clear() {
	gb()->lights.clear();
}
void gamebuino_meta_lights_clear_color(const uint16_t c) {
	gb()->lights.clear((Gamebuino_Meta::Color)c);
}
void gamebuino_meta_lights_fill() {
	gb()->lights.fill();
}
void gamebuino_meta_lights_fill_color(const uint16_t c) {
	gb()->lights.fill((Gamebuino_Meta::Color)c);
}
void gamebuino_meta_lights_draw_pixel(int16_t x, int16_t y) {
	gb()->lights.drawPixel(x, y);
}
void gamebuino_meta_lights_draw_pixel_color(int16_t x, int16_t y, uint16_t c) {
	gb()->lights.drawPixel(x, y, (Gamebuino_Meta::Color)c);
}
void gamebuino_meta_lights_fill_rect(int16_t x, int16_t y, int16_t w, int16_t h) {
	gb()->lights.fillRect(x, y, w, h);
}
void gamebuino_meta_lights_set_color(uint16_t c) {
	gb()->lights.setColor((Gamebuino_Meta::Color)c);
}

const uint8_t gbm_BUTTON_DOWN = (const uint8_t)BUTTON_DOWN;
const uint8_t gbm_BUTTON_LEFT = (const uint8_t)BUTTON_LEFT;
const uint8_t gbm_BUTTON_RIGHT = (const uint8_t)BUTTON_RIGHT;
const uint8_t gbm_BUTTON_UP = (const uint8_t)BUTTON_UP;
const uint8_t gbm_BUTTON_A = (const uint8_t)BUTTON_A;
const uint8_t gbm_BUTTON_B = (const uint8_t)BUTTON_B;
const uint8_t gbm_BUTTON_MENU = (const uint8_t)BUTTON_MENU;
const uint8_t gbm_BUTTON_HOME = (const uint8_t)BUTTON_HOME;
bool gamebuino_meta_buttons_pressed(uint8_t b) {
	return gb()->buttons.pressed((Gamebuino_Meta::Button)b);
}
bool gamebuino_meta_buttons_released(uint8_t b) {
	return gb()->buttons.released((Gamebuino_Meta::Button)b);
}
bool gamebuino_meta_buttons_held(uint8_t b, uint16_t time) {
	return gb()->buttons.held((Gamebuino_Meta::Button)b, time);
}
bool gamebuino_meta_buttons_repeat(uint8_t b, uint16_t time) {
	return gb()->buttons.repeat((Gamebuino_Meta::Button)b, time);
}
uint16_t gamebuino_meta_buttons_time_held(uint8_t b) {
	return gb()->buttons.timeHeld((Gamebuino_Meta::Button)b);
}

void gamebuino_meta_gui_keyboard(const char* title, char* text, uint8_t length) {
	gb()->gui.keyboard(title, text, length);
}
uint8_t gamebuino_meta_gui_menu(const char* title, const char** items, uint8_t length) {
	return gb()->gui.menu(title, items, length);
}
void gamebuino_meta_gui_popup(const char* text, uint8_t duration) {
	gb()->gui.popup(text, duration);
}

void gamebuino_meta_begin() {
    gb();
}
bool gamebuino_meta_update() {
	return gb()->update();
}
void gamebuino_meta_wait_for_update() {
	gb()->waitForUpdate();
}
void gamebuino_meta_update_display() {
	return gb()->updateDisplay();
}
void gamebuino_meta_set_frame_rate(uint8_t fps) {
	gb()->setFrameRate(fps);
}
uint8_t gamebuino_meta_get_cpu_load(){
	return gb()->getCpuLoad();
}
void gamebuino_meta_get_default_name(char* str) {
	gb()->getDefaultName(str);
}
void gamebuino_meta_titlescreen() {
	const char version[] = "Gamebuino\nCircuitpython\nVersion 0.0.5";
	if (PM->RCAUSE.bit.POR) {
		gb()->startScreen();
	}
	gb()->display.clear();
	gb()->display.println(version);
	gb()->display.println("\n\x15: START");
	gb()->display.setCursorY(gb()->display.getCursorY()+1);
	gb()->display.println("\x16: EXIT");
	Image buttonsIcons = Gamebuino_Meta::Image(Gamebuino_Meta::buttonsIconsData);
	while (1) {
		while (gb()->update());
		//blinking A button icon
		if((gb()->frameCount%8) >= 4){
			buttonsIcons.setFrame(1); //button A pressed
		} else {
			buttonsIcons.setFrame(0); //button A released
		}
		uint8_t x = gb()->display.width() - buttonsIcons.width();
		uint8_t y = gb()->display.height() - buttonsIcons.height();
		gb()->display.drawImage(x, y, buttonsIcons);
		if (gb()->buttons.pressed(BUTTON_A)) {
			break;
		}
		if (gb()->buttons.pressed(BUTTON_B)) {
			gb()->bootloader.loader();
			break;
		}
	}
	gb()->display.clear();
	gb()->display.println(version);
	gb()->display.println("\nPlease add a python file...");
	gb()->updateDisplay();
}

} // extern "C"
