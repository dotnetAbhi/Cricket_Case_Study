#include <iostream>
#include <string>
using namespace std;

class Team {
protected:
    string teamName[8];
    int teamScore[8];

public:
    void inputTeams() {
        cout << "=== Enter 8 Team Names and Their Scores ===\n";
        for (int i = 0; i < 8; i++) {
            cout << "Team " << i + 1 << " (Name Score): ";
            cin >> teamName[i] >> teamScore[i];
        }
    }
};

class Groups : public Team {
protected:
    string groupA[8], groupB[8];
    int scoreA[8], scoreB[8];
    int countA = 0, countB = 0;

public:
    void divideGroups() {
        for (int i = 0; i < 8; i++) {
            if (teamScore[i] >= 70) {
                groupA[countA] = teamName[i];
                scoreA[countA] = teamScore[i];
                countA++;
            } else {
                groupB[countB] = teamName[i];
                scoreB[countB] = teamScore[i];
                countB++;
            }
        }
    }

    void showGroups() {
        cout << "\n=== GROUP A (Score >= 70) ===\n";
        for (int i = 0; i < countA; i++)
            cout << groupA[i] << " - " << scoreA[i] << " points\n";

        cout << "\n=== GROUP B (Score < 70) ===\n";
        for (int i = 0; i < countB; i++)
            cout << groupB[i] << " - " << scoreB[i] << " points\n";
    }
};

class SemiFinal : public Groups {
protected:
    string semiTeams[4];
    int semiScores[4];

public:
    void selectTop2EachGroup() {
        for (int i = 0; i < countA - 1; i++)
            for (int j = 0; j < countA - i - 1; j++)
                if (scoreA[j] < scoreA[j + 1]) {
                    swap(scoreA[j], scoreA[j + 1]);
                    swap(groupA[j], groupA[j + 1]);
                }

        for (int i = 0; i < countB - 1; i++)
            for (int j = 0; j < countB - i - 1; j++)
                if (scoreB[j] < scoreB[j + 1]) {
                    swap(scoreB[j], scoreB[j + 1]);
                    swap(groupB[j], groupB[j + 1]);
                }

        int idx = 0;
        for (int i = 0; i < 2 && i < countA; i++) {
            semiTeams[idx] = groupA[i];
            semiScores[idx] = scoreA[i];
            idx++;
        }
        
        for (int i = 0; i < 2 && i < countB; i++) {
            semiTeams[idx] = groupB[i];
            semiScores[idx] = scoreB[i];
            idx++;
        }
    }

    void showSemiFinalists() {
        cout << "\n=== SEMI-FINALISTS (Top 2 from Both Groups) ===\n";
        for (int i = 0; i < 4; i++)
            cout << i + 1 << ". " << semiTeams[i]
                 << " - " << semiScores[i] << " points\n";
    }
};

class Finals : public SemiFinal {
private:
    string finalist1, finalist2;
    int score1, score2;

public:
    void selectFinalTwo() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3 - i; j++)
                if (semiScores[j] < semiScores[j + 1]) {
                    swap(semiScores[j], semiScores[j + 1]);
                    swap(semiTeams[j], semiTeams[j + 1]);
                }

        finalist1 = semiTeams[0];
        score1 = semiScores[0];

        finalist2 = semiTeams[1];
        score2 = semiScores[1];
    }

    void showFinals() {
        cout << "\n=== FINALISTS ===\n";
        cout << "1. " << finalist1 << " (" << score1 << ")\n";
        cout << "2. " << finalist2 << " (" << score2 << ")\n";
    }

    void showWinner() {
        cout << "\n=== WINNER ===\n";
        cout << "🏆 " << semiTeams[0]
             << " WINS WITH " << semiScores[0] << " POINTS! 🏆\n";
    }
};

int main() {
    Finals T;

    T.inputTeams();

    T.divideGroups();
    T.showGroups();

    T.selectTop2EachGroup();
    T.showSemiFinalists();

    T.selectFinalTwo();
    T.showFinals();

    T.showWinner();

    return 0;
}
