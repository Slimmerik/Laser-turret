#pragma once

#include <hwlib.hpp>
#include <pca9685.hpp>
#include <sg90.hpp>
#include <laser.hpp>
#include <hc_sr04.hpp>
#include <cmath>

#define opposite_side 100 //The physical size of the grid
#define turret_to_echo 100 //The distance from the turret to the distance sensor

#define min_distance_plane 100 //The minimal distance the system updates the servos
#define max_distance_plane 400 //The maximum distance the system updates the servos

#define M_PI 3.141592654 //PI
#define servo_middle_of_field_x 900 //Start point for servos
#define servo_middle_of_field_y 900 //Start point for servos
#define servo_multiplier 10 //To give the servos more steps the input value is *10 on the servo side

#define grid_size 10 //Range of coordinates, grid range with size 10 is 2d 5,-5



namespace r2d2::laser_turret_interface {
    class laser_turret_interface_c {
    public:

        /**
         * The constructor of the laser_turret_controller object.
         *
         * @param distance_sensor adds object for distance calculation
         * @param laser adds object to turn on and off je laser
         * @param x_axis_servo adds object to control the x axis servo
         * @param y_axis_servo adds object to control the y axis servo
         */
        laser_turret_interface_c(r2d2::sg90::sg90_c &x_axis_servo
                ,r2d2::sg90::sg90_c &y_axis_servo
                ,r2d2::laser::laser_c &laser
                ,r2d2::distance::hc_sr04_c &distance_sensor);

        /**
         * This method updates the point the laser has to point at and also takes the distance in to account.
         * This method updates the angle of the servos to point at the coordiantion that correlates to the physical
         * point on the grid.
         *
         *
         */
        void update();

        /**
         * This mathod changes the coordinate the laser has to point at on the grid.
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

        const float os = opposite_side/2;
        const float grid_steps = (os / (grid_size/2));

        int8_t coordinate_x = 0;
        int8_t coordinate_y = 0;

    };
} // namespace r2d2::laser_turret_controller
