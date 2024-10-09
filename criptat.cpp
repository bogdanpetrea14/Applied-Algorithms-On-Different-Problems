#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

ifstream fin("criptat.in");
ofstream fout("criptat.out");

const int MAX_WORD_LENGTH = 200;

/*
Calculate the frequency of each letter that appears in the word
It updates the global array of frequencies
*/
void calculate_frequency(int freq[], char* word) {
    for (size_t i = 0; i < strlen(word); i++) {
        freq[word[i] - 'a']++;
    }
}

/*
Calculates the occurences of the letter in the word
and return that number
*/
int occurences_of_letter(char* word, char letter) {
    int occurences = 0;
    for (size_t i = 0; i < strlen(word); i++) {
        if (word[i] == letter) {
            occurences++;
        }
    }
    return occurences;
}

/*
It compares the tho words, based on the most_freq_letter.
The comparison is made by the raport of occurences of that letter
and the length of the word.
*/
int compare(char* word1, char* word2, char most_freq_letter) {
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    double ratio1, ratio2;
    ratio1 = (double)occurences_of_letter(word1, most_freq_letter) / len1;
    ratio2 = (double)occurences_of_letter(word2, most_freq_letter) / len2;
    if (ratio1 < ratio2) return 1;
    if (ratio1 > ratio2) return -1;
    return 0;
}

/*
Sorting the list of words based on the most frequent letter.
It sorts the words in descending order (Basically, if one word has the ratio bigger,
it alows us to add other words that don't even have that letter). After, we put
the words descending by length.
*/
void sort_words(char** words, int n, char let) {
    char* aux = new char[MAX_WORD_LENGTH];
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (compare(words[i], words[j], let) > 0) {
                // deep copy
                strcpy(aux, words[i]);
                strcpy(words[i], words[j]);
                strcpy(words[j], aux);
            } else if (compare(words[i], words[j], let) == 0) {
                if (strlen(words[j]) > strlen(words[i])) {
                    strcpy(aux, words[i]);
                    strcpy(words[i], words[j]);
                    strcpy(words[j], aux);
                }
            }
        }
    }
    delete[] aux;
}

/*
Calculates the length of the password, that has the most
frequent letter as the letter.
*/
int final_len_on_letter(char** words, int n, char letter) {
    sort_words(words, n, letter);
    int len_of_password = 0;
    int occurences_of_let = 0;
    for (int i = 0; i < n; i++) {
        len_of_password += strlen(words[i]);
        occurences_of_let += occurences_of_letter(words[i], letter);
        double ratio = (double)occurences_of_let / len_of_password;
        if (ratio <= 0.5) {
            len_of_password -= strlen(words[i]);
            occurences_of_let -= occurences_of_letter(words[i], letter);
            continue;
        }
    }

    return len_of_password;
}

int main() {
    int freq[26] = {0};
    int n;
    fin >> n;
    char** words = new char*[n];
    if (!words) {
        cout << "Nu s-a putut aloca memorie pentru cuvinte";
        return -1;
    }
    for (int i = 0; i < n; i++) {
        words[i] = new char[MAX_WORD_LENGTH];
        if (!words[i]) {
            cout << "Nu s-a putut aloca memorie pentru cuvinte";
            return -1;
        }
        fin >> words[i];
        calculate_frequency(freq, words[i]);
    }

    int lens1[8] = {0};
    int j = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] != 0) {
            lens1[j] = final_len_on_letter(words, n, char('a' + i));
            j++;
        }
    }

    int max_len = 0;
    for (int i = 0; i < 8; i++) {
        if (max_len < lens1[i]) {
            max_len = lens1[i];
        }
    }
    fout << max_len;

    for (int i = 0; i < n; i++) {
        delete[] words[i];
    }
    delete[] words;
    fin.close();
    fout.close();

    return 0;
}
