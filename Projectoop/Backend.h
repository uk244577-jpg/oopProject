//cpp C:\Users\Usman\source\repos\Projectoop\Projectoop\Backend.h
#pragma once
//25L-2003
#include<iostream>
#include<string>
#include <sstream>
#include<fstream>
#include <ctime>
using namespace std;
class Filehandler {
	string voterFile;   // e.g. "voters.txt"
	string adminFile;   // e.g. "admins.txt"
public:
	Filehandler() {
		voterFile = "voter.txt";
		adminFile = "admins.txt";
	}bool savevoter(string& name, string& password, string& voterId) {
		ofstream outfile(voterFile, ios::app);
		if (!(outfile.is_open())) {
			cout << "file cannot be open" << endl;
			return false;
		}outfile << name << "|" << password << "|" << voterId << "|" << "0|\n";
		outfile.close();
		return true;
	}bool validateVoter(string& inputName, string& inputPass, string& foundId, bool& foundVoted) {
		ifstream infile(voterFile); // Open in read mode
		if (!infile.is_open()) {
			cout << "Could not open database file." << endl;
			return false;
		}

		string line;
		while (getline(infile, line)) {
			string f_name, f_pass, f_id, f_votedStr;
			stringstream ss(line);
			getline(ss, f_name, '|');
			getline(ss, f_pass, '|');
			getline(ss, f_id, '|');
			getline(ss, f_votedStr, '|');
			if (f_name == inputName && f_pass == inputPass) {
				foundId = f_id;
				foundVoted = (f_votedStr == "1");
				infile.close();
				return true;
			}
		}

		infile.close();
		return false;
	}

	// New: validate admin credentials from admins.txt
	bool validateAdmin(string& inputName, string& inputPass) {
		ifstream infile(adminFile);
		if (!infile.is_open()) {
			cout << "Could not open admin database file." << endl;
			return false;
		}
		string line;
		while (getline(infile, line)) {
			string f_name, f_pass;
			stringstream ss(line);
			getline(ss, f_name, '|');
			getline(ss, f_pass, '|');
			if (f_name == inputName && f_pass == inputPass) {
				infile.close();
				return true;
			}
		}
		infile.close();
		return false;
	}

	bool checkusernameExist(const string& username) {
		ifstream infile(voterFile); // Open in read mode
		if (!infile.is_open()) {
			cout << "Could not open database file." << endl;
			return false;
		}string line;
		while (getline(infile, line)) {
			string fname;
			stringstream ss(line);
			getline(ss, fname, '|'); //??
			if (fname == username) {
				infile.close();
				return true;
			}
		}infile.close();
		return false;
	}bool resetPassword(const string& username, const string& voterId, const string& newPassword) {
		ifstream infile(voterFile);
		if (!infile.is_open()) {
			cout << "Could not open database file." << endl;
			return false;
		}

		string allLines, line;
		bool found = false;

		while (getline(infile, line)) {
			string f_name, f_pass, f_id, f_votedStr;
			stringstream ss(line);
			getline(ss, f_name, '|');
			getline(ss, f_pass, '|');
			getline(ss, f_id, '|');
			getline(ss, f_votedStr, '|');

			if (f_name == username && f_id == voterId) {
				// Replace old password with new one, keep everything else same
				allLines += f_name + "|" + newPassword + "|" + f_id + "|" + f_votedStr + "\n";
				found = true;
			}
			else {
				allLines += line + "\n";
			}
		}
		infile.close();

		if (!found) {
			cout << "   No matching record found.\n";
			return false;
		}

		ofstream outFile(voterFile, ios::trunc);
		if (!outFile.is_open()) return false;
		outFile << allLines;
		outFile.close();
		return true;
	}
    // Mark voter as voted. If candidateId is provided, also record vote and include candidate on slip.
	bool markVoted(const string& voterID, const string& candidateId = "") {
		ifstream infile(voterFile); // Open in read mode
		if (!infile.is_open()) {
			cout << "Could not open database file." << endl;
			return false;
		}

		string allines, line;
		string voterName = "";
		while (getline(infile, line)) {
			string f_name, f_pass, f_id, f_votedStr;
			stringstream ss(line);
			getline(ss, f_name, '|');
			getline(ss, f_pass, '|');
			getline(ss, f_id, '|');
			getline(ss, f_votedStr, '|');
			if (f_id == voterID) {
				voterName = f_name;
				allines += f_name + "|" + f_pass + "|" + f_id + "|1\n";
			}
			else {
				allines += line + "\n";
			}
		}
		infile.close();

		ofstream outFile(voterFile, ios::trunc);
		if (!outFile.is_open()) return false;
		outFile << allines;
		outFile.close();

		// If candidateId provided, append to votes log
		if (!candidateId.empty()) {
			try {
				// record vote: voterID|candidateId|timestamp
				ofstream votesOut("votes.txt", ios::app);
				if (votesOut.is_open()) {
					time_t now = time(0);
					char buf[64];
					tm tmnow;
#ifdef _WIN32
					localtime_s(&tmnow, &now);
					strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tmnow);
#else
					tmnow = *localtime(&now);
					strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tmnow);
#endif
					votesOut << voterID << "|" << candidateId << "|" << buf << "\n";
					votesOut.close();
				}
			}
			catch (...) { /* ignore */ }
		}

		// Create a voting slip that includes candidate info if available
		try {
			std::string slipName = "slip_" + voterID + ".txt";
			ofstream slip(slipName, ios::out | ios::trunc);
			if (slip.is_open()) {
				time_t now = time(0);
				char buf[64];
				tm tmnow;
#ifdef _WIN32
				localtime_s(&tmnow, &now);
				strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tmnow);
#else
				tmnow = *localtime(&now);
				strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tmnow);
