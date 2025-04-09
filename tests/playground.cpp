#include <iostream>
using namespace std;


const time_t current_time = time(0);
struct tm* timeinfo = localtime(&current_time);
int current_year_hash = ((timeinfo->tm_year + 1900) % 100) * 1000;
const int SEKOLAH_ID = 91100000;  // 5 zeros

int hash_id(int id) {
    return SEKOLAH_ID + current_year_hash + id;
}

int main() {
    int id = 10;
    int hashed_id = hash_id(id);
    cout << "Hashed ID: " << hashed_id << endl;

    return 0;
}

