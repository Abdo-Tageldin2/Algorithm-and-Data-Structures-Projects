#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <limits>
using namespace std;

int main() {
    int L;

    // Input validation for line length
    cout << "Enter the maximum line length (L): ";
    if (!(cin >> L) || L <= 0) {
        cerr << "Error: Line length must be a positive integer." << endl;
        return 1;
    }
    cin.ignore(); // Ignore the newline character after the integer input

    string text;
    cout << "Enter the text: ";
    getline(cin, text);

    if (text.empty()) {
        cerr << "Error: Input text cannot be empty." << endl;
        return 1;
    }

    // Split the input text into words
    vector<string> words;
    stringstream ss(text);
    string word;
    while (ss >> word) {
        if (word.size() > static_cast<size_t>(L)) {
            cerr << "Error: Word '" << word << "' is longer than the maximum line length (" << L << ")." << endl;
            return 1;
        }
        words.push_back(word);
    }

    if (words.empty()) {
        cerr << "Error: No valid words found in the input text." << endl;
        return 1;
    }

    int n = words.size();
    vector<int> dp(n + 1, numeric_limits<int>::max()); // Minimum cost to format from word `i` to end
    vector<int> nxt(n + 1, -1); // Tracks the next word index for line breaks
    dp[n] = 0; // Base case: No cost for formatting an empty line

    // Dynamic programming to calculate minimum penalty cost
    for (int i = n - 1; i >= 0; i--) {
        int total = 0; // Total characters used in the current line
        for (int j = i; j < n; j++) {
            total += words[j].size();
            int used = total + (j - i); // Includes spaces between words
            if (used > L) break; // Stop if the line exceeds maximum length

            int cost = (j == n - 1) ? 0 : (L - used) * (L - used); // Penalty for extra spaces
            if (dp[j + 1] + cost < dp[i]) {
                dp[i] = dp[j + 1] + cost; // Update minimum cost
                nxt[i] = j + 1; // Record where to break the line
            }
        }
    }

    // Output the formatted text
    int idx = 0, lineNum = 1;
    cout << "\nFormatted text:\n";
    while (idx < n) {
        cout << "line " << lineNum++ << ":";
        for (int k = idx; k < nxt[idx]; k++) {
            cout << " " << words[k];
        }
        cout << "\n";
        idx = nxt[idx];
    }

    return 0;
}
