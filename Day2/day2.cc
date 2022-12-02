#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

typedef enum { Rock = 1, Paper = 2, Scissors = 3 } Hand;
typedef enum { Nil = -1, Lose  = 0, Draw     = 3, Win = 6 } Goal;

typedef pair<char, char> Round;

Hand translate_hand(char hn)
{
    if (hn == 'A' or hn == 'X') return Rock;
    if (hn == 'B' or hn == 'Y') return Paper;
    return Scissors;
}

Goal translate_goal(char gl)
{
    if (gl == 'X') return Lose;
    if (gl == 'Y') return Draw;
    return Win;
}

// Part 1
int strategy1_score(const Round& r)
{
    Hand opposite = translate_hand(r.first);
    Hand self = translate_hand(r.second);

    Goal goal_matrix[4][4] = {
        {Nil, Nil, Nil, Nil},
        {Nil, Draw, Win, Lose},
        {Nil, Lose, Draw, Win},
        {Nil, Win, Lose, Draw},
    };
    // goal_matrix[opposite][self] gives the outcome

    return goal_matrix[opposite][self] + self;
}

// Part 2
int strategy2_score(const Round& r)
{
    Hand opposite = translate_hand(r.first);
    Goal outcome = translate_goal(r.second);
    Hand self;

    if (opposite == Rock) {
        if (outcome == Lose) {
            self = Scissors;
        } else if (outcome == Draw) {
            self = Rock;
        } else {
            self = Paper;
        }
    } else if (opposite == Paper) {
        if (outcome == Lose) {
            self = Rock;
        } else if (outcome == Draw) {
            self = Paper;
        } else {
            self = Scissors;
        }
    } else {
        if (outcome == Lose) {
            self = Paper;
        } else if (outcome == Draw) {
            self = Scissors;
        } else {
            self = Rock;
        }
    }

    return outcome + self;
}

int main()
{
    vector<Round> rounds;
    ifstream is("day2.txt");
    char opp, self;
    while (is >> opp >> self) {
        rounds.push_back({opp, self});
    }
    is.close();

    int score1 = 0, score2 = 0;
    for (const auto& r : rounds) {
        score1 += strategy1_score(r);
        score2 += strategy2_score(r);
    }

    cout << score1 << endl; // Part 1
    cout << score2 << endl; // Part 2

    return 0;
}

