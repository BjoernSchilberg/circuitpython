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

#include "py/nlr.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "py/binary.h"
#include "py/gc.h"
#include "py/objint.h"
#include <string.h>

bool gamebuino_meta_collide_rect_rect(const int16_t, const int16_t, const int16_t, const int16_t, const int16_t, const int16_t, const int16_t, const int16_t);
bool gamebuino_meta_collide_point_rect(const int16_t, const int16_t, const uint16_t, const uint16_t, const uint16_t, const uint16_t);
bool gamebuino_meta_collide_circle_circle(const int16_t, const int16_t, const int16_t, const int16_t, const int16_t, const int16_t);
bool gamebuino_meta_collide_point_circle(const int16_t, const int16_t, const int16_t, const int16_t, const int16_t);

STATIC mp_obj_t gbm_collide_rect_rect(size_t n_args, const mp_obj_t *args) {
    return mp_obj_new_bool(gamebuino_meta_collide_rect_rect(
        mp_obj_get_int(args[0]),
        mp_obj_get_int(args[1]),
        mp_obj_get_int(args[2]),
        mp_obj_get_int(args[3]),
        mp_obj_get_int(args[4]),
        mp_obj_get_int(args[5]),
        mp_obj_get_int(args[6]),
        mp_obj_get_int(args[7])
    ));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gbm_collide_rect_rect_obj, 8, 8, gbm_collide_rect_rect);

STATIC mp_obj_t gbm_collide_point_rect(size_t n_args, const mp_obj_t *args) {
    return mp_obj_new_bool(gamebuino_meta_collide_point_rect(
        mp_obj_get_int(args[0]),
        mp_obj_get_int(args[1]),
        mp_obj_get_int(args[2]),
        mp_obj_get_int(args[3]),
        mp_obj_get_int(args[4]),
        mp_obj_get_int(args[5])
    ));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gbm_collide_point_rect_obj, 6, 6, gbm_collide_point_rect);

STATIC mp_obj_t gbm_collide_circle_circle(size_t n_args, const mp_obj_t *args) {
    return mp_obj_new_bool(gamebuino_meta_collide_circle_circle(
        mp_obj_get_int(args[0]),
        mp_obj_get_int(args[1]),
        mp_obj_get_int(args[2]),
        mp_obj_get_int(args[3]),
        mp_obj_get_int(args[4]),
        mp_obj_get_int(args[5])
    ));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gbm_collide_circle_circle_obj, 6, 6, gbm_collide_circle_circle);

STATIC mp_obj_t gbm_collide_point_circle(size_t n_args, const mp_obj_t *args) {
    return mp_obj_new_bool(gamebuino_meta_collide_point_circle(
        mp_obj_get_int(args[0]),
        mp_obj_get_int(args[1]),
        mp_obj_get_int(args[2]),
        mp_obj_get_int(args[3]),
        mp_obj_get_int(args[4])
    ));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gbm_collide_point_circle_obj, 5, 5, gbm_collide_point_circle);

STATIC const mp_map_elem_t gbm_collide_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR_rectRect), (mp_obj_t)&gbm_collide_rect_rect_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_pointRect), (mp_obj_t)&gbm_collide_point_rect_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_circleCircle), (mp_obj_t)&gbm_collide_circle_circle_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_pointCircle), (mp_obj_t)&gbm_collide_point_circle_obj },
};
STATIC MP_DEFINE_CONST_DICT (
    mp_dict_gamebuino_meta_collide,
    gbm_collide_table
);
const mp_obj_module_t mp_module_gamebuino_meta_collide = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_dict_gamebuino_meta_collide,
};

