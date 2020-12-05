#ifndef INC_1LAB_PARALLEL_H
#define INC_1LAB_PARALLEL_H

#include <iostream>

using namespace std;

class Parallel {
public:
    pair<float, float> atomic(float a = 1e-5, float b = 1e-4, int n_steps = 1e6, int n_thread = 2);
    pair<float, float> critical(float a = 1e-5, float b = 1e-4, int n_steps = 1e6, int n_thread = 2);
    pair<float, float> lock(float a = 1e-5, float b = 1e-4, int n_steps = 1e6, int n_thread = 2);
    pair<float, float> reduction(float a = 1e-5, float b = 1e-4, int n_steps = 1e6, int n_thread = 2);

    void run_atomic(int n_steps = 1e6, int n_thread = 2);
    void run_critical(int n_steps = 1e6, int n_thread = 2);
    void run_lock(int n_steps = 1e6, int n_thread = 2);
    void run_reduction(int n_steps = 1e6, int n_thread = 2);
};

#endif