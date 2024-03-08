#pragma once

#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <optional>
#include <thread>
#include <windows.h>

using time_point = std::chrono::system_clock::time_point;
using float32_t = float;

class Point2i {
  public:
    int32_t x;
    int32_t y;

    static Point2i create(int32_t x, int32_t y);
};

class Point2f {
  public:
    float32_t x;
    float32_t y;

    static Point2f create(float32_t x, float32_t y);
};

Point2i get_screen_size();

class Color {
  public:
    uint8_t r;
    uint8_t g;
    uint8_t b;

    static Color create(uint8_t r, uint8_t g, uint8_t b);
    static Color
    from_hsv(float32_t hew, float32_t saturation, float32_t lightness);
};

class Style {
  public:
    Color fg;
    Color bg;

    static Style unstyled();
    static Style create(Color fg, Color bg);

    Style with_fg(Color fg);
    Style with_bg(Color bg);
};

class Gui {
    uint16_t width;
    uint16_t height;

    Style *style;
    char *screen;

    time_point last_update;

    uint16_t frame_rate = 30;
    float32_t delta_time = 1.0f / frame_rate;

    size_t to_index(Point2i position);
    void refresh_screen();

  public:
    static Gui create();

    void drawText(Point2i position, const std::string text, Style style);
    float32_t get_delta_time();

    void update();
};
