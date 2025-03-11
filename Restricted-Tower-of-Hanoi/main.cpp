#include <iostream>
using namespace std;
int moveCount = 0;
void hanoi(int n, char start, char target, char middle) {
    if (n == 1) {
        cout << "Move disk 1 from " << start << " to " << middle << endl;
        moveCount++;
        cout << "Move disk 1 from " << middle << " to " << target << endl;
        moveCount++;
        return;
    }
    hanoi(n-1, start, target, middle);
    cout << "Move disk " << n << " from " << start << " to " << middle << endl;
    moveCount++;
    hanoi(n-1, target, start, middle);
    cout << "Move disk " << n << " from " << middle << " to " << target << endl;
    moveCount++;
    hanoi(n-1, start, target, middle);
}
int main() {
    int n;
    cout << "Enter the number of disks: ";
    cin >> n;
    hanoi(n, 'A', 'C', 'B');
    cout << "Total moves: " << moveCount << endl;
    return 0;
}
