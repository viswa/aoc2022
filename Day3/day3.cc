#include <cctype>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

typedef vector<string> vs;

char find_common(const string& str)
{
    auto const MID = str.size() / 2;

    vector<bool> first(128, false);
    vector<bool> second(128, false);
    for (string::size_type i = 0, j = MID; i < MID; i++, j++) {
        first[str[i]] = second[str[j]] = true;
    }

    for (char i = 0; i < 128; i++) {
        if (first[i] && second[i]) {
            return i;
        }
    }

    return '\0';
}

char find_common(const vs::const_iterator start, const vs::const_iterator end)
{
    const auto LEN = distance(start, end);

    vector<vector<bool>> found(LEN);
    for (auto i = found.begin(); i != found.end(); i++) *i = vector<bool>(128, false);

    for (auto i = start; i != end; i++) {
        for (auto ch : *i) {
            found[distance(start, i)][ch] = true;
        }
    }

    for (char i = 0; i < 128; i++) {
        bool valid = true;
        for (auto j = 0; j < LEN; j++) {
            valid = valid and found[j][i];
        }
        if (valid) {
            return i;
        }
    }

    return '\0';
}

int priority(char c)
{
    if (islower(c)) return c - 'a' + 1;
    return c - 'A' + 27;
}

int main()
{
    ifstream is("day3.txt");
    vs rucksacks;
    string line;
    while (getline(is, line)) {
        rucksacks.push_back(line);
    }
    is.close();

    int sum_priorities = 0;
    for (const auto& rk : rucksacks) {
        sum_priorities += priority(find_common(rk));
    }
    cout << sum_priorities << endl; // Part 1

    const int GRP_SIZ = 3;
    int sum_group_priorities = 0;
    for (auto i = rucksacks.cbegin(); i != rucksacks.cend(); i += GRP_SIZ) {
        sum_group_priorities += priority(find_common(i, next(i, GRP_SIZ)));
    }
    cout << sum_group_priorities << endl; // Par 2

    return 0;
}

