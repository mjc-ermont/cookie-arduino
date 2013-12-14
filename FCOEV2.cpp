/*
 * Copyright (c) 2013 Sebastien Jean.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU Lesser Public License v3.0
 * which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/lgpl-3.0.html
 *
 * Contributors:
 *     Sebastien Jean - initial API and implementation
 */

#include <Arduino.h> 
#include "FCOEV2.h"

FCOEV2::FCOEV2(uint8_t pwmPin)
{
  this->pwmPin = pwmPin;
  this->pwrPin = NO_PWR_PIN;
  pinMode(this->pwmPin, OUTPUT);
  this->on = true;
  this->resetMode();
}

FCOEV2::FCOEV2(uint8_t pwmPin, uint8_t pwrPin)
{
  this->pwmPin = pwmPin;
  this->pwrPin = pwrPin;
  pinMode(this->pwmPin, OUTPUT);
  pinMode(this->pwrPin, OUTPUT);
  // Camera is off
  digitalWrite(this->pwrPin, LOW);
  this->on = false;
  this->resetMode();
}

void
FCOEV2::resetMode()
{
  this->mode = MODE_VIDEO;
  this->running = false;
}

void
FCOEV2::idle()
{
  for (int i = 0; i < IDLE_PERIODS; i++)
    {
      digitalWrite(this->pwmPin, HIGH);
      delayMicroseconds(IDLE_HIGH_MICROS);
      digitalWrite(this->pwmPin, LOW);
      delay(PERIOD_MILLIS);
    }
}

void
FCOEV2::signal(uint16_t pulseWidthMicros, uint8_t periods)
{
  for (int i = 0; i < periods; i++)
    {
      digitalWrite(this->pwmPin, HIGH);
      delayMicroseconds(pulseWidthMicros);
      digitalWrite(this->pwmPin, LOW);
      delay(PERIOD_MILLIS);
    }
}

void
FCOEV2::toggleAction()
{
  idle();
  signal(ACTION_OR_MODE_HIGH_MICROS, ACTION_PERIODS);
  idle();
  if (this->mode != MODE_PHOTO_SINGLE)
    this->running = !this->running;
}

void
FCOEV2::switchToNextMode()
{
  idle();
  signal(ACTION_OR_MODE_HIGH_MICROS, CHANGE_MODE_PERIODS);
  idle();
  if (this->mode == MODE_VIDEO)
    this->mode = MODE_PHOTO_SERIAL;
  else if (this->mode == MODE_PHOTO_SERIAL)
    this->mode = MODE_PHOTO_SINGLE;
  else if (this->mode == MODE_PHOTO_SINGLE)
    this->mode = MODE_VIDEO;

}

void
FCOEV2::switchToMode(uint8_t mode)
{
  int loops = 0;

  switch (mode)
    {
  case MODE_VIDEO:
  case MODE_PHOTO_SERIAL:
  case MODE_PHOTO_SINGLE:
    {
    if (this->mode == mode)
      return;

    if (this->mode < mode)
      loops = mode - this->mode;
    else
      loops = (mode + 3) - this->mode;
    for (; loops > 0; loops--)
      {
        this->switchToNextMode();
        delay(SWITCH_MODE_PAUSE_MILLIS);
      }
    break;
    }
  default:
    return;

    }
  // Could not figure out problem with modulus, so wrote it like that.
}

void
FCOEV2::switchOn()
{
  if (this->pwrPin != NO_PWR_PIN)
    {
      digitalWrite(this->pwrPin, HIGH);
      this->on = true;
      resetMode();
    }
}

void
FCOEV2::switchOff()
{
  if (this->pwrPin != NO_PWR_PIN)
    {
      digitalWrite(this->pwrPin, LOW);
      this->on = false;
      resetMode();
    }
}

uint8_t
FCOEV2::getCurrentMode()
{
  return this->mode;
}

boolean
FCOEV2::getRunningStatus()
{
  return (this->running == CAMERA_RUNNING);
}

boolean
FCOEV2::isOn()
{
  return (this->on == CAMERA_ON);
}

