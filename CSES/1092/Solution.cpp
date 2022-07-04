/*
https://cses.fi/problemset/task/1092

A sum of integers 1...n can be directly calculated by n(n+1)/2
Since we want 2 sets, the sum of each of these sets needs to be n(n+1)/4

The problem becomes organizing the values we have into summables of each
We cannot brute force all values

We can start with larger values and the moment our larger value subset exceeds the limit, we seek from the smaller values to add a replacement to it 

Suppose n = 7:
1. Add 5, 6, 7 to our larger subset, becoming a total sum of 18
2. We need to reduce our sum by 4, and we can do that by swapping out our smallest number in the big number set with a specific value
3. So that would mean we carry over x from the left side of the equation of the sum equality to the right, and move 5 to the other
4. Solve x-5=-4, so our x is 1
5. Add 1 to the set and remove 5, we can construct the other set using our unused value
*/

#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;

int main() {
    int64_t n;
    cin >> n;

    int64_t targetSum = (n * (n + 1)) / 2;
    if(targetSum % 2 != 0) {
        cout << "NO\n";
        return 0;
    }

    targetSum /= 2;

    std::vector<int64_t> left, right;

    int64_t suffixSum = 0;
    for(int64_t i = n; i > 0; i--) {
        suffixSum += i;
        right.push_back(i);
        if(suffixSum > targetSum) {
            int64_t diff = targetSum - suffixSum;
            int64_t required = right.back() + diff;
            right.back() = required;
            while(i > 0) {
                if(i == required) i--;
                if(i != 0)
                left.push_back(i);
                i--;
            }
        } else if(suffixSum == targetSum) {
            // Fill with other values
            while(i > 0) {
                i--;
                if(i != 0)
                left.push_back(i);
            }
        }
    }

    cout << "YES\n" << left.size() << '\n';
    for(int x : left) cout << x << ' ';
    cout << '\n' << right.size() << '\n';
    for(int x : right) cout << x << ' ';
}

