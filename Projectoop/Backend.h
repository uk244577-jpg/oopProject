//cpp C:\Users\Usman\source\repos\Projectoop\Projectoop\Backend.h
#pragma once
//25L-2003
#include<iostream>
#include<string>
#include <sstream>
#include<fstream>
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
	bool markVoted(const string& voterID) {
		ifstream infile(voterFile); // Open in read mode
		if (!infile.is_open()) {
			cout << "Could not open database file." << endl;
			return false;
		}string allines, line;
		while (getline(infile, line)) {
			string f_name, f_pass, f_id, f_votedStr;
			stringstream ss(line);
			getline(ss, f_name, '|');
			getline(ss, f_pass, '|');
			getline(ss, f_id, '|');
			getline(ss, f_votedStr, '|');
			if (f_id == voterID) {
				allines += f_name + "|" + f_pass + "|" + f_id + "|1\n";
			}
			else {
				allines += line + "\n";
			}
		}infile.close();
		ofstream outFile(voterFile, ios::trunc);
		if (!outFile.is_open()) return false;
		outFile << allines;
		outFile.close();
		return true;
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
		cout << "\n╔══════════════════════════╗\n";
		cout << "║       VOTER LOGIN        ║\n";
		cout << "╚══════════════════════════╝\n";
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
		cout << "\n╔══════════════════════════╗\n";
		cout << "║     FORGOT PASSWORD      ║\n";
		cout << "╚═=════════════════════════╝\n";

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