#endif
				slip << "Voter ID: " << voterID << "\n";
				if (!voterName.empty()) slip << "Voter Name: " << voterName << "\n";
				if (!candidateId.empty()) slip << "Voted For (Candidate ID): " << candidateId << "\n";
				slip << "Voted At: " << buf << "\n";
				slip << "Thank you for voting.\n";
				slip.close();
			}
		}
		catch (...) { /* ignore slip creation errors */ }

		return true;
	}
	bool removeCandidate(const string& candidateId) {
		ifstream infile("Candidates.txt");
		if (!infile.is_open()) {
			cout << "  Could not open Candidates file.\n";
			return false;
		}

		string allLines, line;
		bool found = false;

		while (getline(infile, line)) {
			if (line == "") continue;
			string name, party, cid;
			stringstream ss(line);
			getline(ss, name, '|');
			getline(ss, party, '|');
			getline(ss, cid, '|');

			if (cid == candidateId) {
				found = true;  
			}
			else {
				allLines += line + "\n";
			}
		}
		infile.close();

		if (!found) {
			cout << "  No candidate found with ID: " << candidateId << "\n";
			return false;
		}

		ofstream outFile("Candidates.txt", ios::trunc);
		if (!outFile.is_open()) return false;
		outFile << allLines;
		outFile.close();
		return true;
	}

	// Resets the election — clears all votes in voter.txt
	// and wipes Candidates.txt completely
	bool resetElection() {
		// Step 1: reset every voter's hasVoted flag back to 0
		ifstream infile(voterFile);
		if (!infile.is_open()) {
			cout << "  Could not open voter file.\n";
			return false;
		}

		string allLines, line;
		while (getline(infile, line)) {
			if (line == "") continue;
			string f_name, f_pass, f_id, f_voted;
			stringstream ss(line);
			getline(ss, f_name, '|');
			getline(ss, f_pass, '|');
			getline(ss, f_id, '|');
			getline(ss, f_voted, '|');

			// write same record but force hasVoted back to 0
			allLines += f_name + "|" + f_pass + "|" + f_id + "|0\n";
		}
		infile.close();

		ofstream outVoter(voterFile, ios::trunc);
		if (!outVoter.is_open()) return false;
		outVoter << allLines;
		outVoter.close();

		// Step 2: clear the candidates file entirely
		ofstream outCand("Candidates.txt", ios::trunc);
		if (outCand.is_open()) outCand.close();

		// Step 3: clear the Votes audit file
		ofstream outVotes("Votes.txt", ios::trunc);
		if (outVotes.is_open()) outVotes.close();

		return true;
	}

	// Deletes a voter record from voter.txt by username
	bool deleteVoter(const string& targetUsername) {
		ifstream infile(voterFile);
		if (!infile.is_open()) {
			cout << "  Could not open voter file.\n";
			return false;
		}

		string allLines, line;
		bool found = false;

		while (getline(infile, line)) {
			if (line == "") continue;
			string fname;
			stringstream ss(line);
			getline(ss, fname, '|');

			if (fname == targetUsername) {
				found = true;  // skip this line = delete it
			}
			else {
				allLines += line + "\n";
			}
		}
		infile.close();

		if (!found) {
			cout << "  Voter not found.\n";
			return false;
		}

		ofstream outFile(voterFile, ios::trunc);
		if (!outFile.is_open()) return false;
		outFile << allLines;
		outFile.close();
		return true;
	}int getCandidateCount() {
		ifstream inf("Candidates.txt");
		string line;
		int count = 0;
		while (getline(inf, line)) {
			if (line != "") {
				count++;
			}
		}
		return count;
	}
	string generateCandidateID() {
		int n = getCandidateCount() + 1;
		return "C" + to_string(n);
	}
	bool candidateIdExists(const string& id) {
		ifstream in("Candidates.txt");
		string line;
		while (getline(in, line)) {
			string name, party, cid;
			stringstream ss(line);
			getline(ss, name, '|');
			getline(ss, party, '|');
			getline(ss, cid, '|');
			if (cid == id) {
				return true;
			}
		}
		return false;
	}bool adminUsernameExists(const string& username) {
		ifstream in("Admin.txt");

		// if file does not exist yet, no admin exists
		if (!in.is_open()) {
			return false;
		}

		string line;
		while (getline(in, line)) {
			if (line == "") continue;

			string name, pass, id;
			stringstream ss(line);
			getline(ss, name, '|');
			getline(ss, pass, '|');
			getline(ss, id, '|');

			if (name == username) {
				in.close();
				return true;   // username found
			}
		}

		in.close();
		return false;  
	}
	void registerAdmins() {
		int n;
		cout << "\n  ---- Register New Admin ----\n";
		cout << "  How many admins to register : ";
		cin >> n;
		cin.ignore();

		if (n <= 0) {
			cout << "  Invalid number. Going back.\n";
			return;
		}

		ofstream out("Admin.txt", ios::app);
		if (!out.is_open()) {
			cout << "  Could not open Admin file.\n";
			return;
		}

		for (int i = 1; i <= n; i++) {
			cout << "\n  ---- Admin " << i << " of " << n << " ----\n";

			// ── Username input with duplicate check ──
			string name;
			while (true) {
				cout << "  Enter username : ";
				getline(cin, name);

				if (name == "") {
					cout << "  Username cannot be empty. Try again.\n";
					continue;
				}
				if (adminUsernameExists(name)) {
					cout << "  Username already taken. Try a different one.\n";
					continue;
				}
				break;  
			}

	
			string pass;
			while (true) {
				cout << "  Enter password : ";
				getline(cin, pass);

				if (pass == "") {
					cout << "  Password cannot be empty. Try again.\n";
					continue;
				}
				if (pass.length() < 6) {
					cout << "  Password must be at least 6 characters. Try again.\n";
					continue;
				}
				break;  // password is valid
			}

			// ── Confirm password ──
			string confirmPass;
			while (true) {
				cout << "  Confirm password : ";
				getline(cin, confirmPass);

				if (confirmPass != pass) {
					cout << "  Passwords do not match. Try again.\n";
					continue;
				}
				break; 
			}
			ifstream countFile("Admin.txt");
			int count = 0;
			string tempLine;
			while (getline(countFile, tempLine)) {
				if (tempLine != "") count++;
			}
			countFile.close();

			string adminId = "A" + to_string(count + 1);

			out << name << "|" << pass << "|" << adminId << "\n";

			cout << "  Admin registered successfully.\n";
			cout << "  Assigned Admin ID : " << adminId << "\n";
		}

		out.close();
		cout << "\n  All " << n << " admin(s) registered successfully.\n";
	}
};
class User {
protected:
	string username;
	string password;
	string role;
public:
	User() {
		username = "";
		password = "";
		role = "";
	}User(string& name, string& password, string& role) {
		this->username = name;
		this->password = password;
		this->role = role;
	}void setUsername(string& u) {
		this->username = u;
	}void setPassword(string& s) {
		this->password = s;
	}string getrole() {
		return role;
	}string getusername() {
		return username;
	} virtual bool login(Filehandler& fh) = 0;
	virtual ~User() {}
}; class Voter :public User {
private:
	string voterId;
	bool hasVoted;
public:
	Voter() {
		voterId = "";
		hasVoted = false;
		role = "Voter";
	}string getvoterId() {
		return voterId;
	}bool gethasVoted() {
		return hasVoted;
	} bool registerVote(Filehandler& fh) {
		cout << "enter username" << endl;
		cin >> username;
		cin.ignore();
		if (fh.checkusernameExist(username)) {
			cout << "   Username already taken. Try another.\n";
			return false;
		}cout << "  Enter password : ";
		cin >> password;
		cin.ignore();
		cout << "  Enter Voter ID : ";
		cin >> voterId;
		cin.ignore();
		if (fh.savevoter(username, password, voterId)) {
			cout << "   Registration successful!\n";
			return true;
		}   cout << "   Registration failed (file error).\n";
		return false;

	} bool login(Filehandler& fh) override {

		cout << "  Username : ";
		cin >> username;
		cin.ignore();

		cout << "  Password : ";
		cin >> password;

		if (fh.validateVoter(username, password, voterId, hasVoted)) {
			cout << "\n  [✓] Login successful! Welcome, " << username << ".\n";
			cout << "  Voter ID  : " << voterId << "\n";
			cout << "  Status    : " << (hasVoted ? "Already voted" : "Not voted yet") << "\n";
			return true;
		}
		cout << "\n  Invalid username or password.\n";
		return false;
	}bool forgetPassword(Filehandler& fh) {
		

		string inputUsername, inputVoterId;
		cout << "  Enter your Username : ";
		cin >> inputUsername;
		cin.ignore();
		if (!fh.checkusernameExist(inputUsername)) {
			cout << "  [!] Username not found.\n";
			return false;
		}

		cout << "  Enter your Voter ID : ";
		cin >> inputVoterId;
		cin.ignore();

		string newPass, confirmPass;
		cout << "  Enter new password  : ";
		cin >> newPass;
		cin.ignore();

		cout << "  Confirm password    : ";
		cin >> confirmPass;
		cin.ignore();

		if (newPass != confirmPass) {
			cout << "   Passwords do not match. Try again.\n";
			return false;
		}

		if (newPass.length() < 6) {
			cout << "   Password too short. Minimum 6 characters.\n";
			return false;
		}

		if (fh.resetPassword(inputUsername, inputVoterId, newPass)) {
			cout << "   Password reset successful. Please login again.\n";
			return true;
		}

		cout << "   Voter ID does not match. Reset failed.\n";
		return false;
	}
};
class Admin : public User {
private:
	string adminId;

public:
	Admin() {
		adminId = "";
		role = "Admin";
	}

