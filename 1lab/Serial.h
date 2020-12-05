#ifndef INC_1LAB_SERIAL_H
#define INC_1LAB_SERIAL_H

#include <iostream>

using namespace std;

class Serial {
public:
    pair<float, float> serial(float a = 1e-5, float b = 1e-4, int n_steps = 1e6);

    void run_serial(int n_steps = 1e6);
};

#endif