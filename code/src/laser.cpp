#include <laser.hpp>

r2d2::laser::laser_c::laser_c(hwlib::pin_out & laser_pin_out): laser_pin_out(laser_pin_out){
    laser_pin_out.write(1);
}


void r2d2::laser::laser_c::turn_on(){
    laser_pin_out.write(1);
}

void r2d2::laser::laser_c::turn_off(){
    laser_pin_out.write(0);
}