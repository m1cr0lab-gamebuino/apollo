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

#include "Pot.h"

void Pot::begin(uint8_t pin) {

    pinMode(this->_pin = pin, INPUT);
    _value = 0;

}

void Pot::read() {
    _value = analogRead(_pin);
}

uint16_t Pot::signal() {
    return _value;
}