#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;
#define tolerance 1e-3

ifstream fin("servere.in");
ofstream fout("servere.out");

// Function for reading the input
void read_input(double *server_power, double *server_limit,
                                    double number_of_servers) {
    for (int i = 0; i < number_of_servers; i++) {
        fin >> server_power[i];
    }
    for (int i = 0; i < number_of_servers; i++) {
        fin >> server_limit[i];
    }
}

// Find the minimum limit of the servers
double find_minimum(double *server_limit, int number_of_servers) {
    double minimum = server_limit[0];
    for (int i = 1; i < number_of_servers; i++) {
        minimum = min(minimum, server_limit[i]);
    }
    return minimum;
}

// Find the maximum limit of the servers
double find_maximum(double *server_limit, int number_of_servers) {
    double maximum = server_limit[0];
    for (int i = 1; i < number_of_servers; i++) {
        maximum = max(maximum, server_limit[i]);
    }
    return maximum;
}

/*
Function to find the power of each server that is powered with
power, and return the minimum result. (The minimum after we calculate
the power for each server)
*/
double find_power(double *server_power, double *server_limit,
                            int number_of_servers, double power) {
    double min_power = 1e10;
    for (int i = 0; i < number_of_servers; i++) {
        if (server_power[i] - abs(power - server_limit[i]) < min_power) {
            min_power = server_power[i] - abs(power - server_limit[i]);
        }
    }
    return min_power;
}


/*
Binary search function to find the final power. We firstly power all the servers
with the middle power. After, we add a little more power to all servers and see
how the power changes. Based on that, we decide if we need to increase or decrease
*/
double find_final_power(double *server_power, double *server_limit,
                                                int number_of_servers) {
    double min = find_minimum(server_limit, number_of_servers);
    double max = find_maximum(server_limit, number_of_servers);
    double best_power = 0;
    while (max - min > tolerance) {
        double mid = (min + max) / 2;
        double power = find_power(server_power, server_limit,
                                  number_of_servers, mid);
        double next_power = find_power(server_power, server_limit,
                            number_of_servers, mid + tolerance);
        if (next_power > power) {
            best_power = power;
            min = mid + tolerance;
        } else {
            max = mid;
        }
    }
    return best_power;
}

int main() {
    // prima linie numarul de servere
    // a doua linie, puterile de calcul ale serverelor
    // a treia linie, limitele de alimentare ale serverelor

    int number_of_servers;
    fin >> number_of_servers;
    double *server_power = new (nothrow) double[number_of_servers];
    double *server_limit = new (nothrow) double[number_of_servers];
    if (server_power == nullptr || server_limit == nullptr) {
        fout<<"Eroare la alocare";
        return -1;
    }
    read_input(server_power, server_limit, number_of_servers);

    fout << fixed << setprecision(1)
         << find_final_power(server_power, server_limit, number_of_servers);
    fin.close();
    fout.close();
    delete[] server_power;
    delete[] server_limit;
    return 0;
}
