#include <hwlib.hpp>
#include <pwm.hpp>
using namespace R2D2::pwm_lib;

int main() {
    hwlib::wait_ms(1000);
    auto pwm_0 = pwm_c(7); // construct a pwm channel
    auto pwm_1 = pwm_c(6); // construct a pwm channel
    auto pwm_2 = pwm_c(5); // construct a pwm channel
    pwm_0.select_frequency(
        frequencies::CLOCKA); // set pwm_0 to use CLOCKA ~ 50hz
    pwm_1.select_frequency(
        frequencies::CLOCKA); // set pwm_0 to use CLOCKA ~ 50hz
    pwm_2.select_frequency(
        frequencies::CLOCKA); // set pwm_0 to use CLOCKA ~ 50hz
    int _freq = 0;

    while (1) {
        hwlib::cout << "Type a frequency : " << hwlib::flush;

        char c = hwlib::cin.getc();
        while (c != 0xA) {
            _freq *= 10;
            _freq += atoi(&c);
            c = hwlib::cin.getc();
        }
        hwlib::cout << "_Freq == " << hwlib::dec << _freq << hwlib::endl;
        pwm_0.set_duty_cycle(_freq);
        pwm_1.set_duty_cycle(_freq);
        pwm_2.set_duty_cycle(_freq);
        _freq = 0;
    }
}