#pragma once

#include <hwlib.hpp>
#include <pca9685.hpp>
#include <sg90.hpp>
#include <laser.hpp>
#include <hc_sr04.hpp>
#include <cmath>

#define opposite_side 100
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
         * @param distance_sensor adds object for distance calculation
         * @param laser adds object to turn on and off je laser
         * @param x_axis_servo adds object to control the x axis servo
         * @param y_axis_servo adds object to control the y axis servo
         */
        laser_turret_controller_c(r2d2::sg90::sg90_c &x_axis_servo
                ,r2d2::sg90::sg90_c &y_axis_servo
                ,r2d2::laser::laser_c &laser
                ,r2d2::distance::hc_sr04_c &distance_sensor);

        /**
         * This methode updates the point the laser has to point at and also takes the distance in to account.
         *
         */
        void update();

        /**
         * This mathode changes the coordinate the laser has to point at.
         *
         * @param y y_axis of the grid
         * @param x x_axis of the grid
         */
        void point_at_coordinate_on_plane(int8_t x, int8_t y);

    private:
        r2d2::sg90::sg90_c &x_axis_servo;
        r2d2::sg90::sg90_c &y_axis_servo;
        r2d2::laser::laser_c &laser;
        r2d2::distance::hc_sr04_c &distance_sensor;

        float os = opposite_side/2;
        float grid_steps = (os / (grid_size/2));

        int8_t coordinate_x = 0;
        int8_t coordinate_y = 0;

    };
} // namespace r2d2::laser_turret_controller
