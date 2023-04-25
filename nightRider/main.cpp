#include <iostream>
#include <cmath>
#include <b15f/b15f.h>

int main() {
    B15F &drv = B15F::getInstance();

    int delay = 90; // ms
    int output_knightrider = 1;
    bool moveLeft_knighrider = true;
    int prevMode = -1;

    bool abort = false;
    while (!abort) {
        int dip = drv.readDipSwitch();
        abort = dip & 1;

        int mode = dip >> 7;
        if (mode != prevMode) {
            switch (mode) {
                case 0:
                    std::cout << "K.I.T.T., I need you, buddy!" << std::endl;
                    break;
                case 1:
                    std::cout
                            << "'Well, if you were directly above him, how could you see him?' 'Because I was inverted.'"
                            << std::endl;
                    break;
            }
        }
        prevMode = mode;

        switch (mode) {
            case 0: // display k.i.t.t.-esque led "animation"
                drv.digitalWrite0(output_knightrider);
                if (moveLeft_knighrider) {
                    output_knightrider <<= 1;
                    if (output_knightrider >= 128) {
                        moveLeft_knighrider = false;
                    }
                } else {
                    output_knightrider >>= 1;
                    if (output_knightrider <= 1) {
                        moveLeft_knighrider = true;
                    }
                }
                drv.delay_ms(delay);
                break;
            case 1: // invert signal from input
                drv.digitalWrite0(~drv.digitalRead0());
                break;
            default:
                abort = true;
                std::cout << "aborting just to be sure. something isn't mathing." << std::endl;
                break;
        }
    }

    drv.digitalWrite0(0);
    std::cout << "bye" << std::endl;
}
