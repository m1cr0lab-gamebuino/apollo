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

class Scrap {

    private:

        static const uint8_t VERTICE_NB = 3;

        bool _visible;

        float_t _x;
        float_t _y;
        float_t _r;
        float_t _vx;
        float_t _vy;
        float_t _rot;
        float_t _vrot;

        float_t _vertice[VERTICE_NB << 1];

    public:

        void init(float_t x, float_t y, float_t radius, float_t vx, float_t vy, float_t vrot);
        void draw(Camera &camera);
        void loop();

};