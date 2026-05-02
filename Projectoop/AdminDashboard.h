#pragma once
#include "Backend.h"
#include "ViewResult.h"
#include "VotingHistory.h"
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

        System::Void btnSearchCandidates_Click(System::Object^ sender, System::EventArgs^ e) {
            // Use txtCandName as search input; if empty, refresh full list
            String^ q = txtCandName->Text;
            if (String::IsNullOrWhiteSpace(q)) {
                RefreshCandidates();
                return;
            }

            std::string query;
            msclr::interop::marshal_context ctx;
            query = ctx.marshal_as<std::string>(q);

            listCandidates->Items->Clear();
            std::ifstream in("Candidates.txt");
            if (!in.is_open()) {
                listCandidates->Items->Add("No candidates found.");
                return;
            }
            std::string line;
            while (std::getline(in, line)) {
                if (line.empty()) continue;
                // simple substring search across name and id
                if (line.find(query) != std::string::npos) {
                    std::string name, party, cid;
                    std::stringstream ss(line);
                    std::getline(ss, name, '|');
                    std::getline(ss, party, '|');
                    std::getline(ss, cid, '|');
                    String^ displayStr = gcnew String(("ID: " + cid + " | " + name + " (" + party + ")").c_str());
                    listCandidates->Items->Add(displayStr);
                }
            }
            in.close();
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
        System::Windows::Forms::Button^ btnVotingHistory;
        System::Windows::Forms::Button^ btnSearchCandidates;
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
            this->btnVotingHistory = (gcnew System::Windows::Forms::Button());
            this->btnSearchCandidates = (gcnew System::Windows::Forms::Button());
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
            this->ClientSize = System::Drawing::Size(600, 500);
            this->Text = L"Admin Dashboard";
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->BackColor = System::Drawing::Color::Black;
            this->ForeColor = System::Drawing::Color::White;

            // listCandidates
            this->listCandidates->FormattingEnabled = true;
            this->listCandidates->Location = System::Drawing::Point(12, 12);
            this->listCandidates->Size = System::Drawing::Size(250, 400);
            this->listCandidates->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
            this->listCandidates->ForeColor = System::Drawing::Color::White;
            this->listCandidates->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;

            // btnRefreshCandidates
            this->btnRefreshCandidates->Location = System::Drawing::Point(12, 420);
            this->btnRefreshCandidates->Size = System::Drawing::Size(250, 30);
            this->btnRefreshCandidates->Text = L"Refresh Candidates";
            this->btnRefreshCandidates->Click += gcnew System::EventHandler(this, &AdminDashboard::btnRefreshCandidates_Click);
            // Theme: primary green for positive actions
            System::Drawing::Color primaryGreen = System::Drawing::Color::FromArgb(40, 180, 99);
            System::Drawing::Color dangerRed = System::Drawing::Color::FromArgb(231, 76, 60);
            System::Drawing::Color neutralDark = System::Drawing::Color::FromArgb(45, 45, 45);
            this->btnRefreshCandidates->BackColor = primaryGreen;
            this->btnRefreshCandidates->ForeColor = System::Drawing::Color::White;
            this->btnRefreshCandidates->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnRefreshCandidates->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));

            // groupAddCandidate
            this->groupAddCandidate->Location = System::Drawing::Point(280, 12);
            this->groupAddCandidate->Size = System::Drawing::Size(300, 100);
            this->groupAddCandidate->Text = L"Add Candidate";
            this->groupAddCandidate->ForeColor = System::Drawing::Color::White;
            this->groupAddCandidate->BackColor = System::Drawing::Color::Black;

            this->lblCandName->Location = System::Drawing::Point(10, 25);
            this->lblCandName->Size = System::Drawing::Size(50, 20);
            this->lblCandName->Text = L"Name:";
            this->lblCandName->ForeColor = System::Drawing::Color::White;
            this->txtCandName->Location = System::Drawing::Point(60, 22);
            this->txtCandName->Size = System::Drawing::Size(130, 20);
            this->txtCandName->BackColor = System::Drawing::Color::White;
            this->txtCandName->ForeColor = System::Drawing::Color::Black;

            this->lblCandParty->Location = System::Drawing::Point(10, 55);
            this->lblCandParty->Size = System::Drawing::Size(50, 20);
            this->lblCandParty->Text = L"Party:";
            this->lblCandParty->ForeColor = System::Drawing::Color::White;
            this->txtCandParty->Location = System::Drawing::Point(60, 52);
            this->txtCandParty->Size = System::Drawing::Size(130, 20);
            this->txtCandParty->BackColor = System::Drawing::Color::White;
            this->txtCandParty->ForeColor = System::Drawing::Color::Black;

            this->btnAddCandidate->Location = System::Drawing::Point(200, 22);
            this->btnAddCandidate->Size = System::Drawing::Size(80, 50);
            this->btnAddCandidate->Text = L"Add";
            this->btnAddCandidate->Click += gcnew System::EventHandler(this, &AdminDashboard::btnAddCandidate_Click);
            this->btnAddCandidate->BackColor = primaryGreen;
            this->btnAddCandidate->ForeColor = System::Drawing::Color::White;
            this->btnAddCandidate->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnAddCandidate->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));

            this->groupAddCandidate->Controls->Add(this->lblCandName);
            this->groupAddCandidate->Controls->Add(this->txtCandName);
            this->groupAddCandidate->Controls->Add(this->lblCandParty);
            this->groupAddCandidate->Controls->Add(this->txtCandParty);
            this->groupAddCandidate->Controls->Add(this->btnAddCandidate);

            // groupRemoveCandidate
            this->groupRemoveCandidate->Location = System::Drawing::Point(280, 120);
            this->groupRemoveCandidate->Size = System::Drawing::Size(300, 60);
            this->groupRemoveCandidate->Text = L"Remove Candidate";
            this->groupRemoveCandidate->ForeColor = System::Drawing::Color::White;
            this->groupRemoveCandidate->BackColor = System::Drawing::Color::Black;

            this->lblRemoveId->Location = System::Drawing::Point(10, 25);
            this->lblRemoveId->Size = System::Drawing::Size(50, 20);
            this->lblRemoveId->Text = L"ID:";
            this->lblRemoveId->ForeColor = System::Drawing::Color::White;
            this->txtCandIdToRemove->Location = System::Drawing::Point(60, 22);
            this->txtCandIdToRemove->Size = System::Drawing::Size(130, 20);
            this->txtCandIdToRemove->BackColor = System::Drawing::Color::White;
            this->txtCandIdToRemove->ForeColor = System::Drawing::Color::Black;

            this->btnRemoveCandidate->Location = System::Drawing::Point(200, 20);
            this->btnRemoveCandidate->Size = System::Drawing::Size(80, 25);
            this->btnRemoveCandidate->Text = L"Remove";
            this->btnRemoveCandidate->Click += gcnew System::EventHandler(this, &AdminDashboard::btnRemoveCandidate_Click);
            this->btnRemoveCandidate->BackColor = dangerRed;
            this->btnRemoveCandidate->ForeColor = System::Drawing::Color::White;
            this->btnRemoveCandidate->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnRemoveCandidate->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));

            this->groupRemoveCandidate->Controls->Add(this->lblRemoveId);
            this->groupRemoveCandidate->Controls->Add(this->txtCandIdToRemove);
            this->groupRemoveCandidate->Controls->Add(this->btnRemoveCandidate);

            // groupVoter
            this->groupVoter->Location = System::Drawing::Point(280, 190);
            this->groupVoter->Size = System::Drawing::Size(300, 60);
            this->groupVoter->Text = L"Delete Voter";
            this->groupVoter->ForeColor = System::Drawing::Color::White;
            this->groupVoter->BackColor = System::Drawing::Color::Black;

            this->lblVoterUser->Location = System::Drawing::Point(10, 25);
            this->lblVoterUser->Size = System::Drawing::Size(50, 20);
            this->lblVoterUser->Text = L"User:";
            this->lblVoterUser->ForeColor = System::Drawing::Color::White;
            this->txtVoterUsername->Location = System::Drawing::Point(60, 22);
            this->txtVoterUsername->Size = System::Drawing::Size(130, 20);
            this->txtVoterUsername->BackColor = System::Drawing::Color::White;
            this->txtVoterUsername->ForeColor = System::Drawing::Color::Black;

            this->btnDeleteVoter->Location = System::Drawing::Point(200, 20);
            this->btnDeleteVoter->Size = System::Drawing::Size(80, 25);
            this->btnDeleteVoter->Text = L"Delete";
            this->btnDeleteVoter->Click += gcnew System::EventHandler(this, &AdminDashboard::btnDeleteVoter_Click);
            this->btnDeleteVoter->BackColor = dangerRed;
            this->btnDeleteVoter->ForeColor = System::Drawing::Color::White;
            this->btnDeleteVoter->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnDeleteVoter->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));

            this->groupVoter->Controls->Add(this->lblVoterUser);
            this->groupVoter->Controls->Add(this->txtVoterUsername);
            this->groupVoter->Controls->Add(this->btnDeleteVoter);

            // groupSystem
            this->groupSystem->Location = System::Drawing::Point(280, 260);
            this->groupSystem->Size = System::Drawing::Size(300, 80); // increased height
            this->groupSystem->Text = L"System Operations";
            this->groupSystem->ForeColor = System::Drawing::Color::White;
            this->groupSystem->BackColor = System::Drawing::Color::Black;

            this->btnViewResults->Location = System::Drawing::Point(10, 20);
            this->btnViewResults->Size = System::Drawing::Size(135, 23);
            this->btnViewResults->Text = L"View Election Results";
            this->btnViewResults->Click += gcnew System::EventHandler(this, &AdminDashboard::btnViewResults_Click);
            this->btnViewResults->BackColor = primaryGreen;
            this->btnViewResults->ForeColor = System::Drawing::Color::White;
            this->btnViewResults->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnViewResults->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));

            this->btnResetElection->Location = System::Drawing::Point(155, 20);
            this->btnResetElection->Size = System::Drawing::Size(135, 23);
            this->btnResetElection->Text = L"Reset Election Data";
            this->btnResetElection->Click += gcnew System::EventHandler(this, &AdminDashboard::btnResetElection_Click);
            this->btnResetElection->BackColor = dangerRed;
            this->btnResetElection->ForeColor = System::Drawing::Color::White;
            this->btnResetElection->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnResetElection->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));

            this->btnVotingHistory->Location = System::Drawing::Point(10, 50);
            this->btnVotingHistory->Size = System::Drawing::Size(135, 23);
            this->btnVotingHistory->Text = L"Voting History";
            this->btnVotingHistory->Click += gcnew System::EventHandler(this, &AdminDashboard::btnVotingHistory_Click);

            this->btnSearchCandidates->Location = System::Drawing::Point(155, 50);
            this->btnSearchCandidates->Size = System::Drawing::Size(135, 23);
            this->btnSearchCandidates->Text = L"Search Candidates";
            this->btnSearchCandidates->Click += gcnew System::EventHandler(this, &AdminDashboard::btnSearchCandidates_Click);

            this->groupSystem->Controls->Add(this->btnViewResults);
            this->groupSystem->Controls->Add(this->btnResetElection);
            this->groupSystem->Controls->Add(this->btnVotingHistory);
            this->groupSystem->Controls->Add(this->btnSearchCandidates);

            // groupAdmin
            this->groupAdmin->Location = System::Drawing::Point(280, 350);
            this->groupAdmin->Size = System::Drawing::Size(300, 100);
            this->groupAdmin->Text = L"Register New Admin";
            this->groupAdmin->ForeColor = System::Drawing::Color::White;
            this->groupAdmin->BackColor = System::Drawing::Color::Black;

            this->lblAdminUser->Location = System::Drawing::Point(10, 25);
            this->lblAdminUser->Size = System::Drawing::Size(50, 20);
            this->lblAdminUser->Text = L"User:";
            this->lblAdminUser->ForeColor = System::Drawing::Color::White;
            this->txtAdminUser->Location = System::Drawing::Point(60, 22);
            this->txtAdminUser->Size = System::Drawing::Size(130, 20);
            this->txtAdminUser->BackColor = System::Drawing::Color::White;
            this->txtAdminUser->ForeColor = System::Drawing::Color::Black;

            this->lblAdminPass->Location = System::Drawing::Point(10, 55);
            this->lblAdminPass->Size = System::Drawing::Size(50, 20);
            this->lblAdminPass->Text = L"Pass:";
            this->lblAdminPass->ForeColor = System::Drawing::Color::White;
            this->txtAdminPass->Location = System::Drawing::Point(60, 52);
            this->txtAdminPass->Size = System::Drawing::Size(130, 20);
            this->txtAdminPass->BackColor = System::Drawing::Color::White;
            this->txtAdminPass->ForeColor = System::Drawing::Color::Black;

            this->btnRegAdmin->Location = System::Drawing::Point(200, 22);
            this->btnRegAdmin->Size = System::Drawing::Size(80, 50);
            this->btnRegAdmin->Text = L"Register";
            this->btnRegAdmin->Click += gcnew System::EventHandler(this, &AdminDashboard::btnRegAdmin_Click);
            this->btnRegAdmin->BackColor = primaryGreen;
            this->btnRegAdmin->ForeColor = System::Drawing::Color::White;
            this->btnRegAdmin->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnRegAdmin->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));

            this->groupAdmin->Controls->Add(this->lblAdminUser);
            this->groupAdmin->Controls->Add(this->txtAdminUser);
            this->groupAdmin->Controls->Add(this->lblAdminPass);
            this->groupAdmin->Controls->Add(this->txtAdminPass);
            this->groupAdmin->Controls->Add(this->btnRegAdmin);

            // btnLogout
            this->btnLogout->Location = System::Drawing::Point(280, 460);
            this->btnLogout->Size = System::Drawing::Size(300, 30);
            this->btnLogout->Text = L"Logout";
            this->btnLogout->Click += gcnew System::EventHandler(this, &AdminDashboard::btnLogout_Click);
            this->btnLogout->BackColor = primaryGreen;
            this->btnLogout->ForeColor = System::Drawing::Color::White;
            this->btnLogout->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnLogout->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));

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
            std::ifstream candidates("Candidates.txt");
            int total = 0, voted = 0;
            if (candidates.is_open()) {
                std::string line;
                while (std::getline(candidates, line)) {
                    if (!line.empty()) total++;
                }
                candidates.close();
            }

            std::ifstream votes("Votes.txt");
            if (votes.is_open()) {
                std::string line;
                while (std::getline(votes, line)) {
                    if (!line.empty()) voted++;
                }
                votes.close();
            }

            ViewResult^ vr = gcnew ViewResult(total, voted);
            vr->ShowDialog();
        }

            int total = 0;
            int voted = 0;
            std::string line;
            while (std::getline(voters, line)) {
                if (line.empty()) continue;
                total++;
                // parse fields: name|pass|id|votedFlag|
                std::stringstream ss(line);
                std::string f_name, f_pass, f_id, f_voted;
                std::getline(ss, f_name, '|');
                std::getline(ss, f_pass, '|');
                std::getline(ss, f_id, '|');
                std::getline(ss, f_voted, '|');
                if (f_voted == "1") voted++;
            }
            voters.close();

        System::Void btnSearchCandidates_Click(System::Object^ sender, System::EventArgs^ e) {
            MessageBox::Show("Search functionality coming soon.", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        // Show voting history by reading votes.txt into a dialog
        System::Void btnVotingHistory_Click(System::Object^ sender, System::EventArgs^ e) {
            // Read votes
            std::ifstream vin("votes.txt");
            System::Windows::Forms::Form^ dlg = gcnew System::Windows::Forms::Form();
            dlg->Text = L"Voting History";
            dlg->ClientSize = System::Drawing::Size(480, 360);
            dlg->StartPosition = FormStartPosition::CenterParent;
            System::Windows::Forms::ListBox^ lb = (gcnew System::Windows::Forms::ListBox());
            lb->Location = System::Drawing::Point(8, 8);
            lb->Size = System::Drawing::Size(464, 300);
            lb->BackColor = System::Drawing::Color::FromArgb(30,30,30);
            lb->ForeColor = System::Drawing::Color::White;
            dlg->Controls->Add(lb);
            System::Windows::Forms::Button^ btnClose = (gcnew System::Windows::Forms::Button());
            btnClose->Text = L"Close";
            btnClose->Location = System::Drawing::Point(200, 320);
            btnClose->DialogResult = System::Windows::Forms::DialogResult::OK;
            dlg->Controls->Add(btnClose);

            if (vin.is_open()) {
                std::string vline;
                while (std::getline(vin, vline)) {
                    if (vline.empty()) continue;
                    // Format: voterID|candidateId|timestamp
                    std::stringstream ss(vline);
                    std::string vid, cid, ts;
                    std::getline(ss, vid, '|');
                    std::getline(ss, cid, '|');
                    std::getline(ss, ts, '|');
                    std::string display = vid + " -> " + cid + " @ " + ts;
                    lb->Items->Add(gcnew String(display.c_str()));
                }
                vin.close();
            }
            else {
                lb->Items->Add("No voting history found.");
            }

            dlg->ShowDialog();
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