// -----------
// Voting.c++
// -----------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <tuple>    // make_tuple, tie, tuple
#include <utility>  // make_pair, pair
#include <vector>

#include "Voting.hpp"

using namespace std;

int Ballot::currentPreference() {
    //cout << "Line 26" << endl;
    // - 1 to get an index
    return preferences.at(position) - 1;
}

void Ballot::incrementPreference() {
    ++position;
}

//read in a string of space separated integers and add them to preferences as ints
Ballot::Ballot(string prefs) {
    stringstream stream(prefs);
    int n;
    while(stream >> n) {
        preferences.push_back(n);
    }
    position = 0;
}


Candidate::Candidate(string n) {
    name = n;
}

Candidate::Candidate() {
    name = "";
}

string Candidate::outputName() {
    return name;
}

void Candidate::incrementBallots(Ballot b) {
    ++numBallots;
    ballots.push_back(b);
}

int Candidate::ballotCount() {
    return numBallots;
}

void Candidate::resetBallots() {
    numBallots = 0;
}

bool Candidate::isActive() {
    return active;
}

void Candidate::eliminate() {
    active = false;
    numBallots = 0;
}



//check if any candidate is above 50% of ballots
bool hasWinner(vector<Candidate> candidates, int numCandidates, int numBallots) {
    for(int x = 0; x < numCandidates; x++) {
        if(candidates.at(x).ballotCount() > numBallots / 2.0) {
            return true;
        }
    }
    return false;
}

//check if all active candidates are tied
bool hasTie(vector<Candidate> candidates, int numCandidates, int numBallots) {
    if(numCandidates < 2) {
        return false;
    }
    int tyingBallots = 0;
    int numActive = 0;
    for(int x = 0; x < numCandidates; x++) {
        Candidate c = candidates.at(x);
        if(!c.isActive()) {
            continue;
        }
        numActive += 1;
        if(tyingBallots == 0) {
            tyingBallots = c.ballotCount();
        }
        else {
            if(c.ballotCount() != tyingBallots) {
                return false;
            }
        }
    }
    return numActive * tyingBallots == numBallots;
}





//return what the lowest score in a round was
int lowestNumberOfBallots(vector<Candidate> candidates, int numCandidates, int numBallots) {
    int lowest = numBallots;
    for(int x = 0; x < numCandidates; x++) {
        Candidate c = candidates.at(x);
        if(c.ballotCount() < lowest && c.isActive()) {
            lowest = c.ballotCount();
        }
    }
    return lowest;
}

//tells you if the ballot's current preference is no good
bool needsToUpdateBallot(vector<Candidate> candidates, Ballot b, vector<int> candidatesToDelete, int numLosers) {
    for(int x = 0; x < numLosers; x++) {
        if(candidatesToDelete.at(x) == b.currentPreference()) {
            return true;
        }
    }
    //cout << "line 145" << endl;
    if(candidates.at(b.currentPreference()).isActive()) {
        return false;
    }
    return true;
}

//goes through and find candidates with ballots equal to tbe lowest amount and reallocates their ballots to the next preference
void eliminateLosers(vector<Candidate>& candidates, int numCandidates, int numBallots) {
    int losingScore = lowestNumberOfBallots(candidates, numCandidates, numBallots);
    vector<int> candidatesToDelete;
    int numLosers = 0;
    for(int x = 0; x < numCandidates; x++) {
        Candidate c = candidates.at(x);
        if(c.ballotCount() == losingScore && c.isActive()) {
            candidatesToDelete.push_back(x);
            ++numLosers;
        }
    }
    for(int x = 0; x < numCandidates; x++) {
        Candidate c = candidates.at(x);
        if(c.ballotCount() == losingScore && c.isActive()) {
            candidates.at(x).eliminate();
            for(int y = 0; y < c.ballotCount(); y++) {
                Ballot b = c.ballots.at(y);
                while(needsToUpdateBallot(candidates, b, candidatesToDelete, numLosers)) {
                    b.incrementPreference();
                }
                //cout << "Line 172" << endl;
                candidates.at(b.currentPreference()).incrementBallots(b);
            }
        }
    }
}


//scores candidates for their ballots, eliminates all losers and advances their ballots, then checks for winners or ties
void processBallots(vector<Candidate> candidates, int numCandidates, int numBallots, ostream& sout) {
    //int turnNumber = 0;
    while(!hasWinner(candidates, numCandidates, numBallots) && !hasTie(candidates, numCandidates, numBallots)) {
        //for debugging
        /*
        cout << "Turn number: " << turnNumber << endl;
        for(int x = 0; x < numCandidates; x++) {
            Candidate c = candidates.at(x);
            cout << "Candidate " << c.outputName() << "\tActive: " << c.isActive() << "\tBallots: " << c.ballotCount() << endl;
        }
        turnNumber += 1;
        */
        eliminateLosers(candidates, numCandidates, numBallots);

    }
    if(hasWinner(candidates, numCandidates, numBallots)) {
        for(int x = 0; x < numCandidates; x++) {
            Candidate c = candidates.at(x);
            if(c.ballotCount() > numBallots / 2.0) {
                sout << c.outputName();
            }
        }
    }
    else {
        int num = 0;
        for(int x = 0; x < numCandidates; x++) {
            Candidate c = candidates.at(x);
            if(c.isActive()) {
                if(num > 0) {
                    sout << "\n";
                }
                sout << c.outputName();
                num += 1;
            }
        }
    }
}

// ------------
// voting_eval
// ------------

//reads in input for a given case and then calls processBallots
void voting_eval(istream& sin, ostream& sout) {
    string s;
    getline(sin, s);
    const int numberOfCandidates = stoi(s);
    int numberOfBallots = 0;
    vector<Candidate> candidates;
    for(int x = 0; x < numberOfCandidates; x++) {
        getline(sin, s);
        Candidate c(s);
        candidates.push_back(c);
    }
    while(getline(sin, s)) {
        if(s == "") {
            processBallots(candidates, numberOfCandidates, numberOfBallots, sout);
            return;
        }
        Ballot b(s);
        //cout << "Line 242" << endl;
        candidates.at(b.currentPreference()).incrementBallots(b);
        numberOfBallots += 1;
    }
    processBallots(candidates, numberOfCandidates, numberOfBallots, sout);

}

// -------------
// voting_solve
// -------------

void voting_solve(istream& sin, ostream& sout) {
    string s;
    getline(sin, s);
    int numberOfCases = stoi(s);
    getline(sin, s);
    for(int x = 0; x < numberOfCases; x++) {
        if(x >= 1) {
            sout << "\n" << endl;
        }
        voting_eval(sin, sout);
    }
    sout << endl;
}
