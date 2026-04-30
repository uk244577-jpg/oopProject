#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include "Backend.h"
using namespace std;

inline string extractField(const string& line, int fieldIndex) {
    int currentField = 0;
    string field = "";
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '|') {
            if (currentField == fieldIndex) {
                return field;
            }
            currentField++;
            field = "";
        } else {
            if (currentField == fieldIndex) {
                field += line[i];
            }
        }
    }
    if (currentField == fieldIndex) {
        return field;
    }
    return "";
}

inline bool adminUsernameExists(const string& username) {
    ifstream in("Admin.txt");
    string line;
    while (getline(in, line)) {
        string name = extractField(line, 0);
        if (name == username) {
            in.close();
            return true;
        }
    }
    in.close();
    return false;
}

inline bool candidateIdExists(const string& id) {
    ifstream in("Candidates.txt");
    string line;
    while (getline(in, line)) {
        string cid = extractField(line, 2);
        if (cid == id) {
            in.close();
            return true;
        }
    }
    in.close();
    return false;
}

inline int getCandidateCount() {
    ifstream inf("Candidates.txt");
    string line;
    int count = 0;
    while (getline(inf, line)) {
        if (line != "") {
            count++;
        }
    }
    inf.close();
    return count;
}

inline string generateCandidateID() {
    int n = getCandidateCount() + 1;
    return "C" + to_string(n);
}

class Admin : public User {
private:
    string adminId;

public:
    Admin() : User() {}

    bool login(Filehandler& fh) override {
        cout << endl;
        cout << "           ADMIN LOGIN        " << endl;
        cout << endl;
        cin.ignore();
        cout << "Username : ";
        getline(cin, username);
        cout << "Password : ";
        getline(cin, password);
        
        if (username == "") {
            cout << "Fields cannot be empty." << endl;
            return false;
        }
        if (password == "") {
            cout << "Fields cannot be empty." << endl;
            return false;
        }
        
        ifstream in("Admin.txt");
        if (!in.is_open()) {
            cout << "Could not open admin file." << endl;
            return false;
        }
        
        string line;
        while (getline(in, line)) {
            string n = extractField(line, 0);
            string p = extractField(line, 1);
            string id = extractField(line, 2);
            
            if (n == username && p == password) {
                adminId = id;
                in.close();
                cout << "Login successful! Welcome, " << username << endl;
                return true;
            }
        }
        in.close();
        cout << "Invalid admin information." << endl;
        return false;
    }

    bool loginFromForm(const string& inputName, const string& inputPass) {
        username = inputName;
        password = inputPass;

        if (username == "" || password == "") {
            return false;
        }

        ifstream in("Admin.txt");
        if (!in.is_open()) {
            return false;
        }

        string line;
        while (getline(in, line)) {
            string n = extractField(line, 0);
            string p = extractField(line, 1);
            string id = extractField(line, 2);

            if (n == username && p == password) {
                adminId = id;
                in.close();
                return true;
            }
        }
        in.close();
        return false;
    }
    
    bool addCandidate(const string& name, const string& party) {
        if (name == "" || party == "") {
            return false;
        }

        string id = generateCandidateID();
        if (candidateIdExists(id)) {
            id = "C" + to_string(getCandidateCount() + 2);
        }

        ofstream out("Candidates.txt", ios::app);
        if (!out.is_open()) {
            return false;
        }
        out << name << "|" << party << "|" << id << endl;
        out.close();
        return true;
    }
    
    bool removeCandidate(const string& removeId) {
        ifstream in("Candidates.txt");
        if (!in.is_open()) {
            return false;
        }

        string line, Data = "";
        bool found = false;
        while (getline(in, line)) {
            string id = extractField(line, 2);
            if (id == removeId) {
                found = true;
                continue;
            }
            Data += line + "\n";
        }
        in.close();

        ofstream out("Candidates.txt", ios::trunc);
        out << Data;
        out.close();

        return found;
    }
    
    bool deleteVoter(const string& voterId) {
        ifstream in("voter.txt");
        if (!in.is_open()) {
            return false;
        }

        string line, data = "";
        bool found = false;
        while (getline(in, line)) {
            string id = extractField(line, 2);
            if (id == voterId) {
                found = true;
                continue;
            }
            data += line + "\n";
        }
        in.close();

        ofstream out("voter.txt", ios::trunc);
        out << data;
        out.close();

        return found;
    }
    
    string viewCandidates() {
        ifstream in("Candidates.txt");
        string result = "";
        if (!in.is_open()) {
            return "No data found.";
        }

        string line;
        while (getline(in, line)) {
            if (line != "") {
                string name = extractField(line, 0);
                string party = extractField(line, 1);
                string id = extractField(line, 2);
                result += "ID: " + id + " | Name: " + name + " | Party: " + party + "\n";
            }
        }
        in.close();
        return result;
    }
    
    bool resetElection() {
        ofstream outfile1("votes.txt", ios::trunc);
        outfile1.close();

        ifstream in("voter.txt");
        string data = "", line;
        while (getline(in, line)) {
            string name = extractField(line, 0);
            string pass = extractField(line, 1);
            string id = extractField(line, 2);
            data += name + "|" + pass + "|" + id + "|0\n";
        }
        in.close();

        ofstream outfile2("voter.txt", ios::trunc);
        outfile2 << data;
        outfile2.close();

        return true;
    }

    string getAdminId() {
        return adminId;
    }
};
