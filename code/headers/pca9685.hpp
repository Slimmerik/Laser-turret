#pragma once

#include <hwlib.hpp>
#include <i2c_bus.hpp>

#define PCA9685_BASE 0x40
#define MODE1 0x00
#define MODE2 0x01
#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9
#define LED_SELECT_MULTIPLIER 4

namespace r2d2::pca9685 {
    class pca9685_c {
    public:

        /**
         * Constuctor method for the pca9685 object.
         *
         * @param i2c_bus this param represents the i2c bus used in for communication with the pca9685
         */
        pca9685_c(r2d2::i2c::i2c_bus_c &i2c_bus);

        /**
         * This method writes the start of the duty cycle for a given pwm port.
         *
         * @param duty_cicle_start This param represents the beginning of the duty cycle of the pmw port on the pca9685(0-4095)
         * @param pwm_port_number this parameter represents one of the 16 pwm ports on the pca9685 (0-15)
         */
        void write_duty_cycle_start(uint8_t pwm_port_number, uint16_t duty_cicle_start);

        /**
         * This method writes the stop of the duty cycle for a given pwm port.
         *
         * @param duty_cicle_stop This param represents the and of the duty cycle of the pmw port on the pca9685(0-4095)
         * @param pwm_port_number this parameter represents one of the 16 pwm ports on the pca9685 (0-15)
         */
        void write_duty_cycle_stop(uint8_t pwm_port_number, uint16_t duty_cicle_stop);

        /**
         * read_duty_cycle_stop reads pulse with form pca9685 if start of duty cycle is 0
         * (for use in servos the start of the duty cycle never has to change)
         *
         * @param pwm_port_number this parameter represents one of the 16 pwm ports on the pca9685 (0-15)
         */
        uint16_t read_duty_cycle_stop(uint8_t pwm_port_number);

        /**
         * read_duty_cycle_start reads pulse with form pca9685 if start of duty cycle is 0
         * (for use in servos the start of the duty cycle never has to change)
         *
         * @param pwm_port_number this parameter represents one of the 16 pwm ports on the pca9685 (0-15)
         */
        uint16_t read_duty_cycle_start(uint8_t pwm_port_number);

    private:
        r2d2::i2c::i2c_bus_c &i2c_bus;

        /**
         * This method initialize the pca9685 to run in the appropriate modes.
         */
        void init_pca9685();

    };
} // namespace r2d2::pca9685