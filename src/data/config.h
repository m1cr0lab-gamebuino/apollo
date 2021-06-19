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

#include <Arduino.h>

#define DEBUG 0

const uint8_t LEFT_POT_PIN  = A5;
const uint8_t RIGHT_POT_PIN = A4;

const uint8_t SCREEN_WIDTH  = 160;
const uint8_t SCREEN_HEIGHT = 128;

const uint8_t  STARTING_LIVES = 2;
const uint16_t STARTING_FUEL  = 8000;

const float_t APOLLO_INIT_VY    = .6f;
const float_t APOLLO_POWER      = .01f;
const uint8_t APOLLO_FUEL_DECAY = 10;

const float_t GRAVITY = .003f;