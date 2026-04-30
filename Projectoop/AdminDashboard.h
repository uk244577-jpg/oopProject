#pragma once
#include "Backend.h"
#include <msclr\marshal_cppstd.h>
#include <fstream>
#include <string>
#include <sstream>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace Projectoop {

    public ref class AdminDashboard : public System::Windows::Forms::Form
    {
    public:
        AdminDashboard(void)
        {
            InitializeComponent();
        }

    protected:
        ~AdminDashboard()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::ListBox^ listCandidates;
        System::Windows::Forms::Button^ btnRefreshCandidates;
        System::Windows::Forms::GroupBox^ groupAddCandidate;
        System::Windows::Forms::TextBox^ txtCandName;
        System::Windows::Forms::TextBox^ txtCandParty;
        System::Windows::Forms::Button^ btnAddCandidate;
        System::Windows::Forms::Label^ lblCandName;
        System::Windows::Forms::Label^ lblCandParty;
        System::Windows::Forms::GroupBox^ groupRemoveCandidate;
        System::Windows::Forms::TextBox^ txtCandIdToRemove;
        System::Windows::Forms::Button^ btnRemoveCandidate;
        System::Windows::Forms::Label^ lblRemoveId;
        System::Windows::Forms::GroupBox^ groupVoter;
        System::Windows::Forms::TextBox^ txtVoterUsername;
        System::Windows::Forms::Button^ btnDeleteVoter;
        System::Windows::Forms::Label^ lblVoterUser;
        System::Windows::Forms::GroupBox^ groupSystem;
        System::Windows::Forms::Button^ btnViewResults;
        System::Windows::Forms::Button^ btnResetElection;
        System::Windows::Forms::GroupBox^ groupAdmin;
        System::Windows::Forms::TextBox^ txtAdminUser;
        System::Windows::Forms::TextBox^ txtAdminPass;
        System::Windows::Forms::Button^ btnRegAdmin;
        System::Windows::Forms::Label^ lblAdminUser;
        System::Windows::Forms::Label^ lblAdminPass;
        System::Windows::Forms::Button^ btnLogout;

        System::ComponentModel::Container ^components;

        void InitializeComponent(void)
        {
            this->listCandidates = (gcnew System::Windows::Forms::ListBox());
            this->btnRefreshCandidates = (gcnew System::Windows::Forms::Button());
            this->groupAddCandidate = (gcnew System::Windows::Forms::GroupBox());
            this->lblCandName = (gcnew System::Windows::Forms::Label());
            this->txtCandName = (gcnew System::Windows::Forms::TextBox());
            this->lblCandParty = (gcnew System::Windows::Forms::Label());
            this->txtCandParty = (gcnew System::Windows::Forms::TextBox());
            this->btnAddCandidate = (gcnew System::Windows::Forms::Button());
            this->groupRemoveCandidate = (gcnew System::Windows::Forms::GroupBox());
            this->lblRemoveId = (gcnew System::Windows::Forms::Label());
            this->txtCandIdToRemove = (gcnew System::Windows::Forms::TextBox());
            this->btnRemoveCandidate = (gcnew System::Windows::Forms::Button());
            this->groupVoter = (gcnew System::Windows::Forms::GroupBox());
            this->lblVoterUser = (gcnew System::Windows::Forms::Label());
            this->txtVoterUsername = (gcnew System::Windows::Forms::TextBox());
            this->btnDeleteVoter = (gcnew System::Windows::Forms::Button());
            this->groupSystem = (gcnew System::Windows::Forms::GroupBox());
            this->btnViewResults = (gcnew System::Windows::Forms::Button());
            this->btnResetElection = (gcnew System::Windows::Forms::Button());
            this->groupAdmin = (gcnew System::Windows::Forms::GroupBox());
            this->lblAdminUser = (gcnew System::Windows::Forms::Label());
            this->txtAdminUser = (gcnew System::Windows::Forms::TextBox());
            this->lblAdminPass = (gcnew System::Windows::Forms::Label());
            this->txtAdminPass = (gcnew System::Windows::Forms::TextBox());
            this->btnRegAdmin = (gcnew System::Windows::Forms::Button());
            this->btnLogout = (gcnew System::Windows::Forms::Button());

            // 
            // Form setup
            // 
            this->ClientSize = System::Drawing::Size(600, 480);
            this->Text = L"Admin Dashboard";
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;

            // listCandidates
            this->listCandidates->FormattingEnabled = true;
            this->listCandidates->Location = System::Drawing::Point(12, 12);
            this->listCandidates->Size = System::Drawing::Size(250, 400);

            // btnRefreshCandidates
            this->btnRefreshCandidates->Location = System::Drawing::Point(12, 420);
            this->btnRefreshCandidates->Size = System::Drawing::Size(250, 30);
            this->btnRefreshCandidates->Text = L"Refresh Candidates";
            this->btnRefreshCandidates->Click += gcnew System::EventHandler(this, &AdminDashboard::btnRefreshCandidates_Click);

            // groupAddCandidate
            this->groupAddCandidate->Location = System::Drawing::Point(280, 12);
            this->groupAddCandidate->Size = System::Drawing::Size(300, 100);
            this->groupAddCandidate->Text = L"Add Candidate";

            this->lblCandName->Location = System::Drawing::Point(10, 25);
            this->lblCandName->Size = System::Drawing::Size(50, 20);
            this->lblCandName->Text = L"Name:";
            this->txtCandName->Location = System::Drawing::Point(60, 22);
            this->txtCandName->Size = System::Drawing::Size(130, 20);

            this->lblCandParty->Location = System::Drawing::Point(10, 55);
            this->lblCandParty->Size = System::Drawing::Size(50, 20);
            this->lblCandParty->Text = L"Party:";
            this->txtCandParty->Location = System::Drawing::Point(60, 52);
            this->txtCandParty->Size = System::Drawing::Size(130, 20);

            this->btnAddCandidate->Location = System::Drawing::Point(200, 22);
            this->btnAddCandidate->Size = System::Drawing::Size(80, 50);
            this->btnAddCandidate->Text = L"Add";
            this->btnAddCandidate->Click += gcnew System::EventHandler(this, &AdminDashboard::btnAddCandidate_Click);

            this->groupAddCandidate->Controls->Add(this->lblCandName);
            this->groupAddCandidate->Controls->Add(this->txtCandName);
            this->groupAddCandidate->Controls->Add(this->lblCandParty);
            this->groupAddCandidate->Controls->Add(this->txtCandParty);
            this->groupAddCandidate->Controls->Add(this->btnAddCandidate);

            // groupRemoveCandidate
            this->groupRemoveCandidate->Location = System::Drawing::Point(280, 120);
            this->groupRemoveCandidate->Size = System::Drawing::Size(300, 60);
            this->groupRemoveCandidate->Text = L"Remove Candidate";

            this->lblRemoveId->Location = System::Drawing::Point(10, 25);
            this->lblRemoveId->Size = System::Drawing::Size(50, 20);
            this->lblRemoveId->Text = L"ID:";
            this->txtCandIdToRemove->Location = System::Drawing::Point(60, 22);
            this->txtCandIdToRemove->Size = System::Drawing::Size(130, 20);

            this->btnRemoveCandidate->Location = System::Drawing::Point(200, 20);
            this->btnRemoveCandidate->Size = System::Drawing::Size(80, 25);
            this->btnRemoveCandidate->Text = L"Remove";
            this->btnRemoveCandidate->Click += gcnew System::EventHandler(this, &AdminDashboard::btnRemoveCandidate_Click);

            this->groupRemoveCandidate->Controls->Add(this->lblRemoveId);
            this->groupRemoveCandidate->Controls->Add(this->txtCandIdToRemove);
            this->groupRemoveCandidate->Controls->Add(this->btnRemoveCandidate);

            // groupVoter
            this->groupVoter->Location = System::Drawing::Point(280, 190);
            this->groupVoter->Size = System::Drawing::Size(300, 60);
            this->groupVoter->Text = L"Delete Voter";

            this->lblVoterUser->Location = System::Drawing::Point(10, 25);
            this->lblVoterUser->Size = System::Drawing::Size(50, 20);
            this->lblVoterUser->Text = L"User:";
            this->txtVoterUsername->Location = System::Drawing::Point(60, 22);
            this->txtVoterUsername->Size = System::Drawing::Size(130, 20);

            this->btnDeleteVoter->Location = System::Drawing::Point(200, 20);
            this->btnDeleteVoter->Size = System::Drawing::Size(80, 25);
            this->btnDeleteVoter->Text = L"Delete";
            this->btnDeleteVoter->Click += gcnew System::EventHandler(this, &AdminDashboard::btnDeleteVoter_Click);

            this->groupVoter->Controls->Add(this->lblVoterUser);
            this->groupVoter->Controls->Add(this->txtVoterUsername);
            this->groupVoter->Controls->Add(this->btnDeleteVoter);

            // groupSystem
            this->groupSystem->Location = System::Drawing::Point(280, 260);
            this->groupSystem->Size = System::Drawing::Size(300, 60);
            this->groupSystem->Text = L"System Operations";

            this->btnViewResults->Location = System::Drawing::Point(20, 22);
            this->btnViewResults->Size = System::Drawing::Size(120, 25);
            this->btnViewResults->Text = L"View Turnout Results";
            this->btnViewResults->Click += gcnew System::EventHandler(this, &AdminDashboard::btnViewResults_Click);

            this->btnResetElection->Location = System::Drawing::Point(150, 22);
            this->btnResetElection->Size = System::Drawing::Size(130, 25);
            this->btnResetElection->Text = L"Reset Election Data";
            this->btnResetElection->Click += gcnew System::EventHandler(this, &AdminDashboard::btnResetElection_Click);

            this->groupSystem->Controls->Add(this->btnViewResults);
            this->groupSystem->Controls->Add(this->btnResetElection);


            // groupAdmin
            this->groupAdmin->Location = System::Drawing::Point(280, 330);
            this->groupAdmin->Size = System::Drawing::Size(300, 100);
            this->groupAdmin->Text = L"Register New Admin";

            this->lblAdminUser->Location = System::Drawing::Point(10, 25);
            this->lblAdminUser->Size = System::Drawing::Size(50, 20);
            this->lblAdminUser->Text = L"User:";
            this->txtAdminUser->Location = System::Drawing::Point(60, 22);
            this->txtAdminUser->Size = System::Drawing::Size(130, 20);

            this->lblAdminPass->Location = System::Drawing::Point(10, 55);
            this->lblAdminPass->Size = System::Drawing::Size(50, 20);
            this->lblAdminPass->Text = L"Pass:";
            this->txtAdminPass->Location = System::Drawing::Point(60, 52);
            this->txtAdminPass->Size = System::Drawing::Size(130, 20);

            this->btnRegAdmin->Location = System::Drawing::Point(200, 22);
            this->btnRegAdmin->Size = System::Drawing::Size(80, 50);
            this->btnRegAdmin->Text = L"Register";
            this->btnRegAdmin->Click += gcnew System::EventHandler(this, &AdminDashboard::btnRegAdmin_Click);

            this->groupAdmin->Controls->Add(this->lblAdminUser);
            this->groupAdmin->Controls->Add(this->txtAdminUser);
            this->groupAdmin->Controls->Add(this->lblAdminPass);
            this->groupAdmin->Controls->Add(this->txtAdminPass);
            this->groupAdmin->Controls->Add(this->btnRegAdmin);

            // btnLogout
            this->btnLogout->Location = System::Drawing::Point(280, 440);
            this->btnLogout->Size = System::Drawing::Size(300, 30);
            this->btnLogout->Text = L"Logout";
            this->btnLogout->Click += gcnew System::EventHandler(this, &AdminDashboard::btnLogout_Click);

            this->Controls->Add(this->listCandidates);
            this->Controls->Add(this->btnRefreshCandidates);
            this->Controls->Add(this->groupAddCandidate);
            this->Controls->Add(this->groupRemoveCandidate);
            this->Controls->Add(this->groupVoter);
            this->Controls->Add(this->groupSystem);
            this->Controls->Add(this->groupAdmin);
            this->Controls->Add(this->btnLogout);

            this->Load += gcnew System::EventHandler(this, &AdminDashboard::AdminDashboard_Load);
        }

    private: 
        System::Void AdminDashboard_Load(System::Object^ sender, System::EventArgs^ e) {
            RefreshCandidates();
        }

        void RefreshCandidates() {
            listCandidates->Items->Clear();
            std::ifstream in("Candidates.txt");
            if (!in.is_open()) return;

            std::string line;
            while (std::getline(in, line)) {
                if (line.empty()) continue;
                std::string name, party, cid;
                std::stringstream ss(line);
                std::getline(ss, name, '|');
                std::getline(ss, party, '|');
                std::getline(ss, cid, '|');

                String^ displayStr = gcnew String(("ID: " + cid + " | " + name + " (" + party + ")").c_str());
                listCandidates->Items->Add(displayStr);
            }
            in.close();
        }

        System::Void btnRefreshCandidates_Click(System::Object^ sender, System::EventArgs^ e) {
            RefreshCandidates();
        }

        System::Void btnAddCandidate_Click(System::Object^ sender, System::EventArgs^ e) {
            if (String::IsNullOrWhiteSpace(txtCandName->Text) || String::IsNullOrWhiteSpace(txtCandParty->Text)) {
                MessageBox::Show("Name and Party are required.");
                return;
            }

            msclr::interop::marshal_context context;
            std::string name = context.marshal_as<std::string>(txtCandName->Text);
            std::string party = context.marshal_as<std::string>(txtCandParty->Text);

            Filehandler fh;
            std::string newId = fh.generateCandidateID();

            std::ofstream out("Candidates.txt", std::ios::app);
            if (out.is_open()) {
                out << name << "|" << party << "|" << newId << "\n";
                out.close();
                MessageBox::Show(gcnew String(("Candidate added with ID: " + newId).c_str()), "Success");
                txtCandName->Clear();
                txtCandParty->Clear();
                RefreshCandidates();
            }
        }

        System::Void btnRemoveCandidate_Click(System::Object^ sender, System::EventArgs^ e) {
            if (String::IsNullOrWhiteSpace(txtCandIdToRemove->Text)) return;

            msclr::interop::marshal_context context;
            std::string cid = context.marshal_as<std::string>(txtCandIdToRemove->Text);

            Filehandler fh;
            if (!fh.candidateIdExists(cid)) {
                MessageBox::Show("Candidate ID does not exist.");
                return;
            }

            if (fh.removeCandidate(cid)) {
                MessageBox::Show("Candidate removed successfully.");
                txtCandIdToRemove->Clear();
                RefreshCandidates();
            }
        }

        System::Void btnDeleteVoter_Click(System::Object^ sender, System::EventArgs^ e) {
            if (String::IsNullOrWhiteSpace(txtVoterUsername->Text)) return;

            msclr::interop::marshal_context context;
            std::string user = context.marshal_as<std::string>(txtVoterUsername->Text);

            Filehandler fh;
            if (!fh.checkusernameExist(user)) {
                MessageBox::Show("Voter username not found.");
                return;
            }

            if (fh.deleteVoter(user)) {
                MessageBox::Show("Voter deleted successfully.");
                txtVoterUsername->Clear();
            }
        }

        System::Void btnViewResults_Click(System::Object^ sender, System::EventArgs^ e) {
            std::ifstream voters("voter.txt");
            if (!voters.is_open()) {
                MessageBox::Show("Could not open voter file.");
                return;
            }

            int total = 0, voted = 0;
            std::string line;

            while (std::getline(voters, line)) {
                if (line.empty()) continue;
                total++;
                std::string f_name, f_pass, f_id, f_votedStr;
                std::stringstream ss(line);
                std::getline(ss, f_name, '|');
                std::getline(ss, f_pass, '|');
                std::getline(ss, f_id, '|');
                std::getline(ss, f_votedStr, '|');
                if (f_votedStr == "1" || f_votedStr == "1\r") voted++;
            }
            voters.close();

            int percent = total > 0 ? (voted * 100) / total : 0;
            String^ resultMsg = String::Format("Total Registered: {0}\nVotes Cast: {1}\nYet to Vote: {2}\nTurnout: {3}%", 
                                total, voted, (total - voted), percent);
            MessageBox::Show(resultMsg, "Voting Results");
        }

        System::Void btnResetElection_Click(System::Object^ sender, System::EventArgs^ e) {
            System::Windows::Forms::DialogResult res = MessageBox::Show("Are you sure you want to reset the election? This wipes all candidates and votes.", "Warning", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
            if (res == System::Windows::Forms::DialogResult::Yes) {
                Filehandler fh;
                if (fh.resetElection()) {
                    MessageBox::Show("Election has been reset.");
                    RefreshCandidates();
                }
            }
        }

        System::Void btnRegAdmin_Click(System::Object^ sender, System::EventArgs^ e) {
            if (String::IsNullOrWhiteSpace(txtAdminUser->Text) || String::IsNullOrWhiteSpace(txtAdminPass->Text)) {
                MessageBox::Show("Username and password required.");
                return;
            }

            msclr::interop::marshal_context context;
            std::string name = context.marshal_as<std::string>(txtAdminUser->Text);
            std::string pass = context.marshal_as<std::string>(txtAdminPass->Text);

            if (pass.length() < 6) {
                MessageBox::Show("Password must be at least 6 characters.");
                return;
            }

            Filehandler fh;
            if (fh.adminUsernameExists(name)) {
                MessageBox::Show("Username already taken.");
                return;
            }

            std::ifstream countFile("admins.txt");
            int count = 0;
            std::string tempLine;
            while (std::getline(countFile, tempLine)) {
                if (!tempLine.empty()) count++;
            }
            countFile.close();

            std::string adminId = "A" + std::to_string(count + 1);

            std::ofstream out("admins.txt", std::ios::app);
            if (out.is_open()) {
                out << name << "|" << pass << "|" << adminId << "\n";
                out.close();
                MessageBox::Show(gcnew String(("Admin registered with ID: " + adminId).c_str()));
                txtAdminUser->Clear();
                txtAdminPass->Clear();
            }
        }

        System::Void btnLogout_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }
    };
}