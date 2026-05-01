#pragma once
// VoteTracker.h
// Stores which candidate each voter voted for
// Works alongside your existing Backend.h without modifying it

#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <map>
#include <vector>

using namespace std;

ref class VoteTracker
{
public:
    // Saves a vote to votes.txt
    // Parameters: voterID (string), candidateID (string)
    static bool saveVote(const string& voterID, const string& candidateID)
    {
        ofstream out("votes.txt", ios::app);
        if (!out.is_open()) return false;

        // Get current timestamp
        time_t now = time(0);
        string timestamp = ctime(&now);
        timestamp.pop_back(); // Remove newline

        out << voterID << "|" << candidateID << "|" << timestamp << "\n";
        out.close();
        return true;
    }

    // Gets vote count for a specific candidate
    static int getVoteCountForCandidate(const string& candidateID)
    {
        ifstream in("votes.txt");
        if (!in.is_open()) return 0;

        string line;
        int count = 0;
        while (getline(in, line))
        {
            if (line.empty()) continue;
            string vID, cID, time;
            stringstream ss(line);
            getline(ss, vID, '|');
            getline(ss, cID, '|');
            getline(ss, time, '|');
            if (cID == candidateID) count++;
        }
        in.close();
        return count;
    }

    // Gets total number of votes cast
    static int getTotalVotes()
    {
        ifstream in("votes.txt");
        if (!in.is_open()) return 0;

        string line;
        int count = 0;
        while (getline(in, line))
        {
            if (!line.empty()) count++;
        }
        in.close();
        return count;
    }

    // Checks if a specific voter has already voted (using votes.txt)
    static bool hasVoterVoted(const string& voterID)
    {
        ifstream in("votes.txt");
        if (!in.is_open()) return false;

        string line;
        while (getline(in, line))
        {
            if (line.empty()) continue;
            string vID, cID, time;
            stringstream ss(line);
            getline(ss, vID, '|');
            if (vID == voterID)
            {
                in.close();
                return true;
            }
        }
        in.close();
        return false;
    }

    // Gets which candidate a voter voted for
    static string getCandidateVotedBy(const string& voterID)
    {
        ifstream in("votes.txt");
        if (!in.is_open()) return "";

        string line;
        while (getline(in, line))
        {
            if (line.empty()) continue;
            string vID, cID, time;
            stringstream ss(line);
            getline(ss, vID, '|');
            getline(ss, cID, '|');
            if (vID == voterID)
            {
                in.close();
                return cID;
            }
        }
        in.close();
        return "";
    }

    // Gets all votes (for voting history)
    static vector<string> getAllVotes()
    {
        vector<string> votes;
        ifstream in("votes.txt");
        if (!in.is_open()) return votes;

        string line;
        while (getline(in, line))
        {
            if (!line.empty())
            {
                votes.push_back(line);
            }
        }
        in.close();
        return votes;
    }

    // Clears all votes (for election reset)
    static bool clearAllVotes()
    {
        ofstream out("votes.txt", ios::trunc);
        if (!out.is_open()) return false;
        out.close();
        return true;
    }
};
