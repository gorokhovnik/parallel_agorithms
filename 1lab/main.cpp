#include <iostream>
#include "Serial.h"
#include "Parallel.h"

using namespace std;

int main() {
    Serial s;
    s.run_serial(1e6);
    cout << endl;

    Parallel p;
    p.run_atomic(1e6, 2);
    cout << endl;
    p.run_critical(1e6, 2);
    cout << endl;
    p.run_lock(1e6, 2);
    cout << endl;
    p.run_reduction(1e6, 2);
    cout << endl;

    p.run_atomic(1e6, 4);
    cout << endl;
    p.run_critical(1e6, 4);
    cout << endl;
    p.run_lock(1e6, 4);
    cout << endl;
    p.run_reduction(1e6, 4);
    cout << endl;

    return 0;
}
