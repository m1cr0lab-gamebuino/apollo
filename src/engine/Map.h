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
#include "../data/config.h"

struct LandingZone {

    uint8_t x;
    uint8_t y;
    uint8_t x_start;
    uint8_t width;
    uint8_t bonus_factor;

};

struct Star {
    
    uint8_t x;
    uint8_t y;
    
};

class Map {

    private:

        static constexpr uint8_t NB_STARS        = 50;
        static constexpr uint8_t NB_LANDING_ZONE = 3;
        static constexpr float_t ROUGHNESS       = .5f;

        uint8_t _w;
        uint8_t _h;
        int16_t _y[SCREEN_WIDTH];
        int16_t _y_max;

        float _roughness;

        uint8_t     _nb_landing_zone;
        LandingZone _landing_zone[NB_LANDING_ZONE];

        Star _star[NB_STARS];

        void _build();
        void _shape(int16_t x1, int16_t x2, int16_t displacement, uint8_t step = 1);
        void _spreadStars();

    public:

        uint8_t      landing_zones();
        LandingZone *landing_zone(uint8_t index);
        int16_t      y(uint8_t x);

        void reset();
        void draw(Camera& camera);

};