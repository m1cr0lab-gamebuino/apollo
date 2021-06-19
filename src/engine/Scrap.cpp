/**
 * -------------------------------------------------------------------------
 *                                  Apollo
 * -------------------------------------------------------------------------
 *         a tiny game for the Gamebuino META retro gaming handheld
 *                    inspired by the famous Lunar Lander
 *                       https://youtu.be/McAhSoAEbhM
 *       https://en.wikipedia.org/wiki/Lunar_Lander_(1979_video_game)
 * -------------------------------------------------------------------------
 *                          © 2021 Steph @ m1cr0lab
 *                       https://gamebuino.m1cr0lab.com
 * -------------------------------------------------------------------------
 */

#include <Gamebuino-Meta.h>
#include "Scrap.h"
#include "../data/assets.h"
#include "../data/config.h"

void Scrap::init(float_t x, float_t y, float_t radius, float_t vx, float_t vy, float_t vrot) {

    _x = x;
    _y = y;
    _r = radius;

    _vx   = vx;
    _vy   = vy;
    _rot  = 0;
    _vrot = vrot;

    uint8_t n = VERTICE_NB << 1;

    for (uint8_t i=0; i<n; i+=2) {

        _vertice[i]   = radius * .1f * random(4, 11);
        _vertice[i+1] = i * 2*PI / VERTICE_NB;

    }

    _visible = true;

}

void Scrap::draw(Camera &camera) {

    if (!_visible) return;

    float_t cx = camera.ox();
    float_t cy = camera.oy();
    float_t cz = camera.zoom();

    float_t r = _vertice[0];
    float_t a = _vertice[1] + _rot;

    float_t x0 = _x + r*cos(a), x1 = x0;
    float_t y0 = _y + r*sin(a), y1 = y0;

    float_t x2, y2;
    uint8_t n = VERTICE_NB << 1;

    gb.display.setColor(COLOR_APOLLO);

    for (uint8_t i=2; i<n; i+=2) {

        r = _vertice[i];
        a = _vertice[i+1] + _rot;

        x2 = _x + r*cos(a);
        y2 = _y + r*sin(a);

        gb.display.drawLine(
            cz * (x1 - cx),
            cz * (y1 - cy),
            cz * (x2 - cx),
            cz * (y2 - cy)
        );

        x1 = x2;
        y1 = y2;

    }

    gb.display.drawLine(
        cz * (x0 - cx),
        cz * (y0 - cy),
        cz * (x2 - cx),
        cz * (y2 - cy)
    );

}

void Scrap::loop() {

    if (!_visible) return;

    _rot += _vrot;

         if (_rot < 0)    _rot += 2*PI;
    else if (_rot > 2*PI) _rot -= 2*PI;

    _vy += GRAVITY;

    _x += _vx;
    _y += _vy;

    _visible = !(
            _x + _r < 0
        ||  _x > _r + SCREEN_WIDTH
        ||  _y + _r < 0
        ||  _y > _r + SCREEN_HEIGHT
    );

}