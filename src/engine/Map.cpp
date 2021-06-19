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
#include "Map.h"
#include "../data/assets.h"
#include "../data/config.h"

uint8_t Map::landing_zones() {
    return _nb_landing_zone;
}

LandingZone* Map::landing_zone(uint8_t index) {
    return &_landing_zone[index < _nb_landing_zone ? index : 0];
}

int16_t Map::y(uint8_t x) {
    return _y[x];
}

void Map::reset() {

    _build();
    _spreadStars();

}

void Map::_build() {

    int16_t y = SCREEN_HEIGHT / 3;

    _y_max = _y[0] = _y[SCREEN_WIDTH - 1] = y;

    _nb_landing_zone = 0;

    _shape(0, SCREEN_WIDTH - 1, 1.4f * y);

    LandingZone *zone;
    uint8_t zx, zy, zw1, zw2;

    for (uint8_t i=0; i<_nb_landing_zone; ++i) {

        zone = _landing_zone + i;

        zx = zone->x;
        zy = zone->y;

        zw1 = 0; do { ++zw1; } while (_y[zx - zw1] == _y[zx]);
        zw2 = 0; do { ++zw2; } while (_y[zx + zw2] == _y[zx]);

        zone->x_start = zx  - zw1 + 1;
        zone->width   = zw1 + zw2 - 2;

             if (zone->width <  6) zone->bonus_factor = 5;
        else if (zone->width <  8) zone->bonus_factor = 4;
        else if (zone->width < 10) zone->bonus_factor = 3;
        else                       zone->bonus_factor = 2;
        
    }

    y = SCREEN_HEIGHT - 1 - _y_max - 4 - BONUS_DATA[1];
    for (uint8_t x=0; x<SCREEN_WIDTH; ++x) _y[x] += y;
    for (uint8_t i=0; i<_nb_landing_zone; ++i) _landing_zone[i].y += y;

}

void Map::_shape(int16_t x1, int16_t x2, int16_t displacement, uint8_t step) {

    uint8_t x = (x1 + x2) >> 1;
    int16_t y = ((_y[x1] + _y[x2]) >> 1) + displacement;

    _y[x] = y;

    if (y > _y_max) _y_max = y;

    if (x2 - x1 > 2) {

        uint8_t w2 = SCREEN_WIDTH >> 1,
                w4 = w2 >> 1,
                x3 = x,
                x4 = x;

        if (
            (step == 3 && x > w4 && x < w2) ||
            (step < 4  && x > w2 && _nb_landing_zone < NB_LANDING_ZONE)
        ) {

            LandingZone *zone = _landing_zone + _nb_landing_zone++;

            uint8_t radius = 2*random(1, 5);

            for (uint8_t u=1; u<=radius; ++u) {
                _y[x3 = x - u] = _y[x4 = x + u] = y;
            }

            zone->x = x;
            zone->y = y;

        }

        displacement *= (random(2) ? -1 : 1) * ROUGHNESS;

        _shape(x1, x3, displacement, step+1);
        _shape(x4, x2, displacement, step+1);

    }

}

void Map::_spreadStars() {

    uint8_t n = 0;

    while (n < NB_STARS) {

        uint8_t x = random(0, SCREEN_WIDTH);
        uint8_t y = random(0, SCREEN_HEIGHT);

        if (y < _y[x] - 2) {

            _star[n].x = x;
            _star[n].y = y;
            n++;

        }

    }

}

void Map::draw(Camera& camera) {

    float_t cx = camera.ox();
    float_t cy = camera.oy();
    float_t cz = camera.zoom();

    uint8_t x0 = 0;
    int16_t y0 = _y[x0];

    gb.display.setColor(COLOR_GROUND);
    
    for (uint8_t x=1; x<SCREEN_WIDTH; ++x) {

        gb.display.drawLine(
            cz * (x0 - cx),
            cz * (y0 - cy),
            cz * (x - cx),
            cz * (_y[x] - cy)
        );
        
        x0 = x;
        y0 = _y[x];
        
    }

    gb.display.setColor(COLOR_STAR);

    for (uint8_t i=0; i<NB_STARS; ++i) {

        gb.display.drawPixel(
            cz * (_star[i].x - cx),
            cz * (_star[i].y - cy)
        );

    }

    Image factor(BONUS_DATA);
    char buffer[4];
    int16_t tx, ty;
    LandingZone *zone;

    for (uint8_t i=0; i<_nb_landing_zone; ++i) {

        zone = _landing_zone + i;

        gb.display.setColor(COLOR_LANDING_ZONE);
        gb.display.drawFastHLine(
            cz * (zone->x_start - cx),
            cz * (zone->y - cy),
            cz * zone->width
        );

        tx = cz * (zone->x_start + (zone->width >> 1) - cx);
        ty = cz * (zone->y - cy) + 4;

        factor.setFrame(zone->bonus_factor-1);
        gb.display.drawImage(
            tx - BONUS_DATA[0],
            ty,
            factor
        );

        factor.setFrame(0);
        gb.display.drawImage(
            tx+1,
            ty,
            factor
        );

    }

}