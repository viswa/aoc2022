#include <algorithm>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int, int> Pair;
typedef pair<Pair, Pair> Assignment;

bool all(const Pair& a, const Pair& b)
{
    // Guaranteed a spans more elements than b
    return (b.first >= a.first and b.second <= a.second);
}

bool none(const Pair& a, const Pair& b)
{
    // Guaranteed a spans more elements than b
    return (b.second < a.first or b.first > a.second);
}

bool overlap(const Assignment& as, bool cond(const Pair&, const Pair&))
{
    auto bigger = as.first, smaller = as.second;

    auto span1 = bigger.second - bigger.first + 1;
    auto span2 = smaller.second - smaller.first + 1;

    if (span1 < span2) swap(bigger, smaller);
    // first now spans more elements than second

    return cond(bigger, smaller);
}

int main()
{
    vector<Assignment> assignments;
    fstream is("day4.txt");
    while (is.peek() != EOF) {
        Assignment a;
        char ph; // placeholder
        is >> a.first.first >> ph >> a.first.second >> ph;
        is >> a.second.first >> ph >> a.second.second;
        is.get();
        assignments.push_back(a);
    }
    is.close();

    int full_overlaps = 0, no_overlaps = 0;
    for (const auto& as : assignments) {
        full_overlaps += overlap(as, all);
        no_overlaps += overlap(as, none);
    }
    auto partial_overlaps = assignments.size() - no_overlaps;

    cout << full_overlaps << endl;    // Part 1
    cout << partial_overlaps << endl; // Part 2

    return 0;
}