	string getAdminId() {
		return adminId;
	}

	
	bool login(Filehandler& fh) override {
		cout << "\n╔══════════════════════════╗\n";
		cout << "║       ADMIN LOGIN        ║\n";
		cout << "╚══════════════════════════╝\n";

		cout << "  Username : ";
		cin >> username;
		cin.ignore();

		cout << "  Password : ";
		cin >> password;
		cin.ignore();

		if (fh.validateAdmin(username, password)) {
			cout << "\n  Welcome, " << username << ". Admin access granted.\n";
			return true;
		}
		cout << "\n  Invalid credentials. Access denied.\n";
		return false;
	}

	// Add a new candidate — ID is auto generated by FileHandler
	void addCandidate(Filehandler& fh) {
		string name, party;

		cout << "\n  ---- Add Candidate ----\n";
		cout << "  Candidate Name  : ";
		cin.ignore();
		getline(cin, name);

		if (name == "") {
			cout << "  Name cannot be empty.\n";
			return;
		}

		cout << "  Party Name      : ";
		getline(cin, party);

		if (party == "") {
			cout << "  Party cannot be empty.\n";
			return;
		}

		string id = fh.generateCandidateID();

		ofstream out("Candidates.txt", ios::app);
		if (!out.is_open()) {
			cout << "  Could not open Candidates file.\n";
			return;
		}
		out << name << "|" << party << "|" << id << "\n";
		out.close();

		cout << "  Candidate added. Assigned ID: " << id << "\n";
	}
	void removeCandidate(Filehandler& fh) {
		cout << "\n  ---- Remove Candidate ----\n";
		ifstream in("Candidates.txt");
		if (!in.is_open()) {
			cout << "  Could not open Candidates file.\n";
			return;
		}

		string line;
		int count = 0;
		cout << "  Current candidates:\n";
		while (getline(in, line)) {
			if (line == "") continue;
			string name, party, cid;
			stringstream ss(line);
			getline(ss, name, '|');
			getline(ss, party, '|');
			getline(ss, cid, '|');
			cout << "    ID: " << cid
				<< "  |  Name: " << name
				<< "  |  Party: " << party << "\n";
			count++;
		}
		in.close();

		if (count == 0) {
			cout << "  No candidates registered yet.\n";
			return;
		}

		string targetId;
		cout << "\n  Enter Candidate ID to remove : ";
		cin >> targetId;
		cin.ignore();

		if (!fh.candidateIdExists(targetId)) {
			cout << "  No candidate found with that ID.\n";
			return;
		}

		if (fh.removeCandidate(targetId)) {
			cout << "  Candidate " << targetId << " removed successfully.\n";
		}
	}
	void viewCandidates() {
		ifstream in("Candidates.txt");
		if (!in.is_open()) {
			cout << "  Could not open Candidates file.\n";
			return;
		}

		string line;
		int count = 1;
		cout << "\n  ---- Candidate List ----\n";

		while (getline(in, line)) {
			if (line == "") continue;
			string name, party, cid;
			stringstream ss(line);
			getline(ss, name, '|');
			getline(ss, party, '|');
			getline(ss, cid, '|');
			cout << "  " << count++ << ".  ID: " << cid
				<< "  |  Name: " << name
				<< "  |  Party: " << party << "\n";
		}
		in.close();

		if (count == 1) {
			cout << "  No candidates registered yet.\n";
		}
	}
	void deleteVoterAccount(Filehandler& fh) {
		cout << "\n  ---- Delete Voter ----\n";
		cout << "  Enter voter username to delete : ";
		string targetUsername;
		cin >> targetUsername;
		cin.ignore();

		if (!fh.checkusernameExist(targetUsername)) {
			cout << "  Username not found in the system.\n";
			return;
		}
		char confirm;
		cout << "  Are you sure you want to delete '" << targetUsername << "'? (y/n) : ";
		cin >> confirm;
		cin.ignore();

		if (confirm != 'y' && confirm != 'Y') {
			cout << "  Deletion cancelled.\n";
			return;
		}

		if (fh.deleteVoter(targetUsername)) {
			cout << "  Voter '" << targetUsername << "' deleted successfully.\n";
		}
	}