void gamebuino_meta_display_clear(void);
void gamebuino_meta_display_clear_color(const uint16_t);
void gamebuino_meta_display_fill(void);
void gamebuino_meta_display_fill_color(const uint16_t);
void gamebuino_meta_display_print_int(const int str);
void gamebuino_meta_display_print_int_xy(const int16_t, const int16_t, const int str);
void gamebuino_meta_display_print(const char* str);
void gamebuino_meta_display_print_xy(const int16_t, const int16_t, const char* str);
void gamebuino_meta_display_println_int(const int str);
void gamebuino_meta_display_println_int_xy(const int16_t, const int16_t, const int str);
void gamebuino_meta_display_println(const char* str);
void gamebuino_meta_display_println_xy(const int16_t, const int16_t, const char* str);
void gamebuino_meta_display_draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
void gamebuino_meta_display_draw_rect(int16_t x, int16_t y, int16_t w, int16_t h);
void gamebuino_meta_display_fill_rect(int16_t x, int16_t y, int16_t w, int16_t h);
void gamebuino_meta_display_draw_pixel(int16_t, int16_t);
void gamebuino_meta_display_draw_pixel_color(int16_t, int16_t, int16_t);
void gamebuino_meta_display_draw_circle(int16_t, int16_t, int16_t);
void gamebuino_meta_display_fill_circle(int16_t, int16_t, int16_t);
void gamebuino_meta_display_draw_triangle(int16_t, int16_t, int16_t, int16_t, int16_t, int16_t);
void gamebuino_meta_display_fill_triangle(int16_t, int16_t, int16_t, int16_t, int16_t, int16_t);
void gamebuino_meta_display_draw_round_rect(int16_t, int16_t, int16_t, int16_t, int16_t);
void gamebuino_meta_display_fill_round_rect(int16_t, int16_t, int16_t, int16_t, int16_t);
void gamebuino_meta_display_set_color(uint16_t);
void gamebuino_meta_display_draw_bitmap(int8_t, int8_t, const uint8_t*);
void gamebuino_meta_display_draw_bitmap_scale(int8_t, int8_t, const uint8_t*, int8_t);
void gamebuino_meta_display_draw_image(int8_t, int8_t, const uint8_t*);
void gamebuino_meta_display_set_font_size(uint8_t);

