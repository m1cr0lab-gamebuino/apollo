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

#pragma once

#include "Camera.h"

class Apollo {

    private:

        float_t _x;
        float_t _y;
        float_t _r;

        float_t _pow;
        float_t _vx;
        float_t _vy;
        float_t _acc;
        float_t _rot;
        float_t _vrot;

        uint16_t _fuel;

    public:

        float_t x();
        float_t y();
        float_t r();
        float_t rot();
        float_t vx();
        float_t vy();

        uint16_t fuel();

        void refuel();
        void power(float_t p);
        void rotate(int8_t a);
        void propel(float_t vx, float_t vy, float_t rotation=0);
        void land(float_t y);

        void init(float_t x, float_t y, float_t radius);
        void reset(float_t x, float_t y);
        void moveX(int16_t dx);
        void moveY(int16_t dy);
        void draw(Camera& camera, bool with_flame=false);
        void loop();

};