#include <hwlib.hpp>
#include <pca9685.hpp>

#pragma once

#define sg90_max_duty_cycle 1450
#define sg90_min_duty_cycle 550
#define servo_range_in_degrees 180

namespace r2d2::sg90 {
    class sg90_c {
    public:
        /**
         * The constructor of the sg90 object
         *
         * @param pwm_controller This parameter assigns the pwm controller to the pwm controller
         * @param pwm_port This parameter assigns the sg90 object the correct pwm port
         */
        sg90_c(uint8_t &pwm_port, r2d2::pca9685::pca9685_c &pwm_controller);

        /**
         * The move_servo_to_degrees method moves the servo x degrees from the 0 point
         *
         * @param degrees This parameter
         */
        void move_servo_to_degrees(uint16_t degrees);

        /**
         * This method returns the position of the servo in degrees by taking the duty cycle stop form pca9685.
         *
         * @return returns the position of the servo in degrees.
         */
        uint16_t get_servo_position();

    private:
        uint8_t pwm_port = 0;
        r2d2::pca9685::pca9685_c &pwm_controller;

    };
} // namespace r2d2::sg90
