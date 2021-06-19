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
#include "Apollo.h"
#include "../data/assets.h"
#include "../data/config.h"

float_t Apollo::x() {
    return _x;
}

float_t Apollo::y() {
    return _y;
}

float_t Apollo::r() {
    return _r;
}

float_t Apollo::rot() {
    return _rot;
}

float_t Apollo::vx() {
    return _vx;
}

float_t Apollo::vy() {
    return _vy;
}

uint16_t Apollo::fuel() {
    return _fuel;
}

void Apollo::refuel() {
    _fuel = STARTING_FUEL;
}

void Apollo::power(float_t p) {

    float_t f = min(_fuel, p * APOLLO_FUEL_DECAY);

    _fuel -= f;
    p      = f / APOLLO_FUEL_DECAY;
    _pow   = p;
    _acc   = p * APOLLO_POWER;

}

void Apollo::rotate(int8_t a) {

    if (a == 0) {

        _vrot = 0;

    } else {

        int8_t  s = a < 0 ? -1 : 1;
        uint8_t f = min(_fuel, abs(a));

        _fuel -= f;
        _vrot = PI*s*f/180.f;

    };

}

void Apollo::propel(float_t vx, float_t vy, float_t rotation) {

    _vx  = vx;
    _vy  = vy;
    _rot = rotation;

}

void Apollo::land(float_t y) {

    _y  = y;
    _vx = _vy = _acc = _rot = _vrot = 0;

}

void Apollo::moveX(int16_t dx) {
    _x += dx;
}

void Apollo::moveY(int16_t dy) {
    _y += dy;
}

void Apollo::init(float_t x, float_t y, float_t radius) {

    _x = x;
    _y = y;
    _r = radius;

    refuel();

}

void Apollo::reset(float_t x, float_t y) {

    _x = x;
    _y = y;

    _vx = _vy = _acc = _rot = _vrot = 0;

}

void Apollo::draw(Camera& camera, bool with_flame) {

    float_t cx = camera.ox();
    float_t cy = camera.oy();
    float_t cz = camera.zoom();

    gb.display.setColor(COLOR_APOLLO);

    uint8_t i, j;
    float_t ri, ti, rj, tj;
    float_t x1, y1, x2, y2;

    for (uint8_t a=0; a<APOLLO_ARCS_NB; a+=2) {

        i = APOLLO_ARCS[a] << 1;
        j = APOLLO_ARCS[a+1] << 1;

        ri = _r   * APOLLO_VERTICES[i];
        ti = _rot + APOLLO_VERTICES[i+1];
        rj = _r   * APOLLO_VERTICES[j];
        tj = _rot + APOLLO_VERTICES[j+1];

        x1 = _x + ri*cos(ti);
        y1 = _y + ri*sin(ti);
        x2 = _x + rj*cos(tj);
        y2 = _y + rj*sin(tj);

        gb.display.drawLine(
            cz * (x1 - cx),
            cz * (y1 - cy),
            cz * (x2 - cx),
            cz * (y2 - cy)
        );

    }

    if (with_flame && _pow) {

        float_t r_min = _r   * APOLLO_FLAME[0];
        float_t t_min = _rot + APOLLO_FLAME[1];
        float_t r_max = _r   * APOLLO_FLAME[2];

        float_t r = r_min + _pow * (r_max - r_min);

        float_t ri = _r   * APOLLO_VERTICES[28];
        float_t ti = _rot + APOLLO_VERTICES[29];
        float_t rj = _r   * APOLLO_VERTICES[30];
        float_t tj = _rot + APOLLO_VERTICES[31];

        x1 = _x + ri*cos(ti);
        y1 = _y + ri*sin(ti);
        x2 = _x + rj*cos(tj);
        y2 = _y + rj*sin(tj);

        r *= 1 + .01f*random(50);

        float_t x3 = _x + r*cos(t_min);
        float_t y3 = _y + r*sin(t_min);

        gb.display.setColor(COLOR_FLAME);

        gb.display.drawLine(
            cz * (x1 - cx),
            cz * (y1 - cy),
            cz * (x3 - cx),
            cz * (y3 - cy)
        );

        gb.display.drawLine(
            cz * (x2 - cx),
            cz * (y2 - cy),
            cz * (x3 - cx),
            cz * (y3 - cy)
        );

    }
}

void Apollo::loop() {

    _rot += _vrot;
    
         if (_rot < 0)    _rot += 2*PI;
    else if (_rot > 2*PI) _rot -= 2*PI;

    _vx += _acc * cos(_rot - .5f*PI);
    _vy += _acc * sin(_rot - .5f*PI) + GRAVITY;

    _x += _vx;
    _y += _vy;

}