STATIC mp_obj_t gbm_loader(void) {
    ((void(*)(void))(*((uint32_t*)0x3FF4)))();
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(gbm_loader_obj, gbm_loader);

STATIC mp_obj_t gbm_display_clear(size_t n_args, const mp_obj_t *args) {
    if (n_args == 0) {
        gamebuino_meta_display_clear();
    } else {
        gamebuino_meta_display_clear_color(mp_obj_get_int(args[0]));
    }
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gbm_display_clear_obj, 0, 1, gbm_display_clear);

STATIC mp_obj_t gbm_display_fill(size_t n_args, const mp_obj_t *args) {
    if (n_args == 0) {
        gamebuino_meta_display_fill();
    } else {
        gamebuino_meta_display_fill_color(mp_obj_get_int(args[0]));
    }
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gbm_display_fill_obj, 0, 1, gbm_display_fill);

STATIC mp_obj_t gbm_display_print(size_t n_args, const mp_obj_t *args) {
    if (n_args == 3) {
        if (MP_OBJ_IS_INT(args[2])) {
            gamebuino_meta_display_print_int_xy(mp_obj_get_int(args[0]), mp_obj_get_int(args[1]), mp_obj_get_int(args[2]));
        } else {
            gamebuino_meta_display_print_xy(mp_obj_get_int(args[0]), mp_obj_get_int(args[1]), mp_obj_str_get_str(args[2]));
        }
    } else if (n_args == 1) {
        if (MP_OBJ_IS_INT(args[0])) {
            gamebuino_meta_display_print_int(mp_obj_get_int(args[0]));
        } else {
            gamebuino_meta_display_print(mp_obj_str_get_str(args[0]));
        }
    }
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gbm_display_print_obj, 1, 3, gbm_display_print);

STATIC mp_obj_t gbm_display_println(size_t n_args, const mp_obj_t *args) {
    if (n_args == 3) {
        if (MP_OBJ_IS_INT(args[2])) {
            gamebuino_meta_display_println_int_xy(mp_obj_get_int(args[0]), mp_obj_get_int(args[1]), mp_obj_get_int(args[2]));
        } else {
            gamebuino_meta_display_println_xy(mp_obj_get_int(args[0]), mp_obj_get_int(args[1]), mp_obj_str_get_str(args[2]));
        }
    } else if (n_args == 1) {
        if (MP_OBJ_IS_INT(args[0])) {
            gamebuino_meta_display_println_int(mp_obj_get_int(args[0]));
        } else {
            gamebuino_meta_display_println(mp_obj_str_get_str(args[0]));
        }
    }
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gbm_display_println_obj, 1, 3, gbm_display_println);

STATIC mp_obj_t gbm_display_draw_line(size_t n_args, const mp_obj_t *args) {
    gamebuino_meta_display_draw_line(mp_obj_get_int(args[0]), mp_obj_get_int(args[1]), mp_obj_get_int(args[2]), mp_obj_get_int(args[3]));
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gbm_display_draw_line_obj, 4, 4, gbm_display_draw_line);

STATIC mp_obj_t gbm_display_draw_rect(size_t n_args, const mp_obj_t *args) {
    gamebuino_meta_display_draw_rect(mp_obj_get_int(args[0]), mp_obj_get_int(args[1]), mp_obj_get_int(args[2]), mp_obj_get_int(args[3]));
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gbm_display_draw_rect_obj, 4, 4, gbm_display_draw_rect);

STATIC mp_obj_t gbm_display_fill_rect(size_t n_args, const mp_obj_t *args) {
    gamebuino_meta_display_fill_rect(mp_obj_get_int(args[0]), mp_obj_get_int(args[1]), mp_obj_get_int(args[2]), mp_obj_get_int(args[3]));
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gbm_display_fill_rect_obj, 4, 4, gbm_display_fill_rect);

STATIC mp_obj_t gbm_display_draw_pixel(size_t n_args, const mp_obj_t *args) {
    if (n_args == 2) {
        gamebuino_meta_display_draw_pixel(mp_obj_get_int(args[0]), mp_obj_get_int(args[1]));
    } else {
        gamebuino_meta_display_draw_pixel_color(mp_obj_get_int(args[0]), mp_obj_get_int(args[1]), mp_obj_get_int(args[2]));
    }
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gbm_display_draw_pixel_obj, 2, 3, gbm_display_draw_pixel);

STATIC mp_obj_t gbm_display_draw_circle(mp_obj_t x, mp_obj_t y, mp_obj_t r) {
    gamebuino_meta_display_draw_circle(mp_obj_get_int(x), mp_obj_get_int(y), mp_obj_get_int(r));
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_3(gbm_display_draw_circle_obj, gbm_display_draw_circle);

STATIC mp_obj_t gbm_display_fill_circle(mp_obj_t x, mp_obj_t y, mp_obj_t r) {
    gamebuino_meta_display_fill_circle(mp_obj_get_int(x), mp_obj_get_int(y), mp_obj_get_int(r));
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_3(gbm_display_fill_circle_obj, gbm_display_fill_circle);

STATIC mp_obj_t gbm_display_draw_triangle(size_t n_args, const mp_obj_t *args) {
    gamebuino_meta_display_draw_triangle(mp_obj_get_int(args[0]), mp_obj_get_int(args[1]), mp_obj_get_int(args[2]), mp_obj_get_int(args[3]), mp_obj_get_int(args[4]), mp_obj_get_int(args[5]));
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gbm_display_draw_triangle_obj, 6, 6, gbm_display_draw_triangle);

STATIC mp_obj_t gbm_display_fill_triangle(size_t n_args, const mp_obj_t *args) {
    gamebuino_meta_display_fill_triangle(mp_obj_get_int(args[0]), mp_obj_get_int(args[1]), mp_obj_get_int(args[2]), mp_obj_get_int(args[3]), mp_obj_get_int(args[4]), mp_obj_get_int(args[5]));
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gbm_display_fill_triangle_obj, 6, 6, gbm_display_fill_triangle);

STATIC mp_obj_t gbm_display_draw_round_rect(size_t n_args, const mp_obj_t *args) {
    gamebuino_meta_display_draw_round_rect(mp_obj_get_int(args[0]), mp_obj_get_int(args[1]), mp_obj_get_int(args[2]), mp_obj_get_int(args[3]), mp_obj_get_int(args[4]));
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gbm_display_draw_round_rect_obj, 5, 5, gbm_display_draw_round_rect);

STATIC mp_obj_t gbm_display_fill_round_rect(size_t n_args, const mp_obj_t *args) {
    gamebuino_meta_display_fill_round_rect(mp_obj_get_int(args[0]), mp_obj_get_int(args[1]), mp_obj_get_int(args[2]), mp_obj_get_int(args[3]), mp_obj_get_int(args[4]));
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gbm_display_fill_round_rect_obj, 5, 5, gbm_display_fill_round_rect);

STATIC mp_obj_t gbm_display_set_color(mp_obj_t c) {
    gamebuino_meta_display_set_color(mp_obj_get_int(c)); return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(gbm_display_set_color_obj, gbm_display_set_color);

STATIC mp_obj_t gbm_display_draw_bitmap(size_t n_args, const mp_obj_t *args) {
    int8_t x = mp_obj_get_int(args[0]);
    int8_t y = mp_obj_get_int(args[1]);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[2], &bufinfo, MP_BUFFER_READ);
    const uint8_t* buf = bufinfo.buf;
    if (n_args == 3) {
        gamebuino_meta_display_draw_bitmap(x, y, buf);
    } else {
        gamebuino_meta_display_draw_bitmap_scale(x, y, buf, mp_obj_get_int(args[3]));
    }
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gbm_display_draw_bitmap_obj, 3, 4, gbm_display_draw_bitmap);

STATIC mp_obj_t gbm_display_draw_image(size_t n_args, const mp_obj_t *args) {
    int8_t x = mp_obj_get_int(args[0]);
    int8_t y = mp_obj_get_int(args[1]);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[2], &bufinfo, MP_BUFFER_READ);
    const uint8_t* buf = bufinfo.buf;
    gamebuino_meta_display_draw_image(x, y, buf);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gbm_display_draw_image_obj, 3, 3, gbm_display_draw_image);

STATIC mp_obj_t gbm_display_set_font_size(const mp_obj_t size) {
    gamebuino_meta_display_set_font_size(mp_obj_get_int(size));
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(gbm_display_set_font_size_obj, gbm_display_set_font_size);

STATIC mp_obj_t gbm_display_width(void) {
    return MP_OBJ_NEW_SMALL_INT(80);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(gbm_display_width_obj, gbm_display_width);

STATIC mp_obj_t gbm_display_height(void) {
    return MP_OBJ_NEW_SMALL_INT(64);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(gbm_display_height_obj, gbm_display_height);

STATIC const mp_map_elem_t gbm_display_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR_clear), (mp_obj_t)&gbm_display_clear_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_fill), (mp_obj_t)&gbm_display_fill_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_print), (mp_obj_t)&gbm_display_print_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_println), (mp_obj_t)&gbm_display_println_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_drawLine), (mp_obj_t)&gbm_display_draw_line_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_drawRect), (mp_obj_t)&gbm_display_draw_rect_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_fillRect), (mp_obj_t)&gbm_display_fill_rect_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_drawPixel), (mp_obj_t)&gbm_display_draw_pixel_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_drawCircle), (mp_obj_t)&gbm_display_draw_circle_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_fillCircle), (mp_obj_t)&gbm_display_fill_circle_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_drawTriangle), (mp_obj_t)&gbm_display_draw_triangle_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_fillTriangle), (mp_obj_t)&gbm_display_fill_triangle_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_drawRoundRect), (mp_obj_t)&gbm_display_draw_round_rect_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_fillRoundRect), (mp_obj_t)&gbm_display_fill_round_rect_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_setColor), (mp_obj_t)&gbm_display_set_color_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_drawBitmap), (mp_obj_t)&gbm_display_draw_bitmap_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_drawImage), (mp_obj_t)&gbm_display_draw_image_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_setFontSize), (mp_obj_t)&gbm_display_set_font_size_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_width), (mp_obj_t)&gbm_display_width_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_height), (mp_obj_t)&gbm_display_height_obj },
};
STATIC MP_DEFINE_CONST_DICT (
    mp_dict_gamebuino_meta_display,
    gbm_display_table
);
const mp_obj_module_t mp_module_gamebuino_meta_display = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_dict_gamebuino_meta_display,
};

