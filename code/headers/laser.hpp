#pragma once

#include <hwlib.hpp>

namespace r2d2::laser {
    class laser_c {
    public:
        /**
         * The constructor of the laser object
         *
         * @param laser_pin_out This is the pin out of the laser.
         */
        laser_c(hwlib::pin_out & laser_pin_out);

        /**
         * Turn on the laser.
         */
        void turn_on();

        /**
         * Turn off the laser.
         */
        void turn_off();

    private:
        hwlib::pin_out & laser_pin_out;
    };
} // namespace r2d2::sg90
