#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <list>
#include <string>
#include <vector>

using namespace std;

int sum(const vector<int>& iv)
{
    return accumulate(iv.cbegin(), iv.cend(), 0);
}

void insert(list<vector<int>>& ls, const vector<int>& iv)
{
    const auto vec_sum = sum(iv);
    const auto i = find_if(ls.begin(), ls.end(),
            [&vec_sum](const vector<int>& v) {
                return sum(v) < vec_sum;
            }
    );
    ls.insert(i, iv);
}

int sum_n(list<vector<int>>& ls, int n)
{
    int total = 0;
    auto iter = ls.cbegin();
    while (n--) {
        total += sum(*iter);
        iter++;
    };
    return total;
}

int main()
{
    list<vector<int>> cals;
    vector<int> current;
    ifstream is("day1.txt");
    string line;
    while (getline(is, line)) {
        if (!line.empty()) {
            current.push_back(stoi(line));
        } else {
            insert(cals, current);
            current.clear();
        }
    }
    insert(cals, current);
    is.close();

    cout << sum_n(cals, 1) << endl; // Part 1
    cout << sum_n(cals, 3) << endl; // Part 2

    return 0;
}

