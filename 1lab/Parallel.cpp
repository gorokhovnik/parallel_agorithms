#include <iostream>
#include <cmath>
#include "chrono"
#include "omp.h"
#include "Parallel.h"

using namespace std;

pair<float, float> Parallel::atomic(float a, float b, int n_steps, int n_thread) {
    pair<float, float> result;
    float tmp, eps = (b - a) / n_steps;

    auto start = chrono::high_resolution_clock::now();

    float s = 0;
#pragma omp parallel for num_threads(n_thread) private(tmp)
    for (int x = 0; x < n_steps; x++) {
        tmp = (1 / pow(a + eps * x, 2)) * pow(sin(1 / (a + eps * x)), 2);
#pragma omp atomic
        s += tmp;
    };

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    result.first = duration.count() / 1000;
    result.second = s * eps;
    return result;
};

pair<float, float> Parallel::critical(float a, float b, int n_steps, int n_thread) {
    pair<float, float> result;
    float tmp, eps = (b - a) / n_steps;

    auto start = chrono::high_resolution_clock::now();

    float s = 0;
#pragma omp parallel for num_threads(n_thread) private(tmp)
    for (int x = 0; x < n_steps; x++) {
        tmp = (1 / pow(a + eps * x, 2)) * pow(sin(1 / (a + eps * x)), 2);
#pragma omp critical
        s += tmp;
    };

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    result.first = duration.count() / 1000;
    result.second = s * eps;
    return result;
};

pair<float, float> Parallel::lock(float a, float b, int n_steps, int n_thread) {
    pair<float, float> result;
    float tmp, eps = (b - a) / n_steps;

    auto start = chrono::high_resolution_clock::now();

    float s = 0;
    omp_lock_t lock;
    omp_init_lock(&lock);
#pragma omp parallel for num_threads(n_thread) private(tmp)
    for (int x = 0; x < n_steps; x++) {
        tmp = (1 / pow(a + eps * x, 2)) * pow(sin(1 / (a + eps * x)), 2);
        omp_set_lock(&lock);
        s += tmp;
        omp_unset_lock(&lock);
    };
    omp_destroy_lock(&lock);

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    result.first = duration.count() / 1000;
    result.second = s * eps;
    return result;
};

