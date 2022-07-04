/*
TODO: actually fix my solution
Sauce: https://cses.fi/problemset/task/1072/

The brute force strategy would be to count for the first knight:
- The number of positions that are inside the board that it can attack
- The position the knight occupies itself

If we subtract the total space from the number of spaces for the first knight we get our answer
However for each square we need to calculate this for 1...n with n being up to 10,000, so it is too slow
The fact we need to output from 1...n implies a DP approach

Given k-1, how can we calculate k?
We need to account for three possbilbities:
- No knights are on k (ie our answer is just k-1)
- 1 knight (a blocker) is on k

To account for the second one, we can divide the last row and column into ranges where a knight blocks only 2, 3, and 4 spots
We can then get spots where we can place the second knight by doing k^2 - the # of spots blocked
We then multiply the available spots by the size of the range

Now an issue we might face is that for small board sizes, the number of spots blocked become an issue
To overcome this (suggested by Mieka) is that we can hardcode the solution for the first 3 values of k

To simplfy the actual calcuation, I will assume we are on the last row
A bit of visualization will give us the following pattern of blocked spots

2-3-3-2 // k is 4
2-3-4-3-2 // k is 5
2-3-4-4-3-2 // k is 6
2-3-4-4-4-3-2 // k is 7

Hence, our blocked 2 values are always 2, our blocked 3 values are k - 2, and our blocked 4 values are max(0, k - 4)
Remember NOT to double count! We know that knight will NEVER attack the row or column it is one except for 4 edge cases
The number of ways a two knights can be on the same row/column is (2k - 1) * (2k-2)

*/

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    int solution;
    for(int k = 1; k <= n; k++) {
        if(k == 1) {
            solution = 0;
        } else if (k == 2) {
            solution = 6;
        } else if(k == 3) {
            solution = 28;
        } else {
            int block2 = 3;
            int block3 = 4;
            int block4 = 2 * (k - 4);

            int boardSize = k * k;
            int newSpots = block2 * (boardSize - 2) + block3 * (boardSize - 3) + block4 * (boardSize - 4);
            newSpots -= ((2 * k - 1) * (2 * k - 2)) / 2; // Number of ways (both invalid and valid) both knights can be on a row or column
            solution += newSpots;
        }
        std::cout << solution << '\n';
    }
}