void gamebuino_meta_lights_clear(void);
void gamebuino_meta_lights_clear_color(const uint16_t);
void gamebuino_meta_lights_fill(void);
void gamebuino_meta_lights_fill_color(const uint16_t);
void gamebuino_meta_lights_draw_pixel(int16_t, int16_t);
void gamebuino_meta_lights_draw_pixel_color(int16_t, int16_t, uint16_t);
void gamebuino_meta_lights_fill_rect(int16_t, int16_t, int16_t, int16_t);
void gamebuino_meta_lights_set_color(uint16_t);

STATIC mp_obj_t gbm_lights_clear(size_t n_args, const mp_obj_t *args) {
    if (n_args == 0) {
        gamebuino_meta_lights_clear();
    } else {
        gamebuino_meta_lights_clear_color(mp_obj_get_int(args[0]));
    }
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gbm_lights_clear_obj, 0, 1, gbm_lights_clear);

STATIC mp_obj_t gbm_lights_fill(size_t n_args, const mp_obj_t *args) {
    if (n_args == 0) {
        gamebuino_meta_lights_fill();
    } else {
        gamebuino_meta_lights_fill_color(mp_obj_get_int(args[0]));
    }
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gbm_lights_fill_obj, 0, 1, gbm_lights_fill);

STATIC mp_obj_t gbm_lights_fill_rect(size_t n_args, const mp_obj_t *args) {
    gamebuino_meta_lights_fill_rect(mp_obj_get_int(args[0]), mp_obj_get_int(args[1]), mp_obj_get_int(args[2]), mp_obj_get_int(args[3]));
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gbm_lights_fill_rect_obj, 4, 4, gbm_lights_fill_rect);

