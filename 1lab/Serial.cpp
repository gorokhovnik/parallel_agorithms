#include <iostream>
#include <cmath>
#include "chrono"
#include "Serial.h"

using namespace std;

pair<float, float> Serial::serial(float a, float b, int n_steps) {
    pair<float, float> result;
    float tmp, eps = (b - a) / n_steps;

    auto start = chrono::high_resolution_clock::now();

    float s = 0;
    for (int x = 0; x < n_steps; x++) {
        tmp = (1 / pow(a + eps * x, 2)) * pow(sin(1 / (a + eps * x)), 2);
        s += tmp;
    };

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    result.first = duration.count() / 1000;
    result.second = s * eps;
    return result;
};

void Serial::run_serial(int n_steps) {
    Serial a;
    pair<float, float> serial_result;
    cout << "Serial:\n";
    serial_result = a.serial(1e-5, 1e-4, n_steps);
    cout << "Time: " << serial_result.first << "\tResult: " << serial_result.second << endl;
    serial_result = a.serial(1e-4, 1e-3, n_steps);
    cout << "Time: " << serial_result.first << "\tResult: " << serial_result.second << endl;
    serial_result = a.serial(1e-3, 1e-2, n_steps);
    cout << "Time: " << serial_result.first << "\tResult: " << serial_result.second << endl;
    serial_result = a.serial(1e-2, 1e-1, n_steps);
    cout << "Time: " << serial_result.first << "\tResult: " << serial_result.second << endl;
    serial_result = a.serial(0.1, 1, n_steps);
    cout << "Time: " << serial_result.first << "\tResult: " << serial_result.second << endl;
    serial_result = a.serial(1, 10, n_steps);
    cout << "Time: " << serial_result.first << "\tResult: " << serial_result.second << endl;
    serial_result = a.serial(10, 100, n_steps);
    cout << "Time: " << serial_result.first << "\tResult: " << serial_result.second << endl;
}
