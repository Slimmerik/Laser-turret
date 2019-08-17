#pragma once

#include <hwlib.hpp>
#include <pca9685.hpp>
#include <sg90.hpp>
#include <laser.hpp>
#include <hc_sr04.hpp>
#include <cmath>

#define opposite_side 50
#define turret_to_echo 100

#define min_distance_plane 100
#define max_distance_plane 400

#define M_PI 3.141592654
#define servo_middle_of_field_x 900
#define servo_middle_of_field_y 900
#define servo_multiplier 10

#define grid_size 10



namespace r2d2::laser_turret_controller {
    class laser_turret_controller_c {
    public:

        /**
         * The constructor of the laser_turret_controller object
         *
         */
        laser_turret_controller_c(r2d2::sg90::sg90_c &x_as_servo
                ,r2d2::sg90::sg90_c &y_as_servo
                ,r2d2::laser::laser_c &laser
                ,r2d2::distance::hc_sr04_c &distance_sensor);

        /**
         *
         */
        void update();

        /**
         *
         */
        void point_at_coordinate_on_plane(int8_t x, int8_t y);

    private:
        r2d2::sg90::sg90_c &x_as_servo;
        r2d2::sg90::sg90_c &y_as_servo;
        r2d2::laser::laser_c &laser;
        r2d2::distance::hc_sr04_c &distance_sensor;

        float os = opposite_side/2;
        float grid_steps = (os / (grid_size/2));

        int8_t coordinate_x = 0;
        int8_t coordinate_y = 0;

    };
} // namespace r2d2::laser_turret_controller