STATIC mp_obj_t gbm_lights_draw_pixel(size_t n_args, const mp_obj_t *args) {
    if (n_args == 2) {
        gamebuino_meta_lights_draw_pixel(mp_obj_get_int(args[0]), mp_obj_get_int(args[1]));
    } else {
        gamebuino_meta_lights_draw_pixel_color(mp_obj_get_int(args[0]), mp_obj_get_int(args[1]), mp_obj_get_int(args[2]));
    }
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gbm_lights_draw_pixel_obj, 2, 3, gbm_lights_draw_pixel);

STATIC mp_obj_t gbm_lights_set_color(mp_obj_t c) {
    gamebuino_meta_lights_set_color(mp_obj_get_int(c)); return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(gbm_lights_set_color_obj, gbm_lights_set_color);

STATIC const mp_map_elem_t gbm_lights_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR_clear), (mp_obj_t)&gbm_lights_clear_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_fill), (mp_obj_t)&gbm_lights_fill_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_fillRect), (mp_obj_t)&gbm_lights_fill_rect_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_drawPixel), (mp_obj_t)&gbm_lights_draw_pixel_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_setColor), (mp_obj_t)&gbm_lights_set_color_obj },
};
STATIC MP_DEFINE_CONST_DICT (
    mp_dict_gamebuino_meta_lights,
    gbm_lights_table
);
const mp_obj_module_t mp_module_gamebuino_meta_lights = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_dict_gamebuino_meta_lights,
};

/*
extern const uint8_t gbm_BUTTON_DOWN;
extern const uint8_t gbm_BUTTON_LEFT;
extern const uint8_t gbm_BUTTON_RIGHT;
extern const uint8_t gbm_BUTTON_UP;
extern const uint8_t gbm_BUTTON_A;
extern const uint8_t gbm_BUTTON_B;
extern const uint8_t gbm_BUTTON_MENU;
extern const uint8_t gbm_BUTTON_HOME;
const mp_obj_int_t mp_BUTTON_DOWN_obj = {{&mp_type_int}, gbm_BUTTON_DOWN};
const mp_obj_int_t mp_BUTTON_LEFT_obj = {{&mp_type_int}, gbm_BUTTON_LEFT};
const mp_obj_int_t mp_BUTTON_RIGHT_obj = {{&mp_type_int}, gbm_BUTTON_RIGHT};
const mp_obj_int_t mp_BUTTON_UP_obj = {{&mp_type_int}, gbm_BUTTON_UP};
const mp_obj_int_t mp_BUTTON_A_obj = {{&mp_type_int}, gbm_BUTTON_A};
const mp_obj_int_t mp_BUTTON_B_obj = {{&mp_type_int}, gbm_BUTTON_B};
const mp_obj_int_t mp_BUTTON_MENU_obj = {{&mp_type_int}, gbm_BUTTON_MENU};
const mp_obj_int_t mp_BUTTON_HOME_obj = {{&mp_type_int}, gbm_BUTTON_HOME};
*/
bool gamebuino_meta_buttons_pressed(uint8_t b);
bool gamebuino_meta_buttons_released(uint8_t b);
bool gamebuino_meta_buttons_held(uint8_t b, uint16_t time);
bool gamebuino_meta_buttons_repeat(uint8_t b, uint16_t time);
uint16_t gamebuino_meta_buttons_time_held(uint8_t b);

