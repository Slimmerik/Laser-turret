#include <laser.hpp>

r2d2::laser::laser_c::laser_c(uint8_t gpio): gpio_port(gpio){
    PIOB->PIO_OER = { 0x1U << gpio_port };
    PIOB->PIO_CODR = 0x01 << gpio_port;
}


void r2d2::laser::laser_c::turn_on(){
    PIOB->PIO_SODR = 0x01 << gpio_port;
}

void r2d2::laser::laser_c::turn_off(){
    PIOB->PIO_CODR = 0x01 << gpio_port;
}