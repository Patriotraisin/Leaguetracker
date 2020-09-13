#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>

using namespace std;

#define WINVALUE 2
#define DRAWVALUE 1

struct Team {
    string name;
    int pointsScored;
    int pointsScoredAgainst;
    int winCount;
    int drawCount;
    int gamesPlayed;
    int points;
};

Team* teams;
int teamCount;
char buffer[100];

void initializeTeams() {
    teams = new Team[teamCount];
    
    for (int index = 0; index < teamCount; index++) {
        teams[index].name = "Team " + to_string(index+1);
        teams[index].pointsScored = 0;
        teams[index].pointsScoredAgainst = 0;
        teams[index].gamesPlayed = 0;
        teams[index].winCount = 0;
        teams[index].points = 0;
    }
}

// Extra credit: Add a 'League points' column where the number of wins * winvalue
//               Add Draws and have their points count
const void displayTeam(const Team team) {
    cout << left << setw(10) << team.name
    << setw(10) << team.gamesPlayed
    << setw(11) << team.pointsScored
    << setw(15) << team.pointsScoredAgainst
    << setw(10) << team.winCount
    << setw(10) << team.points << endl;
}

const void displayTeams() {
    cout << left << setw(10) << "Team"
    << setw(10) << "Played"
    << setw(11) << "Goals For"
    << setw(15) << "Goals Against"
    << setw(10) << "Wins"
    << setw(10) << "Points" << endl;
    for (int index = 0; index < teamCount; index++) {
        displayTeam(teams[index]);
    }
}

// figures out winner
// modifies team data
void scoreGame(Team* team1, Team* team2, const int score1, const int score2) {
    (*team1).pointsScored += score1;
    (*team2).pointsScored += score2;
   (*team1).pointsScoredAgainst += score2;
   (*team2).pointsScoredAgainst += score1;
    
    (*team1).gamesPlayed++;
    (*team2).gamesPlayed++;
    
    if (score1 > score2){
        (*team1).winCount++;
        (*team1).points+= WINVALUE;
    }
    else if (score2 > score1){
        (*team2).winCount++;
        (*team2).points+= WINVALUE;
    }
    else{
        (*team1).drawCount++;
        (*team2).drawCount++;
        (*team1).points+= DRAWVALUE;
        (*team2).points+= DRAWVALUE;
    }
}

// Request the team score from the user
// return the value
// do not allow negative score values
// *done
int scoreValue(const int teamIndex) {
    int pointsScored = -1;
    while (pointsScored<0){
        cout << "How many points did team " << teamIndex+1 << " score?" << endl;
        cin >> pointsScored;
    }
    return pointsScored;
}

// Reqest 2 team numbers
// request the score from each team
// figure out who won
// return false if both team numbers are the same
bool askTeamScore() {
    int t1, t2, p1, p2;
    cout << "Enter Team number 1:" << endl;
    cin >> t1;
    cout << "Enter Team number 2:" << endl;
    cin >> t2;
    if (t1==t2){
        return false;
    }
    t1--;
    t2--;
    p1 = scoreValue(t1);
    p2 = scoreValue(t2);
    if (p1>p2){
        cout << "Team " << t1+1 << " won." << endl;
    }
    else if (p2 > p1){
        cout << "Team " << t2+1 << " won." << endl;
    }
    else if (p1 == p2){
        cout << "Tie." << endl;
    }
    scoreGame(&teams[t1], &teams[t2], p1,p2);
    return true;
}

// Ask the user if they want to quit
// if (y) or (yes) return true
bool checkEnd() {
    string ans;
    cout << "Quit? (y/yes)" << endl;
    cin >> ans;
    if (ans == "y" or ans == "yes"){
        return true;
    }
    return false;
}

int getTeamCount() {
    int value = -1;
    
    while (value < 2) {
        cout << "How many teams in the league? " << endl;
        cin >> buffer;
        
        value = atoi(buffer);
        
        if (value < 2) {
            cout << "You can not have a league of less than 2 teams." << endl;
        }
    }
    
    return value;
}

int main() {
    bool end = false;
    teamCount = getTeamCount();
    initializeTeams();
    
    // Loop until checkEnd
    // ask for team scores
    // display teams
    
    while (!end){
        askTeamScore();
        displayTeams();
        end = checkEnd();
    }
    cout << "Final standings:" << endl;
    displayTeams();
    delete[] teams;
    return 0;
}
