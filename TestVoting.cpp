// ---------------
// TestVoting.c++
// ---------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <sstream>  // istringtstream, ostringstream
#include <tuple>    // make_tuple, tuple
#include <utility>  // make_pair, pair
#include <vector>

#include "gtest/gtest.h"

#include "Voting.hpp"

using namespace std;

TEST(VotingFixture, hasWinner1) {
    vector<Candidate> candidates1;
    vector<Candidate> candidates2;
    Candidate c1("c1");
    Candidate c2("c2");
    Candidate c3("c3");
    Candidate c4("c4");
    Ballot b("1 2 3 4");
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    c2.incrementBallots(b);
    c3.incrementBallots(b);
    c3.incrementBallots(b);
    c4.incrementBallots(b);
    c4.incrementBallots(b);
    candidates1.push_back(c1);
    candidates1.push_back(c2);
    candidates2.push_back(c3);
    candidates2.push_back(c4);
    ASSERT_EQ(true, hasWinner(candidates1, 2, 3));
}

TEST(VotingFixture, hasWinner2) {
    vector<Candidate> candidates1;
    vector<Candidate> candidates2;
    Candidate c1("c1");
    Candidate c2("c2");
    Candidate c3("c3");
    Candidate c4("c4");
    Ballot b("1 2 3 4");
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    c2.incrementBallots(b);
    c3.incrementBallots(b);
    c3.incrementBallots(b);
    c4.incrementBallots(b);
    c4.incrementBallots(b);
    candidates1.push_back(c1);
    candidates1.push_back(c2);
    candidates2.push_back(c3);
    candidates2.push_back(c4);
    ASSERT_EQ(false, hasWinner(candidates2, 2, 4));
}

TEST(VotingFixture, hasWinner3) {
    vector<Candidate> candidates;
    Candidate c1("c1");
    Ballot b("1");
    c1.incrementBallots(b);
    candidates.push_back(c1);
    ASSERT_EQ(true, hasWinner(candidates, 1, 1));
}

TEST(VotingFixture, hasWinner4) {
    vector<Candidate> candidates;
    Candidate c1("c1");
    Ballot b("1");
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    candidates.push_back(c1);
    ASSERT_EQ(true, hasWinner(candidates, 1, 10));
}


TEST(VotingFixture, hasTie1) {
    vector<Candidate> candidates1;
    vector<Candidate> candidates2;
    Candidate c1("c1");
    Candidate c2("c2");
    Candidate c3("c3");
    Candidate c4("c4");
    Ballot b("1 2 3 4");
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    c2.incrementBallots(b);
    c3.incrementBallots(b);
    c3.incrementBallots(b);
    c4.incrementBallots(b);
    c4.incrementBallots(b);
    candidates1.push_back(c1);
    candidates1.push_back(c2);
    candidates2.push_back(c3);
    candidates2.push_back(c4);
    ASSERT_EQ(false, hasTie(candidates1, 2, 3));
}

TEST(VotingFixture, hasTie2) {
    vector<Candidate> candidates1;
    vector<Candidate> candidates2;
    Candidate c1("c1");
    Candidate c2("c2");
    Candidate c3("c3");
    Candidate c4("c4");
    Ballot b("1 2 3 4");
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    c2.incrementBallots(b);
    c3.incrementBallots(b);
    c3.incrementBallots(b);
    c4.incrementBallots(b);
    c4.incrementBallots(b);
    candidates1.push_back(c1);
    candidates1.push_back(c2);
    candidates2.push_back(c3);
    candidates2.push_back(c4);
    ASSERT_EQ(true, hasTie(candidates2, 2, 4));
}

TEST(VotingFixture, hasTie3) {
    vector<Candidate> candidates;
    Candidate c1("c1");
    Ballot b("1");
    c1.incrementBallots(b);
    candidates.push_back(c1);
    ASSERT_EQ(false, hasTie(candidates, 1, 1));
}

TEST(VotingFixture, hasTie4) {
    vector<Candidate> candidates;
    Candidate c1("c1");
    Ballot b("1");
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    candidates.push_back(c1);
    ASSERT_EQ(false, hasTie(candidates, 1, 10));
}


TEST(VotingFixture, lowestNumber1) {
    vector<Candidate> candidates;
    Candidate c1("c1");
    Ballot b("1 2");
    c1.incrementBallots(b);
    candidates.push_back(c1);
    ASSERT_EQ(1, lowestNumberOfBallots(candidates, 1, 1));
}

