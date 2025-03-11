#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to randomly assign weights to coins, with one fake coin
void assignRandomWeights(int coins[], int n) {
    int fakeIndex = rand() % n;
    int fakeWeight = rand() % 2 == 0 ? 9 : 11;  // Either lighter (9) or heavier (11)

    for (int i = 0; i < n; ++i) {
        coins[i] = 10;
    }

    coins[fakeIndex] = fakeWeight;  // Assign the fake coin its weight
}

void findFakeCoin(int coins[]) {
    // First, check if all three coins have the same weight
    if (coins[0] == coins[1] && coins[1] == coins[2]) {
        cout << "All three coins have the same weight. Unable to identify a fake coin." << endl;
        return;
    }

    cout << "Comparing coin A and coin B..." << endl;

    if (coins[0] == coins[1]) {
        // If A and B are equal, C must be fake
        cout << "A and B are equal. C is the fake coin." << endl;
        cout << "Comparing coin C with coin A..." << endl;

        if (coins[2] > coins[0]) {
            cout << "C is heavier." << endl;
        } else {
            cout << "C is lighter." << endl;
        }
    } else {
        // If A and B are different, one of them is fake
        cout << "A and B are not equal." << endl;
        cout << "Comparing coin A with coin C..." << endl;

        if (coins[0] == coins[2]) {
            // If A and C are equal, B is fake
            cout << "A and C are equal. B is the fake coin." << endl;

            if (coins[1] > coins[0]) {
                cout << "B is heavier." << endl;
            } else {
                cout << "B is lighter." << endl;
            }
        } else {
            // Otherwise, A is fake
            cout << "A is the fake coin." << endl;

            if (coins[0] > coins[2]) {
                cout << "A is heavier." << endl;
            } else {
                cout << "A is lighter." << endl;
            }
        }
    }
}

int main() {
    srand(time(0));  // Seed for random number generation

    int coins[3];  // Array to store weights of three coins
    assignRandomWeights(coins, 3);  // Randomly assign weights to the coins

    cout << "Coin weights: A=" << coins[0] << ", B=" << coins[1] << ", C=" << coins[2] << endl;

    findFakeCoin(coins);  // Find and identify the fake coin

    return 0;
}
