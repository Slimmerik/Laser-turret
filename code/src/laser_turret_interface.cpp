#include <laser_turret_interface.hpp>

r2d2::laser_turret_interface::laser_turret_interface_c::laser_turret_interface_c(r2d2::sg90::sg90_c &x_axis_servo
,r2d2::sg90::sg90_c &y_axis_servo
,r2d2::laser::laser_c &laser
,r2d2::distance::hc_sr04_c &distance_sensor)
    :x_axis_servo(x_axis_servo)
    ,y_axis_servo(y_axis_servo)
    ,laser(laser)
    ,distance_sensor(distance_sensor)
{
    laser.turn_on();
}


void r2d2::laser_turret_interface::laser_turret_interface_c::update(){
    //update distance
    int16_t distance = distance_sensor.get_distance();
    if(distance >= min_distance_plane && distance <= max_distance_plane ){
        int16_t adjacent_side = turret_to_echo + distance;
        float as = adjacent_side;
        hwlib::wait_ms(100);
        if(coordinate_x > 0){
            float x_axis = atan(grid_steps * coordinate_x/as);
            x_axis = (x_axis*180.0f/M_PI)*servo_multiplier;
            uint16_t final_servo_position = servo_middle_of_field_x + (x_axis) ;
            x_axis_servo.move_servo_to_degrees(final_servo_position);
        }else{
            float coordinate_multiplier = coordinate_x*-1;
            float x_axis = atan(grid_steps * coordinate_multiplier/as);
            x_axis = (x_axis*180.0f/M_PI)*servo_multiplier;
            uint16_t final_servo_position = servo_middle_of_field_x - (x_axis);
            x_axis_servo.move_servo_to_degrees(final_servo_position);
        }
        hwlib::wait_ms(100);
        if(coordinate_y > 0){
            float x_axis = atan(grid_steps * coordinate_y/as);
            x_axis = (x_axis*180.0f/M_PI)*servo_multiplier;
            uint16_t final_servo_position = servo_middle_of_field_y + (x_axis);
            y_axis_servo.move_servo_to_degrees(final_servo_position);
        }else{
            float coordinate_multiplier = coordinate_y*-1;
            float x_axis = atan(grid_steps * coordinate_multiplier/as);
            x_axis = (x_axis*180.0f/M_PI)*servo_multiplier;
            uint16_t final_servo_position = servo_middle_of_field_y - (x_axis);
            y_axis_servo.move_servo_to_degrees(final_servo_position);
        }
    }
}


void r2d2::laser_turret_interface::laser_turret_interface_c::point_at_coordinate_on_plane(int8_t x, int8_t y){
    coordinate_x = x;
    coordinate_y = y;
}