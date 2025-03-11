#include <iostream>
#include <string>
using namespace std;

int main() {
    int n; // Variable to store the number of disks
    cout << "Enter the number of disks (n): "; // Prompt the user to input the number of disks
    cin >> n; // Read the user input

    // Ensure the input is valid (n must be greater than 0)
    while (n <= 0) {
        cout << "Please enter a number greater than 0: ";
        cin >> n;
    }

    int size = n; // Set the size of the array to n (no need to multiply by 2 as indicated in the comment)
    string* disks = new string[size]; // Dynamically allocate an array of strings to hold disk colors

    // Initialize the disks array with an alternating pattern of "white" and "black"
    for (int i = 0; i < size; i++) {
        disks[i] = (i % 2 == 0) ? "white" : "black"; // Use modulus operator to alternate colors
    }

    // Display the initial configuration of the disks
    cout << "Initial configuration: ";
    for (int i = 0; i < size; i++) {
        cout << disks[i] << " ";
    }
    cout << endl;

    int swapCount = 0; // Counter for the total number of swaps made
    bool sorted = false; // Boolean flag to check if the disks are sorted
    int iteration = 0; // Counter for the number of iterations

    // Perform sorting using a swapping process until the array is sorted
    while (!sorted) {
        iteration++; // Increment the iteration count
        int iterationSwaps = 0; // Count the number of swaps in the current iteration
        sorted = true; // Assume the array is sorted initially

        // Loop through the array to find "white" disks next to "black" disks and swap them
        for (int i = 0; i < size - 1; i++) {
            if (disks[i] == "white" && disks[i + 1] == "black") {
                swap(disks[i], disks[i + 1]); // Swap the disks
                swapCount++; // Increment the total swap count
                iterationSwaps++; // Increment the iteration swap count
                sorted = false; // Set sorted to false, as we performed a swap
            }
        }

        // Print the number of interchanges (swaps) performed in the current iteration
        cout << "Number of interchanges in iteration " << iteration << ": " << iterationSwaps << endl;
    }

    // Display the final configuration of the disks after sorting
    cout << "Final configuration: ";
    for (int i = 0; i < size; i++) {
        cout << disks[i] << " ";
    }
    cout << endl;

    // Display the total number of swaps performed
    cout << "Total number of swaps: " << swapCount << endl;

    delete[] disks; // Deallocate the dynamically allocated array to avoid memory leaks
    return 0; // Indicate successful program termination
}
