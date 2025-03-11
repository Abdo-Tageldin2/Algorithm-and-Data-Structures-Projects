#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
void selectionSort(char arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
// Find the minimum element in the unsorted part
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
// Swap the found minimum element with the first element
        swap(arr[i], arr[minIndex]);
    }
}
// Function to check if two strings are anagrams
bool areAnagrams(string A, string B) {
    int SizeA = A.length();
    char arrA[SizeA + 1];
    int SizeB=B.length();
    char arrB[SizeB +1];
// Check if both strings have the same size
    if (SizeA !=SizeB) {
        return false;
    }
// Fill arr with characters from string A
    for (int i = 0; i < SizeA; i++) {
        arrA[i] = A[i];
    }
    for (int i = 0; i < SizeB; i++) {
        arrB[i] = B[i];
    }
    selectionSort(arrA, SizeA);
    selectionSort(arrB,SizeB);
// Compare the sorted versions of both arrays
    for (int i = 0; i < SizeA; i++) {
        if (arrA[i] != arrB[i]) {
            return false;
        }
    }
    return true;
}
int main() {
    string A;
    string B;
    cout << "Enter first word: ";
    getline(cin, A);
    cout << "Enter second word: ";
    getline(cin, B);
    transform(A.begin(),A.end(),A.begin(),:: tolower);
    transform(B.begin(),B.end(),B.begin(),:: tolower);
// Call the function to check if the words are anagrams
    if (areAnagrams(A, B)) {
        cout << "The words are anagrams." << endl;
    } else {
        cout << "The words are not anagrams." << endl;
    }
    return 0;
}
