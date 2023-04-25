#include <iostream>
#include <cmath>
#include <b15f/b15f.h>

int main() {
    B15F &drv = B15F::getInstance();

    int primes[8] = {2, 3, 5, 7, 11, 13, 17, 19};

    std::cout << "I'm optimus prime, and I'm here to save the day!" << std::endl;

    for (int p: primes) {
        std::cout << p << std::endl;
        drv.analogWrite0(
                (p * 0.1) / (5.0 / 1023.0)
        );
        drv.delay_ms(1750);
    }

    drv.analogWrite0(0);
}
