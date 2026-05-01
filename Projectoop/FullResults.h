#pragma once
// FullResults.h
// Automatic Vote Counting + Results Display + Winner Declaration
// Features 9 & 10 for Part 4

#pragma once
#include "Backend.h"
#include "VoteTracker.h"
#include <msclr\marshal_cppstd.h>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace Projectoop {

    public ref class FullResults : public System::Windows::Forms::Form
    {
    public:
        FullResults(void)
        {
            InitializeComponent();
            LoadResults();
        }

    protected:
        ~FullResults()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::ListView^ listViewResults;
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Label^ lblWinner;
        System::Windows::Forms::Button^ btnRefresh;
        System::Windows::Forms::Button^ btnClose;
        System::Windows::Forms::ColumnHeader^ colCandidate;
        System::Windows::Forms::ColumnHeader^ colParty;
        System::Windows::Forms::ColumnHeader^ colVotes;
        System::Windows::Forms::ColumnHeader^ colPercentage;

        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->listViewResults = (gcnew System::Windows::Forms::ListView());
            this->lblTitle = (gcnew System::Windows::Forms::Label());
            this->lblWinner = (gcnew System::Windows::Forms::Label());
            this->btnRefresh = (gcnew System::Windows::Forms::Button());
            this->btnClose = (gcnew System::Windows::Forms::Button());
            this->colCandidate = (gcnew System::Windows::Forms::ColumnHeader());
            this->colParty = (gcnew System::Windows::Forms::ColumnHeader());
            this->colVotes = (gcnew System::Windows::Forms::ColumnHeader());
            this->colPercentage = (gcnew System::Windows::Forms::ColumnHeader());
            this->SuspendLayout();

            // Form settings
            this->ClientSize = System::Drawing::Size(550, 450);
            this->Text = L"Election Results - Vote Counting & Winner";
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->StartPosition = FormStartPosition::CenterScreen;

            // Title Label
            this->lblTitle->Location = System::Drawing::Point(20, 10);
            this->lblTitle->Size = System::Drawing::Size(500, 25);
            this->lblTitle->Font = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
            this->lblTitle->TextAlign = ContentAlignment::MiddleCenter;
            this->lblTitle->Text = L"?????? ELECTION RESULTS ??????";

            // ListView for results
            this->listViewResults->Location = System::Drawing::Point(20, 50);
            this->listViewResults->Size = System::Drawing::Size(510, 300);
            this->listViewResults->View = System::Windows::Forms::View::Details;
            this->listViewResults->FullRowSelect = true;
            this->listViewResults->GridLines = true;

            this->colCandidate->Text = L"Candidate Name";
            this->colCandidate->Width = 150;
            this->colParty->Text = L"Party";
            this->colParty->Width = 120;
            this->colVotes->Text = L"Votes Received";
            this->colVotes->Width = 120;
            this->colPercentage->Text = L"Percentage";
            this->colPercentage->Width = 100;

            this->listViewResults->Columns->AddRange(gcnew cli::array<System::Windows::Forms::ColumnHeader^>(4) {
                this->colCandidate, this->colParty, this->colVotes, this->colPercentage
            });

            // Winner Label
            this->lblWinner->Location = System::Drawing::Point(20, 360);
            this->lblWinner->Size = System::Drawing::Size(510, 40);
            this->lblWinner->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
            this->lblWinner->TextAlign = ContentAlignment::MiddleCenter;
            this->lblWinner->BackColor = System::Drawing::Color::LightYellow;
            this->lblWinner->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;

            // Refresh Button
            this->btnRefresh->Location = System::Drawing::Point(150, 410);
            this->btnRefresh->Size = System::Drawing::Size(120, 30);
            this->btnRefresh->Text = L"Refresh Results";
            this->btnRefresh->Click += gcnew System::EventHandler(this, &FullResults::btnRefresh_Click);

            // Close Button
            this->btnClose->Location = System::Drawing::Point(290, 410);
            this->btnClose->Size = System::Drawing::Size(120, 30);
            this->btnClose->Text = L"Close";
            this->btnClose->Click += gcnew System::EventHandler(this, &FullResults::btnClose_Click);

            // Add controls to form
            this->Controls->Add(this->lblTitle);
            this->Controls->Add(this->listViewResults);
            this->Controls->Add(this->lblWinner);
            this->Controls->Add(this->btnRefresh);
            this->Controls->Add(this->btnClose);

            this->ResumeLayout(false);
        }

        void LoadResults() {
            listViewResults->Items->Clear();

            // Get all candidates from file
            std::ifstream in("Candidates.txt");
            if (!in.is_open()) {
                lblWinner->Text = L"? No candidates found. Please add candidates first.";
                return;
            }

            // Store candidate info
            std::vector<std::tuple<std::string, std::string, std::string>> candidates;
            std::string line;
            while (std::getline(in, line)) {
                if (line.empty()) continue;
                std::string name, party, cid;
                std::stringstream ss(line);
                std::getline(ss, name, '|');
                std::getline(ss, party, '|');
                std::getline(ss, cid, '|');
                candidates.push_back({ name, party, cid });
            }
            in.close();

            if (candidates.empty()) {
                lblWinner->Text = L"? No candidates registered.";
                return;
            }

            // Get total votes
            int totalVotes = VoteTracker::getTotalVotes();
            int maxVotes = -1;
            std::string winnerName;
            std::string winnerParty;
            std::string winnerId;

            // Display each candidate's votes
            for (const auto& cand : candidates) {
                std::string name = std::get<0>(cand);
                std::string party = std::get<1>(cand);
                std::string cid = std::get<2>(cand);

                int votes = VoteTracker::getVoteCountForCandidate(cid);
                double percentage = (totalVotes > 0) ? (votes * 100.0 / totalVotes) : 0.0;

                // Track winner
                if (votes > maxVotes) {
                    maxVotes = votes;
                    winnerName = name;
                    winnerParty = party;
                    winnerId = cid;
                }

                // Add to ListView
                ListViewItem^ item = gcnew ListViewItem(gcnew String(name.c_str()));
                item->SubItems->Add(gcnew String(party.c_str()));
                item->SubItems->Add(votes.ToString());
                item->SubItems->Add(String::Format("{0:F1}%", percentage));
                listViewResults->Items->Add(item);
            }

            // Declare Winner
            if (totalVotes == 0) {
                lblWinner->Text = L"? No votes have been cast yet.";
                lblWinner->BackColor = System::Drawing::Color::LightGray;
            }
            else if (maxVotes == 0) {
                lblWinner->Text = L"? No votes cast. Waiting for votes...";
                lblWinner->BackColor = System::Drawing::Color::LightYellow;
            }
            else {
                lblWinner->Text = String::Format("?? WINNER DECLARED: {0} ({1}) with {2} votes ??",
                    gcnew String(winnerName.c_str()),
                    gcnew String(winnerParty.c_str()),
                    maxVotes.ToString());
                lblWinner->BackColor = System::Drawing::Color::LightGreen;
                lblWinner->ForeColor = System::Drawing::Color::DarkGreen;
            }

            // Add summary at bottom of ListView (as a special item)
            ListViewItem^ summaryItem = gcnew ListViewItem(L"??????????????");
            summaryItem->SubItems->Add(L"?????????");
            summaryItem->SubItems->Add(L"?????????");
            summaryItem->SubItems->Add(L"?????????");
            listViewResults->Items->Add(summaryItem);

            ListViewItem^ totalItem = gcnew ListViewItem(L"TOTAL");
            totalItem->SubItems->Add(L"");
            totalItem->SubItems->Add(totalVotes.ToString());
            totalItem->SubItems->Add(L"100%");
            totalItem->Font = gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold);
            listViewResults->Items->Add(totalItem);
        }

        System::Void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e) {
            LoadResults();
        }

        System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }
    };
}