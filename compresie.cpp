#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

ifstream fin("compresie.in");
ofstream fout("compresie.out");

int check_if_continue(int* a_values, int* b_values, int A, int B) {
    double sum_a = 0, sum_b = 0;
    for (int i = 0; i < A; i++) {
        sum_a += a_values[i];
    }
    for (int i = 0; i < B; i++) {
        sum_b += b_values[i];
    }
    if (sum_a == sum_b) {
        return 1;
    }
    return 0;
}

int transform_for_switch(int number) {
    if (number > 0) {
        return 1;
    } else if (number < 0) {
        return -1;
    }
    return 0;
}

int* generate_partial_sums(int n, int* values) {
    int* partial_sums = new (nothrow) int[n];
    if (partial_sums == nullptr) {
        cerr << "Nu s-a putut aloca memorie pentru vectorul de sume partiale.";
        return nullptr;
    }
    partial_sums[0] = values[0];
    for (int i = 1; i < n; i++) {
        partial_sums[i] = partial_sums[i - 1] + values[i];
    }
    return partial_sums;
}

int find_max_compress(int* a_partial, int* b_partial, int A, int B) {
    int counter = 0;
    int i = 0, j = 0;
    while (i < A && j < B) {
        if (a_partial[i] == b_partial[j]) {
            counter++;
            i++;
            j++;
        } else if (a_partial[i] < b_partial[j]) {
            i++;
        } else {
            j++;
        }
    }

    return counter;
}


int main() {
    int A, B;

    fin >> A;
    int* a_values = new (nothrow) int[A];
    if (a_values == nullptr) {
        cerr << "Nu s-a putut aloca memorie pentru vectorul de valori a.";
        return -1;
    }
    for (int i = 0; i < A; i++) {
        fin >> a_values[i];
    }

    fin >> B;
    int* b_values = new (nothrow) int[B];
    if (b_values == nullptr) {
        cerr << "Nu s-a putut aloca memorie pentru vectorul de valori b.";
        return -1;
    }
    for (int i = 0; i < B; i++) {
        fin >> b_values[i];
    }

    int* a_partial_sums = generate_partial_sums(A, a_values);
    int* b_partial_sums = generate_partial_sums(B, b_values);
    if (a_partial_sums == nullptr || b_partial_sums == nullptr) {
        return -1;
    }

    int check_value = check_if_continue(a_values, b_values, A, B);
    if (check_value) {
         fout << find_max_compress(a_partial_sums, b_partial_sums, A, B);
    } else {
        fout << -1;
    }
    fin.close();
    fout.close();
    delete[] a_values;
    delete[] b_values;
    return 0;
}
