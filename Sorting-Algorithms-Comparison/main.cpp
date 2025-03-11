#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
using namespace std;
using namespace chrono;

// Helper function to maintain the min-heap property
void min_heapify(int arr[], int n, int i, int &count) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        count++; // Count comparison
        if (arr[left] < arr[smallest])
            smallest = left;
    }

    if (right < n) {
        count++; // Count comparison
        if (arr[right] < arr[smallest])
            smallest = right;
    }

    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        min_heapify(arr, n, smallest, count);
    }
}

// Min-Heap Sort that counts comparisons
int heap_sort_count(int arr[], int n) {
    int count = 0;
    for (int i = n / 2 - 1; i >= 0; i--)
        min_heapify(arr, n, i, count);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        min_heapify(arr, i, 0, count);
    }
    return count;
}

// Bubble Sort that counts comparisons
int bubble_sort_count(int arr[], int n) {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            count++; // Count each comparison
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
    return count;
}

// Selection Sort that counts comparisons
int selection_sort_count(int arr[], int n) {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            count++; // Count each comparison
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        swap(arr[min_idx], arr[i]);
    }
    return count;
}

// Insertion Sort that counts comparisons
int insertion_sort_count(int arr[], int n) {
    int count = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            count++; // Count each comparison
            if (arr[j] > key)
                arr[j + 1] = arr[j];
            else
                break;
            j--;
        }
        arr[j + 1] = key;
    }
    return count;
}

int random_arrays[30][30] = {
        {1}, // size = 1
        {2, 1}, // size = 2
        {2, 3, 1}, // size = 3
        {3, 1, 4, 2}, // size = 4
        {2, 5, 1, 3, 4}, // size = 5
        {4, 1, 6, 3, 2, 5}, // size = 6
        {5, 2, 7, 3, 1, 4, 6}, // size = 7
        {8, 2, 5, 1, 7, 4, 3, 6}, // size = 8
        {4, 7, 2, 9, 1, 5, 3, 8, 6}, // size = 9
        {10, 2, 6, 4, 7, 8, 3, 1, 9, 5}, // size = 10
        {2, 11, 5, 9, 3, 1, 7, 10, 6, 8, 4}, // size = 11
        {12, 3, 5, 1, 8, 9, 2, 4, 10, 6, 11, 7}, // size = 12
        {3, 1, 13, 7, 10, 2, 6, 12, 5, 9, 4, 11, 8}, // size = 13
        {5, 8, 3, 14, 2, 4, 9, 1, 6, 10, 13, 7, 12, 11}, // size = 14
        {15, 6, 9, 3, 5, 7, 1, 12, 14, 2, 8, 4, 10, 13, 11}, // size = 15
        {8, 6, 4, 2, 5, 3, 16, 10, 1, 15, 13, 7, 12, 9, 11, 14}, // size = 16
        {2, 5, 7, 9, 4, 6, 3, 8, 17, 10, 1, 15, 13, 11, 14, 12, 16}, // size = 17
        {10, 3, 6, 2, 8, 4, 18, 1, 5, 13, 17, 9, 16, 15, 14, 7, 11, 12}, // size = 18
        {9, 6, 1, 5, 3, 7, 19, 16, 2, 14, 10, 15, 17, 4, 12, 8, 11, 13, 18}, // size = 19
        {4, 3, 2, 5, 7, 8, 6, 20, 19, 1, 10, 17, 9, 12, 15, 13, 14, 16, 11, 18}, // size = 20
        {7, 3, 8, 5, 6, 1, 2, 4, 21, 9, 11, 16, 20, 15, 14, 10, 13, 17, 12, 18, 19}, // size = 21
        {6, 9, 8, 7, 5, 4, 3, 22, 2, 1, 10, 19, 12, 14, 20, 16, 21, 13, 17, 15, 18, 11}, // size = 22
        {2, 3, 9, 7, 6, 5, 23, 1, 4, 10, 8, 20, 13, 15, 11, 17, 21, 12, 14, 22, 18, 16, 19}, // size = 23
        {8, 1, 6, 9, 3, 7, 24, 5, 2, 4, 23, 10, 15, 13, 19, 21, 20, 12, 16, 17, 11, 14, 18, 22}, // size = 24
        {4, 6, 5, 3, 2, 8, 25, 1, 7, 9, 10, 15, 13, 19, 23, 12, 11, 24, 16, 20, 14, 22, 17, 21, 18}, // size = 25
        {10, 1, 9, 3, 6, 7, 2, 8, 26, 4, 23, 5, 11, 15, 13, 14, 25, 20, 17, 21, 19, 12, 16, 24, 22, 18}, // size = 26
        {9, 2, 5, 6, 8, 27, 1, 4, 10, 3, 7, 11, 14, 16, 12, 23, 22, 17, 24, 26, 15, 25, 20, 13, 18, 21, 19}, // size = 27
        {7, 3, 9, 1, 4, 28, 2, 8, 6, 10, 15, 5, 19, 21, 12, 16, 14, 27, 20, 22, 24, 11, 17, 25, 13, 23, 18, 26}, // size = 28
        {2, 8, 5, 6, 7, 29, 10, 3, 1, 4, 12, 13, 9, 14, 27, 23, 15, 24, 21, 25, 22, 26, 11, 16, 17, 20, 19, 28, 18}, // size = 29
        {10, 3, 6, 1, 30, 2, 9, 5, 7, 8, 4, 12, 20, 15, 23, 28, 16, 24, 11, 19, 21, 26, 29, 25, 18, 22, 27, 13, 17, 14} // size = 30
};

