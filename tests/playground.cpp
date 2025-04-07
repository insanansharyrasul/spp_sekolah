#include <iostream>
using namespace std;

const time_t current_time = time(0);
const int SEKOLAH_ID = 91100000;

int hash_id(int id) {
   struct tm* timeinfo = localtime(&current_time);
   int current_year = ((timeinfo->tm_year + 1900) % 100) * 1000;
   return SEKOLAH_ID + current_year + id;
}

int main() {
    int id = 10;
    int hashed_id = hash_id(id);
    cout << "Hashed ID: " << hashed_id << endl;

    return 0;
}

