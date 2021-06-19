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

#include "Camera.h"

#include "../data/config.h"

float_t Camera::ox() {
    return _ox;
}

float_t Camera::oy() {
    return _oy;
}

float_t Camera::w() {
    return _w;
}

float_t Camera::h() {
    return _h;
}

float_t Camera::zoom() {
    return _z;
}

void Camera::begin(float_t x, float_t y) {

    _fx = _x = x;
    _fy = _y = y;
    _fz = _z = 1.f;

    _w = SCREEN_WIDTH;
    _h = SCREEN_HEIGHT;

    _focusing = false;

}

void Camera::focus(float_t x, float_t y, float_t zoom, float_t easing) {

    float_t w2 = SCREEN_WIDTH  / (2.f * zoom);
    float_t h2 = SCREEN_HEIGHT / (2.f * zoom);

    _fx = max(w2, min(x, SCREEN_WIDTH  - 1 - w2));
    _fy = max(h2, min(y, SCREEN_HEIGHT - 1 - h2));
    _fz = zoom;
    _fk = easing;

    _focusing = true;

}

void Camera::_focus() {

    float_t dx = _fx - _x;
    float_t dy = _fy - _y;
    float_t dz = _fz - _z;

    _focusing = (abs(dx) > .05f) || (abs(dy) > .05f) || (abs(dz) > .05f);

    if (_focusing) {

        _x += _fk * dx;
        _y += _fk * dy;
        _z += _fk * dz;

    } else {

        _x = _fx;
        _y = _fy;
        _z = _fz;

    }

    _w = SCREEN_WIDTH  / _z;
    _h = SCREEN_HEIGHT / _z;

    _ox = _x - .5f * _w;
    _oy = _y - .5f * _h;

}

void Camera::loop() {

    if (_focusing) _focus();

}