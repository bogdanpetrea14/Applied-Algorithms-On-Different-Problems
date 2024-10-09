#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <cstdint>

using namespace std;

#define MODULO 1000000007

struct Pairs {
    unsigned int x;
    char y;
};

ifstream fin("colorare.in");
ofstream fout("colorare.out");

void read_pairs(unsigned int& k, Pairs* pairs) {
    for (unsigned int i = 0; i < k; i++) {
        fin >> pairs[i].x >> pairs[i].y;
    }
}

int compress_pairs(unsigned int k, Pairs* pairs) {
    if (k == 0) return 0;  // If there are no pairs, return 0

    Pairs* new_pairs = new (nothrow) Pairs[k];
    if (new_pairs == nullptr) {
        cout << "Nu s-a putut aloca memorie pentru vectorul de perechi.";
        return -1;
    }

    int counter = 0;  // Counter for the new pairs
    new_pairs[0] = pairs[0];  // Initialize the first pair

    for (unsigned int i = 1; i < k; i++) {
        if (pairs[i].y == new_pairs[counter].y) {
            // If the blocks are of the same type, we add the lengths
            new_pairs[counter].x += pairs[i].x;
        } else {
            // Else, we move to the next pair
            counter++;
            new_pairs[counter] = pairs[i];
        }
    }

    // Counter is the last index of the new_pairs array
    int new_k = counter + 1;

    // Copy the new_pairs array to the pairs array
    for (int i = 0; i < new_k; i++) {
        pairs[i] = new_pairs[i];
    }

    // Free the memory
    delete[] new_pairs;

    return new_k;
}

uint64_t to_power(uint64_t base, uint64_t exponent) {
    uint64_t result = 1;
    while (exponent) {
        if (exponent % 2) {
            result = (result * base) % MODULO;
        }
        base = (base * base) % MODULO;
        exponent /= 2;
    }

    return result;
}

uint64_t final_result(int k, Pairs* pairs) {
    uint64_t result = 1;
    uint64_t v_values = 0;
    uint64_t h_values = 0;
    uint64_t inter_values = 0;

    for (int i = 0; i < k - 1; i++) {
        if ((pairs[i].y == 'H' && pairs[i + 1].y == 'V')
            || (pairs[i].y == 'V' && pairs[i + 1].y == 'H')) {
            inter_values++;
        }
    }

    size_t power_of_2 = 0;
    size_t power_of_3 = 0;

    if (pairs[0].y == 'V') {
        power_of_2 = pairs[0].x - 1;
        power_of_3 = 1;
    } else {
        power_of_3 = pairs[0].x;
        power_of_2 = 1;
    }
    for (int i = 1; i < k; i++) {
        if (pairs[i].y == 'V') {
            power_of_2 += pairs[i].x - 1;
            power_of_3 += 1;
        } else {
            power_of_3 += pairs[i].x;
            power_of_2 += 1;
        }
    }
    power_of_3 -= inter_values;
    uint64_t power_2_res = (to_power(2, power_of_2) % MODULO);
    uint64_t power_3_res = (to_power(3, power_of_3) % MODULO);
    result = (power_2_res * power_3_res) % MODULO;
    return result;
}

int main() {
    unsigned int k, new_k;
    fin >> k;
    Pairs* pairs = new (nothrow) Pairs[k];
    if (pairs == nullptr) {
        cout << "Nu s-a putut aloca memorie pentru vectorul de perechi.";
        return -1;
    }
    read_pairs(k, pairs);
    new_k = compress_pairs(k, pairs);

    fout << final_result(new_k, pairs) << endl;

    fin.close();
    fout.close();
    delete[] pairs;
    return 0;
}
