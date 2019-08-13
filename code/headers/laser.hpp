#include <hwlib.hpp>

#pragma once


namespace r2d2::laser {
    class laser_c {
    public:
        /**
         * The constructor of the laser object
         *
         */
        laser_c(uint8_t gpio);

        /**
         * Turn on the laser.
         */
        void turn_on();

        /**
         * Turn off the laser.
         */
        void turn_off();

    private:
        uint8_t gpio_port;
    };
} // namespace r2d2::sg90
