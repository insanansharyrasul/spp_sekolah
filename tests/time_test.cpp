#include <ctime>
#include <iostream>
using namespace std;

int main() {
    time_t apa;
    time(&apa);

    cout << ctime(&apa) << endl;
}