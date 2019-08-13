#include <sg90.hpp>

r2d2::sg90::sg90_c::sg90_c(uint8_t &pwm_port, r2d2::pca9685::pca9685_c &pwm_controller)
    : pwm_port(pwm_port), pwm_controller(pwm_controller){
    uint16_t duty_cycle_start = 0;
    pwm_controller.write_duty_cycle_start(pwm_port, duty_cycle_start); //set start duty cycle to 0
}

void r2d2::sg90::sg90_c::move_servo_to_degrees(uint16_t degrees){
    uint16_t def_degrees = 0;
    if(degrees > servo_range_in_degrees){
        def_degrees = servo_range_in_degrees;
    } else {
        def_degrees = degrees;
    }

    uint16_t duty_cycle_servo_range = sg90_max_duty_cycle - sg90_min_duty_cycle;
    float degrees_steps = (duty_cycle_servo_range / servo_range_in_degrees);
    pwm_controller.write_duty_cycle_stop(pwm_port, static_cast<uint16_t>(sg90_min_duty_cycle + (degrees_steps*def_degrees)));
}

uint16_t r2d2::sg90::sg90_c::get_servo_position(){
    uint16_t duty_cycle = pwm_controller.read_duty_cycle_stop(pwm_port);
    uint16_t duty_cycle_servo_range = sg90_max_duty_cycle - sg90_min_duty_cycle;
    float degrees_steps = (duty_cycle_servo_range / servo_range_in_degrees);
    float degrees = ((duty_cycle - sg90_min_duty_cycle) / degrees_steps);
    return static_cast<uint16_t>(degrees);
}