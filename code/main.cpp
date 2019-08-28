#include <hwlib.hpp>
#include <pca9685.hpp>
#include <i2c_bus.hpp>
#include <sg90.hpp>
#include <laser.hpp>
#include <hc_sr04.hpp>
#include <laser_turret_interface.hpp>

int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);

    //servo obj
    auto i2c = r2d2::i2c::i2c_bus_c(r2d2::i2c::i2c_bus_c::interface::interface_1, 400000);
    r2d2::pca9685::pca9685_c pca = r2d2::pca9685::pca9685_c(i2c);
    uint8_t servo_0 = 0;
    uint8_t servo_4 = 4;
    r2d2::sg90::sg90_c sg90_x = r2d2::sg90::sg90_c(servo_0, pca);
    r2d2::sg90::sg90_c sg90_y = r2d2::sg90::sg90_c(servo_4, pca);

    //laser obj
    auto laser_pin_out = hwlib::target::pin_out(hwlib::target::pins::d13);
    r2d2::laser::laser_c laser = r2d2::laser::laser_c(laser_pin_out);

    sg90_x.move_servo_to_degrees(900);
    hwlib::wait_ms(1000);
    sg90_y.move_servo_to_degrees(900);
    hwlib::wait_ms(5000);

    //distance obj
    auto echo_pin = hwlib::target::pin_in(hwlib::target::pins::d7);
    auto trigger_pin = hwlib::target::pin_out(hwlib::target::pins::d8);
    r2d2::distance::hc_sr04_c sensor = r2d2::distance::hc_sr04_c(echo_pin, trigger_pin);

    //turret obj
    r2d2::laser_turret_interface::laser_turret_interface_c turret =
            r2d2::laser_turret_interface::laser_turret_interface_c(sg90_x, sg90_y, laser, sensor);

    while (1){
        hwlib::cout << "enter the loop\n";
        turret.point_at_coordinate_on_plane(5,5);
        turret.update();
        hwlib::wait_ms(200);
        turret.point_at_coordinate_on_plane(5,0);
        turret.update();
        hwlib::wait_ms(200);
        turret.point_at_coordinate_on_plane(5,-5);
        turret.update();
        hwlib::wait_ms(200);
        turret.point_at_coordinate_on_plane(0,5);
        turret.update();
        hwlib::wait_ms(200);
        turret.point_at_coordinate_on_plane(0,0);
        turret.update();
        hwlib::wait_ms(200);
        turret.point_at_coordinate_on_plane(0,-5);
        turret.update();
        hwlib::wait_ms(200);
        turret.point_at_coordinate_on_plane(-5,5);
        turret.update();
        hwlib::wait_ms(200);
        turret.point_at_coordinate_on_plane(-5,0);
        turret.update();
        hwlib::wait_ms(200);
        turret.point_at_coordinate_on_plane(-5,-5);
        turret.update();
        hwlib::wait_ms(400);
    }
}