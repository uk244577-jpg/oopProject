#pragma once
#include "Backend.h"
#include "CandidateSearch.h"
#include <msclr\marshal_cppstd.h>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <map>
#include <vector>
#include <algorithm>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace Projectoop {

    public ref class VoterDashboard : public System::Windows::Forms::Form
    {
    private:
        String^ voterId;
        bool hasVoted;
        System::Windows::Forms::ListBox^ lstCandidates;
        System::Windows::Forms::Button^ btnVote;
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Label^ lblStatus;
        System::Windows::Forms::Button^ btnRefresh;
        System::Windows::Forms::Button^ btnOpenSlip;
        System::Windows::Forms::Button^ btnShowResults;
        System::ComponentModel::Container^ components;

    public:
        VoterDashboard(String^ vId, bool voted)
        {
            InitializeComponent();
            this->voterId = vId;
            this->hasVoted = voted;
            lblStatus->Text = hasVoted ? "Status: Already voted" : "Status: Not voted yet";
            LoadCandidates();
        }

    protected:
        ~VoterDashboard()
        {
            if (components)
            {
                delete components;
            }
        }

        void InitializeComponent(void)
        {
            this->lstCandidates = (gcnew System::Windows::Forms::ListBox());
            this->btnVote = (gcnew System::Windows::Forms::Button());
            this->lblTitle = (gcnew System::Windows::Forms::Label());
            this->lblStatus = (gcnew System::Windows::Forms::Label());
            this->btnRefresh = (gcnew System::Windows::Forms::Button());
            this->btnOpenSlip = (gcnew System::Windows::Forms::Button());
            this->btnShowResults = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();
            // 
            // lblTitle
            // 
            this->lblTitle->AutoSize = true;
            this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
            this->lblTitle->Location = System::Drawing::Point(16, 16);
            this->lblTitle->Size = System::Drawing::Size(220, 30);
            this->lblTitle->Text = L"Cast Your Vote";
            // 
            // lblStatus
            // 
            this->lblStatus->AutoSize = true;
            this->lblStatus->Location = System::Drawing::Point(260, 24);
            this->lblStatus->Size = System::Drawing::Size(180, 20);
            this->lblStatus->Text = L"Status: Unknown";
            // 
            // lstCandidates
            // 
            this->lstCandidates->FormattingEnabled = true;
            this->lstCandidates->Location = System::Drawing::Point(16, 64);
            this->lstCandidates->Size = System::Drawing::Size(420, 220);
            this->lstCandidates->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
            // 
            // btnVote
            // 
            this->btnVote->Location = System::Drawing::Point(16, 300);
            this->btnVote->Size = System::Drawing::Size(120, 36);
            this->btnVote->Text = L"Vote";
            this->btnVote->Click += gcnew System::EventHandler(this, &VoterDashboard::btnVote_Click);
            // 
            // btnRefresh
            // 
            this->btnRefresh->Location = System::Drawing::Point(152, 300);
            this->btnRefresh->Size = System::Drawing::Size(120, 36);
            this->btnRefresh->Text = L"Refresh";
            this->btnRefresh->Click += gcnew System::EventHandler(this, &VoterDashboard::btnRefresh_Click);
            // 
            // btnOpenSlip
            // 
            this->btnOpenSlip->Location = System::Drawing::Point(288, 300);
            this->btnOpenSlip->Size = System::Drawing::Size(120, 36);
            this->btnOpenSlip->Text = L"My Receipt";
            this->btnOpenSlip->Click += gcnew System::EventHandler(this, &VoterDashboard::btnOpenSlip_Click);
            // 
            // btnShowResults
            // 
            this->btnShowResults->Location = System::Drawing::Point(416, 300);
            this->btnShowResults->Size = System::Drawing::Size(140, 36);
            this->btnShowResults->Text = L"Show Results";
            this->btnShowResults->Click += gcnew System::EventHandler(this, &VoterDashboard::btnShowResults_Click);
            // 
            // VoterDashboard
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(570, 352);
            this->Controls->Add(this->btnShowResults);
            this->Controls->Add(this->btnOpenSlip);
            this->Controls->Add(this->btnRefresh);
            this->Controls->Add(this->lblStatus);
            this->Controls->Add(this->lblTitle);
            this->Controls->Add(this->btnVote);
            this->Controls->Add(this->lstCandidates);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"VoterDashboard";
            this->StartPosition = FormStartPosition::CenterParent;
            this->Text = L"Voter Dashboard";
            this->ResumeLayout(false);
            this->PerformLayout();
            // Apply black & white theme
            this->BackColor = System::Drawing::Color::Black;
            this->ForeColor = System::Drawing::Color::White;

            // Title styling
            this->lblTitle->ForeColor = System::Drawing::Color::White;
            this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold));

            this->lblStatus->ForeColor = System::Drawing::Color::White;

            // List box: dark background, white text for black/green/red theme
            this->lstCandidates->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
            this->lstCandidates->ForeColor = System::Drawing::Color::White;
            this->lstCandidates->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;

            // Buttons: primary actions = green, destructive actions = red
            System::Drawing::Color primaryGreen = System::Drawing::Color::FromArgb(40, 180, 99);
            System::Drawing::Color dangerRed = System::Drawing::Color::FromArgb(231, 76, 60);
            System::Drawing::Color neutralDark = System::Drawing::Color::FromArgb(45, 45, 45);

            this->btnVote->BackColor = primaryGreen;
            this->btnVote->ForeColor = System::Drawing::Color::White;
            this->btnVote->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnVote->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));

            this->btnRefresh->BackColor = primaryGreen;
            this->btnRefresh->ForeColor = System::Drawing::Color::White;
            this->btnRefresh->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnRefresh->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));

            this->btnOpenSlip->BackColor = neutralDark;
            this->btnOpenSlip->ForeColor = System::Drawing::Color::White;
            this->btnOpenSlip->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnOpenSlip->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));

            this->btnShowResults->BackColor = System::Drawing::Color::FromArgb(52, 152, 219);
            this->btnShowResults->ForeColor = System::Drawing::Color::White;
            this->btnShowResults->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnShowResults->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
        }

        void LoadCandidates() {
            lstCandidates->Items->Clear();
            std::ifstream in("Candidates.txt");
            if (!in.is_open()) {
                lstCandidates->Items->Add("No candidates found.");
                return;
            }
            std::string line;
            while (std::getline(in, line)) {
                if (line.empty()) continue;
                std::string name, party, cid;
                std::stringstream ss(line);
                std::getline(ss, name, '|');
                std::getline(ss, party, '|');
                std::getline(ss, cid, '|');
                // store as CID|Name|Party so we can parse later
                std::string store = cid + "|" + name + "|" + party;
                String^ disp = gcnew String(store.c_str());
                lstCandidates->Items->Add(disp);
            }
            in.close();
        }

        System::Void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e) {
            LoadCandidates();
        }

        System::Void btnVote_Click(System::Object^ sender, System::EventArgs^ e) {
            if (hasVoted) {
                MessageBox::Show("You have already voted.", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
                return;
            }
            if (lstCandidates->SelectedIndex < 0) {
                MessageBox::Show("Please select a candidate to vote for.", "Choose Candidate", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            String^ sel = safe_cast<String^>(lstCandidates->SelectedItem);
            cli::array<String^>^ parts = sel->Split('|');
            if (parts->Length < 1) return;
            String^ candidateId = parts[0];

            // confirm
            if (MessageBox::Show(String::Format("Confirm vote for {0}?", sel), "Confirm Vote", MessageBoxButtons::YesNo, MessageBoxIcon::Question) != System::Windows::Forms::DialogResult::Yes) {
                return;
            }

            // call backend
            msclr::interop::marshal_context ctx;
            std::string nativeVoterId = ctx.marshal_as<std::string>(voterId);
            std::string nativeCandidateId = ctx.marshal_as<std::string>(candidateId);
            Filehandler fh;
            if (fh.markVoted(nativeVoterId, nativeCandidateId)) {
                hasVoted = true;
                lblStatus->Text = "Status: Already voted";
                MessageBox::Show("Your vote has been recorded. A receipt was generated.", "Thank You", MessageBoxButtons::OK, MessageBoxIcon::Information);
                // offer to open slip
                String^ slipPath = "slip_" + voterId + ".txt";
                try {
                    System::Diagnostics::Process::Start(slipPath);
                }
                catch (...) {
                    // ignore if cannot open
                }
            }
            else {
                MessageBox::Show("Failed to record vote. Try again.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        System::Void btnOpenSlip_Click(System::Object^ sender, System::EventArgs^ e) {
            String^ slipPath = "slip_" + voterId + ".txt";
            try {
                System::Diagnostics::Process::Start(slipPath);
            }
            catch (...) {
                MessageBox::Show("Receipt not found.", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }

        System::Void btnShowResults_Click(System::Object^ sender, System::EventArgs^ e) {
            try {
                // Count total registered voters
                int totalVoters = 0;
                std::ifstream vfile("voter.txt");
                if (vfile.is_open()) {
                    std::string line;
                    while (std::getline(vfile, line)) {
                        if (!line.empty()) totalVoters++;
                    }
                    vfile.close();
                }

                // Count votes cast
                int votesCast = 0;
                std::map<std::string, int> voteCount;
                std::map<std::string, std::string> candidateNames;

                std::ifstream cfile("Candidates.txt");
                if (cfile.is_open()) {
                    std::string line;
                    while (std::getline(cfile, line)) {
                        if (line.empty()) continue;
                        std::string name, party, cid;
                        std::stringstream ss(line);
                        std::getline(ss, name, '|');
                        std::getline(ss, party, '|');
                        std::getline(ss, cid, '|');
                        candidateNames[cid] = name + " (" + party + ")";
                    }
                    cfile.close();
                }

                std::ifstream votesfile("votes.txt");
                if (votesfile.is_open()) {
                    std::string line;
                    while (std::getline(votesfile, line)) {
                        if (line.empty()) continue;
                        std::string vid, cid, ts;
                        std::stringstream ss(line);
                        std::getline(ss, vid, '|');
                        std::getline(ss, cid, '|');
                        std::getline(ss, ts, '|');
                        if (!cid.empty()) {
                            voteCount[cid]++;
                            votesCast++;
                        }
                    }
                    votesfile.close();
                }

                // Create results message
                String^ resultsText = "";
                resultsText += "========== CURRENT VOTING RESULTS ==========\n\n";
                resultsText += String::Format("Total Registered Voters: {0}\n", totalVoters);
                resultsText += String::Format("Votes Cast So Far: {0}\n", votesCast);
                int yetToVote = totalVoters - votesCast;
                resultsText += String::Format("Yet to Vote: {0}\n", yetToVote);
                if (totalVoters > 0) {
                    int percent = (votesCast * 100) / totalVoters;
                    resultsText += String::Format("Turnout: {0}%\n", percent);
                }
                resultsText += "\n========== CANDIDATE VOTE COUNT ==========\n\n";

                // Sort candidates by vote count (descending)
                std::vector<std::pair<std::string, int>> sortedVotes;
                for (auto& p : candidateNames) {
                    int count = 0;
                    auto it = voteCount.find(p.first);
                    if (it != voteCount.end()) count = it->second;
                    sortedVotes.push_back({p.second, count});
                }
                // Manual bubble sort for descending order
                for (size_t i = 0; i < sortedVotes.size(); i++) {
                    for (size_t j = i + 1; j < sortedVotes.size(); j++) {
                        if (sortedVotes[j].second > sortedVotes[i].second) {
                            std::swap(sortedVotes[i], sortedVotes[j]);
                        }
                    }
                }

                for (auto& p : sortedVotes) {
                    resultsText += String::Format("{0}: {1} vote(s)\n", gcnew String(p.first.c_str()), p.second);
                }

                // Find leading candidate
                if (!sortedVotes.empty() && sortedVotes[0].second > 0) {
                    resultsText += "\n========== LEADING CANDIDATE ==========\n\n";
                    resultsText += String::Format("Leading: {0} with {1} vote(s)\n", 
                        gcnew String(sortedVotes[0].first.c_str()), sortedVotes[0].second);
                } else {
                    resultsText += "\n========== NO VOTES YET ==========\n\n";
                    resultsText += "No votes have been cast so far.\n";
                }

                resultsText += "\n===========================================";

                // Show results in a message box
                MessageBox::Show(resultsText, "Current Voting Results", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            catch (System::Exception^ ex) {
                MessageBox::Show("Error displaying results: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        System::Void btnLogout_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }
    };
}