STATIC mp_obj_t gbm_buttons_pressed(mp_obj_t b) { return 
mp_obj_new_bool(gamebuino_meta_buttons_pressed(mp_obj_get_int(b))); }
STATIC MP_DEFINE_CONST_FUN_OBJ_1(gbm_buttons_pressed_obj, gbm_buttons_pressed);

STATIC mp_obj_t gbm_buttons_released(mp_obj_t b) { return mp_obj_new_bool(gamebuino_meta_buttons_released(mp_obj_get_int(b))); }
STATIC MP_DEFINE_CONST_FUN_OBJ_1(gbm_buttons_released_obj, gbm_buttons_released);

STATIC mp_obj_t gbm_buttons_held(mp_obj_t b, mp_obj_t time) { return mp_obj_new_bool(gamebuino_meta_buttons_held(mp_obj_get_int(b), mp_obj_get_int(time))); }
STATIC MP_DEFINE_CONST_FUN_OBJ_2(gbm_buttons_held_obj, gbm_buttons_held);

STATIC mp_obj_t gbm_buttons_repeat(mp_obj_t b, mp_obj_t time) { return mp_obj_new_bool(gamebuino_meta_buttons_repeat(mp_obj_get_int(b), mp_obj_get_int(time))); }
STATIC MP_DEFINE_CONST_FUN_OBJ_2(gbm_buttons_repeat_obj, gbm_buttons_repeat);

STATIC mp_obj_t gbm_buttons_time_held(mp_obj_t b) { return mp_obj_new_int(gamebuino_meta_buttons_time_held(mp_obj_get_int(b))); }
STATIC MP_DEFINE_CONST_FUN_OBJ_1(gbm_buttons_time_held_obj, gbm_buttons_time_held);

STATIC const mp_map_elem_t gbm_buttons_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR_DOWN), MP_OBJ_NEW_SMALL_INT(0) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_LEFT), MP_OBJ_NEW_SMALL_INT(1) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_RIGHT), MP_OBJ_NEW_SMALL_INT(2) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_UP), MP_OBJ_NEW_SMALL_INT(3) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_A), MP_OBJ_NEW_SMALL_INT(4) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_B), MP_OBJ_NEW_SMALL_INT(5) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_MENU), MP_OBJ_NEW_SMALL_INT(6) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_HOME), MP_OBJ_NEW_SMALL_INT(7) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_pressed), (mp_obj_t)&gbm_buttons_pressed_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_released), (mp_obj_t)&gbm_buttons_released_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_held), (mp_obj_t)&gbm_buttons_held_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_repeat), (mp_obj_t)&gbm_buttons_repeat_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_timeHeld), (mp_obj_t)&gbm_buttons_time_held_obj },
};
STATIC MP_DEFINE_CONST_DICT (
    mp_dict_gamebuino_meta_buttons,
    gbm_buttons_table
);
const mp_obj_module_t mp_module_gamebuino_meta_buttons = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_dict_gamebuino_meta_buttons,
};


