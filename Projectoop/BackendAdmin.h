#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include "Backend.h"
using namespace std;

// Helper function to extract field from pipe-delimited string
string extractField(const string& line, int fieldIndex) {
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

bool adminUsernameExists(const string& username) {
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

bool candidateIdExists(const string& id) {
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

void registerAdmins() {
    int n;
    cout << "Enter number of admins to register: ";
    cin >> n;
    ofstream out("Admin.txt", ios::app);
    if (!out.is_open()) {
        cout << "File error." << endl;
        return;
    }
    for (int i = 1; i <= n; i++) {
        string name, pass;
        cin.ignore();
        cout << endl;
        cout << "Admin " << i << endl;
        while (true) {
            cout << "Enter username: ";
            getline(cin, name);
            if (name == "") {
                cout << "Username cannot be empty. Try to enter the username again." << endl;
                continue;
            }
            if (adminUsernameExists(name)) {
                cout << "Username already exists. Try Again" << endl;
                continue;
            }
            break;
        }
        while (true) {
            cout << "Enter Password: ";
            getline(cin, pass);
            if (pass == "") {
                cout << "Password cannot be empty. Try to enter the password again." << endl;
                continue;
            }
            if (pass.length() < 6) {
                cout << "Password must be at least 6 characters." << endl;
                continue;
            }
            break;
        }
        string Id = "A" + to_string(1000 + i);
        out << name << "|" << pass << "|" << Id << endl;
        cout << endl;
        cout << "Admin Registered with ID: " << Id << endl;
    }
    out.close();
    cout << endl;
    cout << "All admins registered successfully!!" << endl;
}

int getCandidateCount() {
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

string generateCandidateID() {
    int n = getCandidateCount() + 1;
    return "C" + to_string(n);
}

class Admin : public User {
private:
    string adminId;

public:
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
    
    void addCandidate() {
        string name, party;
        cin.ignore();
        while (true) {
            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter party: ";
            getline(cin, party);
            
            if (name == "" || party == "") {
                cout << "Invalid input. Try again" << endl;
                continue;
            }
            break;
        }
        
        string id = generateCandidateID();
        if (candidateIdExists(id)) {
            id = "C" + to_string(getCandidateCount() + 2);
        }
        cout << "Unique Candidate ID : " << id << endl;
        
        ofstream out("Candidates.txt", ios::app);
        if (!out.is_open()) {
            cout << "File error in opening." << endl;
            return;
        }
        out << name << "|" << party << "|" << id << endl;
        out.close();
        cout << "Candidate added successfully." << endl;
    }
    
    void removeCandidate() {
        string removeId;
        cout << "Enter ID for Removal: ";
        cin >> removeId;
        
        ifstream in("Candidates.txt");
        if (!in.is_open()) {
            cout << "Error in opening the desired file." << endl;
            return;
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
        
        if (found) {
            cout << "Candidate removed successfully." << endl;
        } else {
            cout << "Not found." << endl;
        }
    }
    
    void deleteVoter() {
        string voterId;
        cout << "Enter Voter ID to delete: ";
        cin >> voterId;
        
        ifstream in("voter.txt");
        if (!in.is_open()) {
            cout << "File error in opening." << endl;
            return;
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
        
        if (found) {
            cout << "Voter deleted successfully." << endl;
        } else {
            cout << "Voter not found." << endl;
        }
    }
    
    void viewCandidates() {
        ifstream in("Candidates.txt");
        if (!in.is_open()) {
            cout << "No data found in candidates.txt file." << endl;
            return;
        }
        
        string line;
        cout << "      Candidate List         " << endl;
        while (getline(in, line)) {
            string name = extractField(line, 0);
            string party = extractField(line, 1);
            string id = extractField(line, 2);
            
            cout << "ID: " << id << " | Name: " << name << " | Party: " << party << endl;
        }
        in.close();
    }
    
    void resetElection() {
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
        
        cout << "Election reset successfully. All votes cleared and voters marked as not voted." << endl;
    }
};
