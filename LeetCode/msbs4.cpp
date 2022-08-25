//
// Created by jinzhaopeng on 2022/8/25.
//

// #include "bits/stdc++.h"

#include "iostream"
#include "vector"
#include "map"
#include "queue"
#include "string"
#include "unordered_map"
#include "unordered_set"

using namespace std;

string removeX(string N, char X)
{

    // Stores the index of X
    // that has to be removed
    int index = -1;

    // Find leftmost occurrence of X
    // such that the digit just after X
    // is greater than X
    for (int i = 0; i < N.length() - 1; i++) {
        if (N[i] == X && N[i] - '0' < N[i + 1] - '0') {

            // Update index and break
            index = i;
            break;
        }
    }

    // If no occurrence of X such that
    // the digit just after X
    // is greater than X is found
    // then find last occurrence of X
    if (index == -1) {
        for (int i = N.length() - 1; i >= 0; i--) {
            if (N[i] == X) {
                index = i;
                break;
            }
        }
    }

    // Construct answer using all characters
    // in string N except index
    string ans = "";
    for (int i = 0; i < N.length(); i++) {
        if (i != index)
            ans = ans + N[i];
    }

    return ans;
}

int solution1(int N) {
    // write your code in C++ (C++14 (g++ 6.2.0))
    string number = to_string(N);
    int len = number.size();
    int res = INT_MIN;
    for (int i = 0; i < len; ++i) {
        if (number[i] == '5') {
            string tmp = number.substr(0, i);
            tmp.append(number.substr(i + 1, len - i));
            res = max(res, stoi(tmp));
        }
    }
    return res;
}

int solution2(vector<int> &A) {
    // write your code in C++ (C++14 (g++ 6.2.0))
    unordered_map<long long, long long> mp;
    mp[0] = 1;
    long long res = 0, sum = 0;
    for (int i = 0; i < A.size(); ++i) {
        sum += A[i];
        if (mp.find(sum) != mp.end()) {
            res += mp[sum];
        }
        if (res > 1000000000) {
            return -1;
        }
        mp[sum]++;
    }
    return res > 1000000000 ? -1 : res;
}

int solution(vector<int> &a) {
    // write your code in C++ (C++14 (g++ 6.2.0))
    int n = a.size();
    long long res = 0;
    for (int i = 0; i < n; ++i) {
        for (int cnt = 0; i < n - 2 && a[i + 1] - a[i] == a[i + 2] - a[i + 1]; i++) {
            cnt++;
            res += cnt;
            if (res > 1000000000) {
                return -1;
            }
        }
    }
    int sad = res;
    return res > 1000000000 ? -1 : res;
}

int main() {
    vector<int> aa{-1, 1, 3, 3, 3, 2, 3, 2 ,1 ,0};
    cout << solution(aa);
    return 0;
}