pair<float, float> Parallel::reduction(float a, float b, int n_steps, int n_thread) {
    pair<float, float> result;
    float tmp, eps = (b - a) / n_steps;

    auto start = chrono::high_resolution_clock::now();

    float s = 0;

#pragma omp parallel num_threads(n_thread) private(tmp)
    {
#pragma omp for reduction(+:s)
        for (int x = 0; x < n_steps; x++) {
            tmp = (1 / pow(a + eps * x, 2)) * pow(sin(1 / (a + eps * x)), 2);
            s += tmp;
        };
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    result.first = duration.count() / 1000;
    result.second = s * eps;
    return result;
};

void Parallel::run_atomic(int n_steps, int n_thread) {
    Parallel a;
    pair<float, float> atomic_result;
    cout << "Atomic " << n_thread << " threads:\n";
    atomic_result = a.atomic(1e-5, 1e-4, n_steps, n_thread);
    cout << "Time: " << atomic_result.first << "\tResult: " << atomic_result.second << endl;
    atomic_result = a.atomic(1e-4, 1e-3, n_steps, n_thread);
    cout << "Time: " << atomic_result.first << "\tResult: " << atomic_result.second << endl;
    atomic_result = a.atomic(1e-3, 1e-2, n_steps, n_thread);
    cout << "Time: " << atomic_result.first << "\tResult: " << atomic_result.second << endl;
    atomic_result = a.atomic(1e-2, 1e-1, n_steps, n_thread);
    cout << "Time: " << atomic_result.first << "\tResult: " << atomic_result.second << endl;
    atomic_result = a.atomic(0.1, 1, n_steps, n_thread);
    cout << "Time: " << atomic_result.first << "\tResult: " << atomic_result.second << endl;
    atomic_result = a.atomic(1, 10, n_steps, n_thread);
    cout << "Time: " << atomic_result.first << "\tResult: " << atomic_result.second << endl;
    atomic_result = a.atomic(10, 100, n_steps, n_thread);
    cout << "Time: " << atomic_result.first << "\tResult: " << atomic_result.second << endl;
}

void Parallel::run_critical(int n_steps, int n_thread) {
    Parallel a;
    pair<float, float> critical_result;
    cout << "Critical " << n_thread << " threads:\n";
    critical_result = a.critical(1e-5, 1e-4, n_steps, n_thread);
    cout << "Time: " << critical_result.first << "\tResult: " << critical_result.second << endl;
    critical_result = a.critical(1e-4, 1e-3, n_steps, n_thread);
    cout << "Time: " << critical_result.first << "\tResult: " << critical_result.second << endl;
    critical_result = a.critical(1e-3, 1e-2, n_steps, n_thread);
    cout << "Time: " << critical_result.first << "\tResult: " << critical_result.second << endl;
    critical_result = a.critical(1e-2, 1e-1, n_steps, n_thread);
    cout << "Time: " << critical_result.first << "\tResult: " << critical_result.second << endl;
    critical_result = a.critical(0.1, 1, n_steps, n_thread);
    cout << "Time: " << critical_result.first << "\tResult: " << critical_result.second << endl;
    critical_result = a.critical(1, 10, n_steps, n_thread);
    cout << "Time: " << critical_result.first << "\tResult: " << critical_result.second << endl;
    critical_result = a.critical(10, 100, n_steps, n_thread);
    cout << "Time: " << critical_result.first << "\tResult: " << critical_result.second << endl;
}

void Parallel::run_lock(int n_steps, int n_thread) {
    Parallel a;
    pair<float, float> lock_result;
    cout << "Lock " << n_thread << " threads:\n";
    lock_result = a.lock(1e-5, 1e-4, n_steps, n_thread);
    cout << "Time: " << lock_result.first << "\tResult: " << lock_result.second << endl;
    lock_result = a.lock(1e-4, 1e-3, n_steps, n_thread);
    cout << "Time: " << lock_result.first << "\tResult: " << lock_result.second << endl;
    lock_result = a.lock(1e-3, 1e-2, n_steps, n_thread);
    cout << "Time: " << lock_result.first << "\tResult: " << lock_result.second << endl;
    lock_result = a.lock(1e-2, 1e-1, n_steps, n_thread);
    cout << "Time: " << lock_result.first << "\tResult: " << lock_result.second << endl;
    lock_result = a.lock(0.1, 1, n_steps, n_thread);
    cout << "Time: " << lock_result.first << "\tResult: " << lock_result.second << endl;
    lock_result = a.lock(1, 10, n_steps, n_thread);
    cout << "Time: " << lock_result.first << "\tResult: " << lock_result.second << endl;
    lock_result = a.lock(10, 100, n_steps, n_thread);
    cout << "Time: " << lock_result.first << "\tResult: " << lock_result.second << endl;
}

void Parallel::run_reduction(int n_steps, int n_thread) {
    Parallel a;
    pair<float, float> reduction_result;
    cout << "Reduction " << n_thread << " threads:\n";
    reduction_result = a.reduction(1e-5, 1e-4, n_steps, n_thread);
    cout << "Time: " << reduction_result.first << "\tResult: " << reduction_result.second << endl;
    reduction_result = a.reduction(1e-4, 1e-3, n_steps, n_thread);
    cout << "Time: " << reduction_result.first << "\tResult: " << reduction_result.second << endl;
    reduction_result = a.reduction(1e-3, 1e-2, n_steps, n_thread);
    cout << "Time: " << reduction_result.first << "\tResult: " << reduction_result.second << endl;
    reduction_result = a.reduction(1e-2, 1e-1, n_steps, n_thread);
    cout << "Time: " << reduction_result.first << "\tResult: " << reduction_result.second << endl;
    reduction_result = a.reduction(0.1, 1, n_steps, n_thread);
    cout << "Time: " << reduction_result.first << "\tResult: " << reduction_result.second << endl;
    reduction_result = a.reduction(1, 10, n_steps, n_thread);
    cout << "Time: " << reduction_result.first << "\tResult: " << reduction_result.second << endl;
    reduction_result = a.reduction(10, 100, n_steps, n_thread);
    cout << "Time: " << reduction_result.first << "\tResult: " << reduction_result.second << endl;
}
