#include <iostream>
#include <fstream>
#include <b15f/b15f.h>

float toVolts(float reading) {
    return reading * (5.0 / 1023.0);
}

int main() {
    B15F &drv = B15F::getInstance();

    int inputPin = 2;
    int potiOne = 0;
    int potiTwo = 1;

    int mode = 0; // single input or potentiometers
    int prevMode = -1;

    int state = 0; // reading or not
    int prevState = -1;

    bool abort = false; // bit 0

    std::ofstream file;

    while (!abort) {
        int dip = drv.readDipSwitch();

        abort = dip & 1;
        state = (dip >> 1) & 1;
        mode = dip >> 7;

        if (mode != prevMode) {
            switch (mode) {
                case 0:
                    file.close();
                    std::cout << "[reading single input (" << inputPin
                              << ")] People are strange, When you're a stranger, Faces look ugly, When you're alone"
                              << std::endl;
                    file.open("plot_sofittenlampe.txt");
                    break;
                case 1:
                    file.close();
                    std::cout << "[reading potentiometers] Prepare for trouble. Make it double." << std::endl;
                    file.open("plot_potentiometers.txt");
                    break;
                default:
                    abort = true;
                    std::cout << "aborting just to be sure. something isn't mathing." << std::endl;
                    break;
            }
            prevMode = mode;
        }

        if (state != prevState) {
            switch (state) {
                case 0: // idle
                    std::cout
                            << "[idle] I'm wastin' my time, I got nothin' to do, I'm hangin' around, I'm waitin' for you"
                            << std::endl;
                    drv.digitalWrite0(0);
                    file.close();
                    break;
                case 1: // active
                    std::cout << "[active] Name it, read it, tune it, print it, scan it, send it, fax, rename it" << std::endl;
                    drv.digitalWrite0(0xFF);
                    break;
                default:
                    abort = true;
                    std::cout << "aborting just to be sure. something isn't mathing." << std::endl;
                    break;
            }
        }

        prevState = state;

        if (state) {
            switch (mode) {
                case 0: // single input
                    file << toVolts(drv.analogRead(inputPin)) << std::endl;
                    break;
                case 1: // potentiometers
                    file << toVolts(drv.analogRead(potiOne)) << "\t" << toVolts(drv.analogRead(potiTwo)) << std::endl;
                    break;
                default:
                    break;
            }
        }
    }

    file.close();
    drv.digitalWrite0(0);
    std::cout << "ok bye!" << std::endl;

    /* todo write to file
    while(1)
    {
        std::cout << drv.analogRead(2) * (5.0 / 1023.0) << std::endl;
        std::cout << drv.analogRead(0) * (5.0 / 1023.0);
        std::cout << "\t" << drv.analogRead(1) * (5.0 / 1023.0) << std::endl;

    }
    */
}

