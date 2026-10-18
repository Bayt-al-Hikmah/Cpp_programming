// Counting Word Frequencies with unordered_map

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
    string sentence = "cat dog cat bird dog cat";

    unordered_map<string, int> frequency;

    istringstream input(sentence);

    string word;

    while (input >> word) {
        frequency[word]++;
    }

    cout << "Word frequencies:\n";

    for (const auto& entry : frequency) {
        cout << entry.first << ": "
             << entry.second << '\n';
    }

    return 0;
}