int sorted_arrays[30][30] = {
        {1}, // size = 1
        {1, 2}, // size = 2
        {1, 2, 3}, // size = 3
        {1, 2, 3, 4}, // size = 4
        {1, 2, 3, 4, 5}, // size = 5
        {1, 2, 3, 4, 5, 6}, // size = 6
        {1, 2, 3, 4, 5, 6, 7}, // size = 7
        {1, 2, 3, 4, 5, 6, 7, 8}, // size = 8
        {1, 2, 3, 4, 5, 6, 7, 8, 9}, // size = 9
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, // size = 10
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, // size = 11
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, // size = 12
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}, // size = 13
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}, // size = 14
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, // size = 15
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}, // size = 16
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17}, // size = 17
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}, // size = 18
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}, // size = 19
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, // size = 20
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21}, // size = 21
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22}, // size = 22
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23}, // size = 23
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24}, // size = 24
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25}, // size = 25
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26}, // size = 26
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27}, // size = 27
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28}, // size = 28
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29}, // size = 29
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30} // size = 30
};

int inverse_sorted_arrays[30][30] = {
        {1}, // size = 1
        {2, 1}, // size = 2
        {3, 2, 1}, // size = 3
        {4, 3, 2, 1}, // size = 4
        {5, 4, 3, 2, 1}, // size = 5
        {6, 5, 4, 3, 2, 1}, // size = 6
        {7, 6, 5, 4, 3, 2, 1}, // size = 7
        {8, 7, 6, 5, 4, 3, 2, 1}, // size = 8
        {9, 8, 7, 6, 5, 4, 3, 2, 1}, // size = 9
        {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, // size = 10
        {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, // size = 11
        {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, // size = 12
        {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, // size = 13
        {14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, // size = 14
        {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, // size = 15
        {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, // size = 16
        {17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, // size = 17
        {18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, // size = 18
        {19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, // size = 19
        {20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, // size = 20
        {21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, // size = 21
        {22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, // size = 22
        {23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, // size = 23
        {24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, // size = 24
        {25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, // size = 25
        {26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, // size = 26
        {27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, // size = 27
        {28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, // size = 28
        {29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, // size = 29
        {30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1} // size = 30
};

// Function to test sorting algorithms and write results to a CSV file
void test_comparisons(const string &test_type, int size, int arr[], int n, ofstream &outfile) {
    // Making copies of the array for each sort
    int arr1[30], arr2[30], arr3[30], arr4[30];
    copy(arr, arr + n, arr1);
    copy(arr, arr + n, arr2);
    copy(arr, arr + n, arr3);
    copy(arr, arr + n, arr4);

    // Heap Sort
    auto start = high_resolution_clock::now();
    int heap_comps = heap_sort_count(arr1, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);

    outfile << test_type << "," << size << ",Heap Sort," << heap_comps << "," << duration.count() << "\n";
    cout << left << setw(20) << test_type
         << setw(12) << size
         << setw(16) << "Heap Sort"
         << setw(12) << heap_comps
         << setw(16) << duration.count()
         << "\n";

    // Bubble Sort
    start = high_resolution_clock::now();
    int bubble_comps = bubble_sort_count(arr2, n);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);

    outfile << test_type << "," << size << ",Bubble Sort," << bubble_comps << "," << duration.count() << "\n";
    cout << left << setw(20) << test_type
         << setw(12) << size
         << setw(16) << "Bubble Sort"
         << setw(12) << bubble_comps
         << setw(16) << duration.count()
         << "\n";

    // Selection Sort
    start = high_resolution_clock::now();
    int selection_comps = selection_sort_count(arr3, n);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);

    outfile << test_type << "," << size << ",Selection Sort," << selection_comps << "," << duration.count() << "\n";
    cout << left << setw(20) << test_type
         << setw(12) << size
         << setw(16) << "Selection Sort"
         << setw(12) << selection_comps
         << setw(16) << duration.count()
         << "\n";

    // Insertion Sort
    start = high_resolution_clock::now();
    int insertion_comps = insertion_sort_count(arr4, n);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);

    outfile << test_type << "," << size << ",Insertion Sort," << insertion_comps << "," << duration.count() << "\n";
    cout << left << setw(20) << test_type
         << setw(12) << size
         << setw(16) << "Insertion Sort"
         << setw(12) << insertion_comps
         << setw(16) << duration.count()
         << "\n";
}

// Main function to run tests and save results to a CSV file
int main() {
    // Open a CSV file for output
    ofstream outfile("sortingresults.csv");

    // Write header row to CSV
    outfile << "Test Type,Array Size,Algorithm,Comparisons,Time (ns)\n";

    // Print a neat table header to console
    cout << left << setw(20) << "Test Type"
         << setw(12) << "Array Size"
         << setw(16) << "Algorithm"
         << setw(12) << "Comparisons"
         << setw(16) << "Time(ns)"
         << "\n";

    // Testing each category of arrays
    for (int size = 1; size <= 30; size++) {
        test_comparisons("Random Array", size, random_arrays[size - 1], size, outfile);
        test_comparisons("Sorted Array", size, sorted_arrays[size - 1], size, outfile);
        test_comparisons("Inverse Sorted Array", size, inverse_sorted_arrays[size - 1], size, outfile);
    }

    outfile.close();
    cout << "Results saved to sortingresults.csv\n";

    return 0;
}