STATIC const mp_map_elem_t gbm_color_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR_WHITE), MP_OBJ_NEW_SMALL_INT(0xFFFF) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_GRAY), MP_OBJ_NEW_SMALL_INT(0xACD0) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_DARKGRAY), MP_OBJ_NEW_SMALL_INT(0x5268) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_BLACK), MP_OBJ_NEW_SMALL_INT(0x0000) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_PURPLE), MP_OBJ_NEW_SMALL_INT(0x9008) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_PINK), MP_OBJ_NEW_SMALL_INT(0xCA30) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_RED), MP_OBJ_NEW_SMALL_INT(0xD8E4) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_ORANGE), MP_OBJ_NEW_SMALL_INT(0xFD42) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_BROWN), MP_OBJ_NEW_SMALL_INT(0xCC68) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_BEIGE), MP_OBJ_NEW_SMALL_INT(0xFEB2) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_YELLOW), MP_OBJ_NEW_SMALL_INT(0xF720) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_LIGHTGREEN), MP_OBJ_NEW_SMALL_INT(0x8668) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_GREEN), MP_OBJ_NEW_SMALL_INT(0x044A) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_DARKBLUE), MP_OBJ_NEW_SMALL_INT(0x0210) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_BLUE), MP_OBJ_NEW_SMALL_INT(0x4439) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_LIGHTBLUE), MP_OBJ_NEW_SMALL_INT(0x7DDF) },
};
STATIC MP_DEFINE_CONST_DICT (
    mp_dict_gamebuino_meta_color,
    gbm_color_table
);
const mp_obj_module_t mp_module_gamebuino_meta_color = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_dict_gamebuino_meta_color,
};


void gamebuino_meta_gui_keyboard(const char*, char*, uint8_t);
uint8_t gamebuino_meta_gui_menu(const char*, const char**, uint8_t);
void gamebuino_meta_gui_popup(const char*, uint8_t);

STATIC mp_obj_t gbm_gui_keyboard(size_t n_args, const mp_obj_t *args) {
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[0], &bufinfo, MP_BUFFER_READ);
    const char* title = bufinfo.buf;
    uint8_t length = 63;
    if (n_args > 1) {
        if (n_args == 3) {
            length = mp_obj_get_int(args[2]);
        }
    }
    char text[length + 1];
    if (n_args > 1) {
        mp_get_buffer_raise(args[1], &bufinfo, MP_BUFFER_READ);
        strncpy(text, bufinfo.buf, length);
        text[length] = '\0';
    } else {
        text[0] = '\0';
    }
    gamebuino_meta_gui_keyboard(title, text, length);
    return mp_obj_new_str(text, strlen(text));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(gbm_gui_keyboard_obj, 1, 3, gbm_gui_keyboard);

STATIC mp_obj_t gbm_gui_menu(const mp_obj_t title_obj, const mp_obj_t entries_obj) {
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(title_obj, &bufinfo, MP_BUFFER_READ);
    const char* title = bufinfo.buf;
    
    uint8_t entries_size = mp_obj_get_int(mp_obj_len(entries_obj));
    mp_obj_iter_buf_t iter_buf;
    mp_obj_t iterable = mp_getiter(entries_obj, &iter_buf);
    const char* entries[entries_size];
    for (uint8_t i = 0; i < entries_size; i++) {
        mp_obj_t o = mp_iternext(iterable);
        mp_get_buffer_raise(o, &bufinfo, MP_BUFFER_READ);
        entries[i] = bufinfo.buf;
    }
    uint8_t res = gamebuino_meta_gui_menu(title, entries, entries_size);
    return MP_OBJ_NEW_SMALL_INT(res);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(gbm_gui_menu_obj, gbm_gui_menu);

STATIC mp_obj_t gbm_gui_popup(const mp_obj_t title_obj, const mp_obj_t duration_obj) {
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(title_obj, &bufinfo, MP_BUFFER_READ);
    gamebuino_meta_gui_popup(bufinfo.buf, mp_obj_get_int(duration_obj));
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(gbm_gui_popup_obj, gbm_gui_popup);

STATIC const mp_map_elem_t gbm_gui_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR_keyboard), (mp_obj_t)&gbm_gui_keyboard_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_menu), (mp_obj_t)&gbm_gui_menu_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_popup), (mp_obj_t)&gbm_gui_popup_obj },
};
STATIC MP_DEFINE_CONST_DICT (
    mp_dict_gamebuino_meta_gui,
    gbm_gui_table
);
const mp_obj_module_t mp_module_gamebuino_meta_gui = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_dict_gamebuino_meta_gui,
};


