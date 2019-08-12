#include <pca9685.hpp>


r2d2::pca9685::pca9685_c::pca9685_c(r2d2::i2c::i2c_bus_c &i2c_bus) : i2c_bus(i2c_bus){
    r2d2::pca9685::pca9685_c::init_pca9685();
}


void r2d2::pca9685::pca9685_c::write_duty_cycle_start(uint8_t pwm_port_number, uint16_t duty_cicle_start){
    //Split 16 bit int into 8 and (effectively)4 bit values.
    uint16_t start[1] = {duty_cicle_start};
    uint8_t start_first_8_bits[1];
    start_first_8_bits[0] = start[0] & 0xff;
    uint8_t start_next_4_bits[1];
    start_next_4_bits[0] = start[0] >> 8;

    //i2c write
    i2c_bus.write(PCA9685_BASE,start_first_8_bits,1, LED0_ON_L + (pwm_port_number * LED_SELECT_MULTIPLIER),1);
    i2c_bus.write(PCA9685_BASE,start_next_4_bits,1, LED0_ON_H + (pwm_port_number * LED_SELECT_MULTIPLIER),1);
}

void r2d2::pca9685::pca9685_c::write_duty_cycle_stop(uint8_t pwm_port_number, uint16_t duty_cicle_stop){
    //Split 16 bit int into 8 and (effectively)4 bit values.
    uint16_t duty_cicle_stop_value[1];
    duty_cicle_stop_value[0] = duty_cicle_stop;
    uint8_t duty_cicle_stop_first_8_bits[1];
    duty_cicle_stop_first_8_bits[0] = duty_cicle_stop_value[0] & 0xff;
    uint8_t duty_cicle_stop_next_4_bits[1];
    duty_cicle_stop_next_4_bits[0] = duty_cicle_stop_value[0] >> 8;

    //i2c write.
    i2c_bus.write(PCA9685_BASE,duty_cicle_stop_first_8_bits,1, LED0_OFF_L + (pwm_port_number * LED_SELECT_MULTIPLIER),1);
    i2c_bus.write(PCA9685_BASE,duty_cicle_stop_next_4_bits,1, LED0_OFF_H + (pwm_port_number * LED_SELECT_MULTIPLIER),1);
}

uint16_t r2d2::pca9685::pca9685_c::read_duty_cycle_stop(uint8_t pwm_port_number){
    uint8_t data_off_l[1];
    uint8_t data_off_h[1];
    uint16_t data_off_comb = 0;

    //read i2c
    i2c_bus.read(PCA9685_BASE,data_off_l,1,LED0_OFF_L + (pwm_port_number * LED_SELECT_MULTIPLIER),1);
    i2c_bus.read(PCA9685_BASE,data_off_h,1,LED0_OFF_H + (pwm_port_number * LED_SELECT_MULTIPLIER),1);

    //combine uint8_t to uint16_t
    data_off_comb = data_off_comb + static_cast<uint16_t>(data_off_h[0]);
    data_off_comb = data_off_comb << 8;
    data_off_comb = data_off_comb + static_cast<uint16_t>(data_off_l[0]);

    return data_off_comb;
}

uint16_t r2d2::pca9685::pca9685_c::read_duty_cycle_start(uint8_t pwm_port_number){
    uint8_t data_on_l[1];
    uint8_t data_on_h[1];
    uint16_t data_on_comb = 0;

    //read i2c
    i2c_bus.read(PCA9685_BASE,data_on_l,1,LED0_ON_L + (pwm_port_number * LED_SELECT_MULTIPLIER),1);
    i2c_bus.read(PCA9685_BASE,data_on_h,1,LED0_ON_H + (pwm_port_number * LED_SELECT_MULTIPLIER),1);

    //combine uint8_t to uint16_t
    data_on_comb = data_on_comb + static_cast<uint16_t>(data_on_h[0]);
    data_on_comb = data_on_comb << 8;
    data_on_comb = data_on_comb + static_cast<uint16_t>(data_on_l[0]);

    return data_on_comb;
}

void r2d2::pca9685::pca9685_c::init_pca9685(){
    uint8_t mode1[1];
    mode1[0] = 0x00;
    uint8_t mode2[1];
    mode2[0] = 0x04;
    i2c_bus.write(PCA9685_BASE,mode1,1,MODE1,1);
    i2c_bus.write(PCA9685_BASE,mode2,1,MODE2,1);
}

