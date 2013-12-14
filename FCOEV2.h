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

#ifndef FCOEV2_h
#define FCOEV2_h

#include <inttypes.h>

/**
 * Milliseconds to wait after calling <tt>switchToNextMode</tt> in order to be sure that
 * camera has correctly process the order
 */
// TODO try to decrease this value to the least working one
#define SWITCH_MODE_PAUSE_MILLIS 1500

/**
 * Milliseconds to wait after calling <tt>switchOn</tt> in order to be sure that
 * camera has correctly process the order
 */
#define SWITCH_ON_PAUSE_MILLIS 15000

/**
 * Number of periods (20ms) of IDLE signal.
 */
// TODO try to decrease this value to the least working one
#define IDLE_PERIODS 100

/**
 * Number of periods (20ms) of ACTION signal.
 */
#define ACTION_PERIODS 25

/**
 * Number of periods (20ms) of CHANGE_MODE signal.
 */
// TODO try to decrease this value to the least working one
#define CHANGE_MODE_PERIODS 150

/**
 * Width, in microseconds, of IDLE pulse.
 */
#define IDLE_HIGH_MICROS 1500

/**
 * PWM period, in milliseconds.
 */
#define PERIOD_MILLIS 20

/**
 * Width, in microseconds, of ACTION/CHANGE_MODE pulse.
 */
#define ACTION_OR_MODE_HIGH_MICROS 2000

/**
 * Initial value for PWR pin when no power supply control is used.
 */
#define NO_PWR_PIN 255

/**
 * Camera running/idle status when running
 */
#define CAMERA_RUNNING 1

/**
 * Camera running/idle status when idle
 */
#define CAMERA_IDLE 0

/**
 * Camera on/off status when on
 */
#define CAMERA_ON 1

/**
 * Camera on/off status when off
 */
#define CAMERA_OFF 0

/**
 * Camera mode status when on video mode
 */
#define MODE_VIDEO 0

/**
 * Camera mode status when on photo serial mode
 */
#define MODE_PHOTO_SERIAL 1

/**
 * Camera mode status when on photo single mode
 */
#define MODE_PHOTO_SINGLE 2

/**
 * A FCOEV2 camera, attached to a given digital output.
 */
class FCOEV2
{
private:
  // per object data
  /**
   * Current mode
   */
  uint8_t mode;

  /**
   * Running status (action started/ended)
   */
  uint8_t running;

  /**
   * Power status (on/off)
   */
  uint8_t on;

  /**
   * Pin used as output for PWM signal
   */
  uint8_t pwmPin;

  /**
   * Pin used as output for power supply control (on/off)
   */
  uint8_t pwrPin;

private:
  // private methods

  /**
   * Sending idle signal.
   */
  void
  idle();

  /**
   * Sending a custom signal, corresponding to a given pulse width repeated a given time.
   * @param pulseWidthMicros the pulse width in microseconds
   * @param periods the number of periods to generate
   */
  void
  signal(uint16_t pulseWidthMicros, uint8_t periods);

public:
  // public methods
  /**
   * Creates a new FCOEV2 instance, using digital IO <tt>pwmPin</tt> for PWM output.
   * @param pwmPin digital IO where FCOEV2 is attached
   */
  FCOEV2(uint8_t pwmPin);

  /**
   * Creates a new FCOEV2 instance, using digital IO <tt>pwmPin</tt> for PWM output
   * and digital IO <tt>pwrPin</tt> for PWR output.
   * @param pwmPin digital IO where FCOEV2 PWM is attached
   * @param pwmPin digital IO where FCOEV2 PWR is attached
   */
  FCOEV2(uint8_t pwmPin, uint8_t pwrPin);

  /**
   * Resets FCOEV2 instance mode to MODE_VIDEO
   */
  void
  resetMode();

  /**
   * Toggles (on/off) the action associated to current mode.
   */
  void
  toggleAction();

  /**
   * Switches to next operating mode.
   * N.B. after calling this method, an explicit pause of SWITCH_MODE_PAUSE_MILLIS
   * has to be done using delay, in order to ensure that camera has properly processed
   * the order.
   */
  void
  switchToNextMode();

  /**
   * Switches to given operating mode.
   * N.B. An explicit pause of SWITCH_MODE_PAUSE_MILLIS
   * is done using delay after each internal call to switchToNextMode
   * @param mode mode to switch to
   */
  void
  switchToMode(uint8_t mode);

  /**
   * Switches camera on.
   * N.B. after calling this method, an explicit pause of SWITCH_ON_PAUSE_MILLIS
   * has to be done using delay, in order to ensure that camera has powered up properly
   */
  void
  switchOn();

  /**
   * Switches camera off.
   */
  void
  switchOff();

  /**
   * Returns the current operating mode.
   */
  uint8_t
  getCurrentMode();

  /**
   * Returns running status, i.e. if action has been toggled on
   * (this applies only to MODE_VIDEO and MODE_PHOTO_SERIAL).
   *
   * @return <tt>true</tt> if action is in progress
   */
  boolean
  getRunningStatus();

  /**
   * Returns on/off status
   *
   * @return <tt>true</tt> if camera is on
   */
  boolean
  isOn();
};
#endif