void gamebuino_meta_begin(void);
bool gamebuino_meta_update(void);
void gamebuino_meta_wait_for_update(void);
void gamebuino_meta_update_display(void);
void gamebuino_meta_set_frame_rate(uint8_t fps);
uint8_t gamebuino_meta_get_cpu_load(void);
void gamebuino_meta_get_default_name(char*);

STATIC mp_obj_t gbm_begin(void) { gamebuino_meta_begin(); return mp_const_none; }
STATIC MP_DEFINE_CONST_FUN_OBJ_0(gbm_begin_obj, gbm_begin);

STATIC mp_obj_t gbm_update(void) { return mp_obj_new_bool(gamebuino_meta_update()); }
STATIC MP_DEFINE_CONST_FUN_OBJ_0(gbm_update_obj, gbm_update);

STATIC mp_obj_t gbm_wait_for_update(void) { gamebuino_meta_wait_for_update(); return mp_const_none; }
STATIC MP_DEFINE_CONST_FUN_OBJ_0(gbm_wait_for_update_obj, gbm_wait_for_update);

STATIC mp_obj_t gbm_update_display(void) { gamebuino_meta_update_display(); return mp_const_none; }
STATIC MP_DEFINE_CONST_FUN_OBJ_0(gbm_update_display_obj, gbm_update_display);

STATIC mp_obj_t gbm_set_frame_rate(mp_obj_t fps) { gamebuino_meta_set_frame_rate(mp_obj_get_int(fps)); return mp_const_none; }
STATIC MP_DEFINE_CONST_FUN_OBJ_1(gbm_set_frame_rate_obj, gbm_set_frame_rate);

STATIC mp_obj_t gbm_get_cpu_load(void) { return mp_obj_new_int(gamebuino_meta_get_cpu_load()); }
STATIC MP_DEFINE_CONST_FUN_OBJ_0(gbm_get_cpu_load_obj, gbm_get_cpu_load);

STATIC mp_obj_t gbm_get_free_ram(void) {
    gc_collect();
    gc_info_t info;
    gc_info(&info);
    return MP_OBJ_NEW_SMALL_INT(info.free);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(gbm_get_free_ram_obj, gbm_get_free_ram);

STATIC mp_obj_t gbm_get_default_name(void) {
    char name[13];
    gamebuino_meta_get_default_name(name);
    return mp_obj_new_str(name, strlen(name));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(gbm_get_default_name_obj, gbm_get_default_name);

STATIC const mp_map_elem_t gbm_globals_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_gamebuino_meta) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_loader), (mp_obj_t)&gbm_loader_obj },
    
    { MP_OBJ_NEW_QSTR(MP_QSTR_begin), (mp_obj_t)&gbm_begin_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_update), (mp_obj_t)&gbm_update_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_waitForUpdate), (mp_obj_t)&gbm_wait_for_update_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_updateDisplay), (mp_obj_t)&gbm_update_display_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_setFrameRate), (mp_obj_t)&gbm_set_frame_rate_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_getCpuLoad), (mp_obj_t)&gbm_get_cpu_load_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_getFreeRam), (mp_obj_t)&gbm_get_free_ram_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_getDefaultName), (mp_obj_t)&gbm_get_default_name_obj },
    
    { MP_OBJ_NEW_QSTR(MP_QSTR_collide), (mp_obj_t)&mp_module_gamebuino_meta_collide },
    { MP_OBJ_NEW_QSTR(MP_QSTR_display), (mp_obj_t)&mp_module_gamebuino_meta_display },
    { MP_OBJ_NEW_QSTR(MP_QSTR_lights), (mp_obj_t)&mp_module_gamebuino_meta_lights },
    { MP_OBJ_NEW_QSTR(MP_QSTR_buttons), (mp_obj_t)&mp_module_gamebuino_meta_buttons },
    { MP_OBJ_NEW_QSTR(MP_QSTR_color), (mp_obj_t)&mp_module_gamebuino_meta_color },
    { MP_OBJ_NEW_QSTR(MP_QSTR_gui), (mp_obj_t)&mp_module_gamebuino_meta_gui },
};
STATIC MP_DEFINE_CONST_DICT (
    mp_module_gamebuino_meta_globals,
    gbm_globals_table
);
const mp_obj_module_t mp_module_gamebuino_meta = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_module_gamebuino_meta_globals,
};
