// ---------
// Voting.h
// ---------

#ifndef Voting_h
#define Voting_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <tuple>    // tuple
#include <utility>  // pair
#include <vector>

using namespace std;



class Ballot {
    vector<int> preferences;
    int position;

public:
    int currentPreference();
    void incrementPreference();
    Ballot(string prefs);
};

class Candidate {
    string name;
    int numBallots = 0;
    bool active = true;

public:
    vector<Ballot> ballots;
    Candidate(string n);
    Candidate();
    string outputName();
    void incrementBallots(Ballot b);
    int ballotCount();
    void resetBallots();
    bool isActive();
    void eliminate();
};

// ------------
// hasWinner
// ------------

/**
 * determines whether there is a winner among the candidates
 * @param a vector of candidates
 * @param an int
 * @param an int
 * @return a bool
 */
bool hasWinner(vector<Candidate> candidates, int numCandidates, int numBallots);

// ------------
// hasTie
// ------------

/**
 * determines whether there is a tie among the candidates
 * @param a vector of candidates
 * @param an int
 * @param an int
 * @return a bool
 */
bool hasTie(vector<Candidate> candidates, int numCandidates, int numBallots);

// ------------
// lowestNumberOfBallots
// ------------

/**
 * determines the lowest number of ballots for an active candidate
 * @param a vector of candidates
 * @param an int
 * @param an int
 * @return a int
 */
int lowestNumberOfBallots(vector<Candidate> candidates, int numCandidates, int numBallots);

// ------------
// needsToUpdateBallot
// ------------

/**
 * determines whether a given ballot needs to update its current preference
 * @param a vector of candidates
 * @param a ballot
 * @param a vector of ints
 * @param an int
 * @return a bool
 */
bool needsToUpdateBallot(vector<Candidate> candidates, Ballot b, vector<int> candidatesToDelete, int numLosers);

// -------------
// eliminateLosers
// -------------

/**
 * Determines the losers in a given round and reorganizes their ballots to the next available preference
 * @param a vector of candidates
 * @param an int
 * @param an int
 */
void eliminateLosers(vector<Candidate>& candidates, int numCandidates, int numBallots);

// -------------
// processBallots
// -------------

/**
 * Simulates voting by eliminating until there is a winner or a tie
 * @param a vector of candidates
 * @param an int
 * @param an int
 * @param an ostream
 */
void processBallots(vector<Candidate> candidates, int numCandidates, int numBallots, ostream& sout);


// -------------
// voting_eval
// -------------

/**
 * @param an istream
 * @param an ostream
 */
void voting_eval(istream& sin, ostream& sout);

// -------------
// voting_solve
// -------------

/**
 * @param an istream
 * @param an ostream
 */
void voting_solve (istream& sin, ostream& sout);

#endif // Voting_h