TEST(VotingFixture, lowestNumber2) {
    vector<Candidate> candidates;
    Candidate c1("c1");
    Candidate c2("c2");
    Ballot b("1 2");
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    c2.incrementBallots(b);
    candidates.push_back(c1);
    candidates.push_back(c2);
    ASSERT_EQ(1, lowestNumberOfBallots(candidates, 2, 3));
}

TEST(VotingFixture, lowestNumber3) {
    vector<Candidate> candidates;
    Candidate c1("c1");
    Candidate c2("c2");
    Ballot b("1 2");
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    c2.incrementBallots(b);
    c1.eliminate();
    candidates.push_back(c1);
    candidates.push_back(c2);
    ASSERT_EQ(1, lowestNumberOfBallots(candidates, 2, 3));
}

TEST(VotingFixture, lowestNumber4) {
    vector<Candidate> candidates;
    Candidate c1("c1");
    Candidate c2("c2");
    Ballot b("1 2");
    c1.incrementBallots(b);
    c1.incrementBallots(b);
    c2.incrementBallots(b);
    c2.eliminate();
    candidates.push_back(c1);
    candidates.push_back(c2);
    ASSERT_EQ(2, lowestNumberOfBallots(candidates, 2, 3));
}


TEST(VotingFixture, needsToUpdate1) {
    vector<Candidate> candidates;
    vector<int> losers;
    Candidate c1("c1");
    Candidate c2("c2");
    Ballot b("1 2");
    c1.incrementBallots(b);
    candidates.push_back(c1);
    ASSERT_EQ(false, needsToUpdateBallot(candidates, b, losers, 0));
}

TEST(VotingFixture, needsToUpdate2) {
    vector<Candidate> candidates;
    vector<int> losers;
    Candidate c1("c1");
    Candidate c2("c2");
    Ballot b("1 2");
    c1.incrementBallots(b);
    c1.eliminate();
    candidates.push_back(c1);
    candidates.push_back(c2);
    ASSERT_EQ(true, needsToUpdateBallot(candidates, b, losers, 0));
}

TEST(VotingFixture, needsToUpdate3) {
    vector<Candidate> candidates;
    vector<int> losers;
    Candidate c1("c1");
    Candidate c2("c2");
    Ballot b("1 2");
    c1.incrementBallots(b);
    losers.push_back(0);
    candidates.push_back(c1);
    candidates.push_back(c2);
    ASSERT_EQ(true, needsToUpdateBallot(candidates, b, losers, 1));
}

TEST(VotingFixture, needsToUpdate4) {
    vector<Candidate> candidates;
    vector<int> losers;
    Candidate c1("c1");
    Candidate c2("c2");
    Candidate c3("c3");
    Ballot b("1 2 3");
    c1.incrementBallots(b);
    losers.push_back(0);
    c2.eliminate();
    candidates.push_back(c1);
    candidates.push_back(c2);
    candidates.push_back(c3);
    ASSERT_EQ(true, needsToUpdateBallot(candidates, b, losers, 1));
    b.incrementPreference();
    ASSERT_EQ(true, needsToUpdateBallot(candidates, b, losers, 1));
    b.incrementPreference();
    ASSERT_EQ(false, needsToUpdateBallot(candidates, b, losers, 1));
}

// -----
// solve
// -----

TEST(VotingFixture, solve1) {
    istringstream sin("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    ostringstream sout;
    voting_solve(sin, sout);
    ASSERT_EQ(sout.str(), "John Doe\n");
}

TEST(VotingFixture, solve2) {
    istringstream sin("2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
    ostringstream sout;
    voting_solve(sin, sout);
    ASSERT_EQ(sout.str(), "John Doe\n\nJohn Doe\n");
}

TEST(VotingFixture, solve3) {
    istringstream sin("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 2 1\n1 2 3");
    ostringstream sout;
    voting_solve(sin, sout);
    ASSERT_EQ(sout.str(), "John Doe\nJane Smith\n");
}

TEST(VotingFixture, solve4) {
    istringstream sin("1\n\n1\nJohn Doe\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1\n1");
    ostringstream sout;
    voting_solve(sin, sout);
    ASSERT_EQ(sout.str(), "John Doe\n");
}
