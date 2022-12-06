#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void lshift(string& str)
{
    for (string::size_type i = 0; i < str.size() - 1; i++) {
        str[i] = str[i + 1];
    }
}

bool uniquep(const string& str)
{
    vector<bool> seen(26, false);
    for (const char ch : str) {
        if (seen[ch - 'a']) {
            return false;
        }
        seen[ch - 'a'] = true;
    }
    return true;
}

int find_marker(const string& data, const int window_size)
{
    string window = data.substr(0, window_size);
    for (string::size_type i = window_size - 1; i < data.size(); i++) {
        window[window_size - 1] = data[i];
        if (uniquep(window)) {
            return i + 1;
        }
        lshift(window);
    }
    return -1;
}

int main()
{
    ifstream is("day6.txt");
    string data;
    is >> data;
    is.close();

    cout << find_marker(data, 4)  << endl; // Part 1
    cout << find_marker(data, 14) << endl; // Part 2

    return 0;
}