	// View how many people voted vs total registered
	void viewResults() {
		ifstream voters("voter.txt");
		if (!voters.is_open()) {
			cout << "  Could not open voter file.\n";
			return;
		}

		int total = 0, voted = 0;
		string line;

		while (getline(voters, line)) {
			if (line == "") continue;
			total++;
			string f_name, f_pass, f_id, f_voted;
			stringstream ss(line);
			getline(ss, f_name, '|');
			getline(ss, f_pass, '|');
			getline(ss, f_id, '|');
			getline(ss, f_voted, '|');
			if (f_voted == "1") voted++;
		}
		voters.close();

		cout << "\n  ---- Voting Results ----\n";
		cout << "  Total Registered Voters : " << total << "\n";
		cout << "  Votes Cast              : " << voted << "\n";
		cout << "  Yet to Vote             : " << (total - voted) << "\n";

		if (total > 0) {
			int percent = (voted * 100) / total;
			cout << "  Turnout                 : " << percent << "%\n";
		}
	}

	void resetElection(Filehandler& fh) {
		cout << "\n  ---- Reset Election ----\n";
		cout << "  WARNING: This will clear all votes and candidates.\n";
		cout << "  Type CONFIRM to proceed : ";

		string input;
		cin >> input;
		cin.ignore();

		if (input != "CONFIRM") {
			cout << "  Reset cancelled.\n";
			return;
		}

		if (fh.resetElection()) {
			cout << "  Election reset successfully.\n";
			cout << "  All votes cleared. Candidates list wiped.\n";
		}
		else {
			cout << "  Reset failed. Check your files.\n";
		}
	}


	void adminPanel(Filehandler& fh) {
		int choice;
		do {
			int pad = 10 - username.length();
			for (int i = 0; i < pad; i++) cout << " ";
		
			cout << "  1. Add Candidate\n";
			cout << "  2. Remove Candidate\n";
			cout << "  3. View Candidates\n";
			cout << "  4. Delete a Voter\n";
			cout << "  5. View Voting Results\n";
			cout << "  6. Reset Election\n";
			cout << "  7. Register New Admin\n";
			cout << "  8. Logout\n";
			cout << "  Choice : ";
			cin >> choice;
			cin.ignore();

			if (choice == 1) addCandidate(fh);
			else if (choice == 2) removeCandidate(fh);
			else if (choice == 3) viewCandidates();
			else if (choice == 4) deleteVoterAccount(fh);
			else if (choice == 5) viewResults();
			else if (choice == 6) resetElection(fh);
			else if (choice == 7) fh.registerAdmins();
			else if (choice == 8) cout << "  Admin logged out. Goodbye!\n";
			else                  cout << "  Invalid option. Try again.\n";

		} while (choice != 8);
	}
};