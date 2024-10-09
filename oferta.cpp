#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

ifstream fin("oferta.in");
ofstream fout("oferta.out");

double group_last_2(int start, int end, double* prices) {
    // group last 2 prices and return the price with the discount
    // find the minimum of the two prices and give it 50% off
    double min_price = min(prices[start], prices[end]) * 0.5;
    double max_price = max(prices[start], prices[end]);
    return min_price + max_price;
}

double group_last_3(int start, int end, double* prices) {
    // group last 3 prices and return the price with the discount
    // find the minimum of the three prices and give it 100% off
    double min_price = min(prices[start], min(prices[start + 1], prices[end]));
    return (prices[start] + prices[start + 1] + prices[end] - min_price);
}

double group_first_3(double* prices) {
    double first = prices[0];
    double second = prices[1];
    double third = prices[2];
    double min1 = first + second + third - min(first, min(second, third));
    double min2 = group_last_2(0, 1, prices) + third;
    double min3 = group_last_2(1, 2, prices) + first;
    return min(min1, min(min2, min3));
}

double final_price(int n, double* prices) {
    double* dp = new double[n];
    // scriem cazurile de baza, pentru dp[0], dp[1] si dp[2]
    dp[0] = prices[0];
    dp[1] = group_last_2(0, 1, prices);
    dp[2] = group_first_3(prices);
    for (int i = 3; i < n; i++) {
        double keep_last_1 = dp[i - 1] + prices[i];
        double grp_last_2 = dp[i - 2] + group_last_2(i - 1, i, prices);
        double grp_last_3 = dp[i - 3] + group_last_3(i - 2, i, prices);
        dp[i] = min(keep_last_1, min(grp_last_2, grp_last_3));
    }

    double result = dp[n - 1];
    delete[] dp;
    return result;
}

int main() {
    // n, numarul de produse, si k, al catealea cel mai mic pret
    // a doua linie, preturile produselor, in ordinea de pe banda
    int n, k;
    fin >> n >> k;
    double* prices = new double[n];
    for (int i = 0; i < n; i++) {
        fin >> prices[i];
    }
    if (k > n) {
        fout << -1 << endl;
    } else {
        fout << fixed << setprecision(2) << final_price(n, prices) << endl;
    }

    fin.close();
    fout.close();

    delete[] prices;
    return 0;
}
