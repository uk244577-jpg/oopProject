#pragma once
#pragma once
#include "UITheme.h"
#include <msclr/marshal_cppstd.h>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

struct CandData {
    std::string name;
    std::string party;
    int votes;
};

namespace Projectoop {

    public ref class ElectionResults : public System::Windows::Forms::Form
    {
    private:
        System::Windows::Forms::ListView^ listResults;
        System::Windows::Forms::ColumnHeader^ colCand;
        System::Windows::Forms::ColumnHeader^ colVotes;
        System::Windows::Forms::ColumnHeader^ colPercent;
        System::Windows::Forms::Label^ lblWinner;
        System::Windows::Forms::Button^ btnRefresh;

        System::ComponentModel::Container^ components;

    public:
        ElectionResults(void)
        {
            InitializeComponent();
            UITheme::ApplyTheme(this);
        }

    protected:
        ~ElectionResults()
        {
            if (components) delete components;
        }

    private:
        void InitializeComponent(void)
        {
            this->listResults = (gcnew System::Windows::Forms::ListView());
            this->colCand = (gcnew System::Windows::Forms::ColumnHeader());
            this->colVotes = (gcnew System::Windows::Forms::ColumnHeader());
            this->colPercent = (gcnew System::Windows::Forms::ColumnHeader());
            this->lblWinner = (gcnew System::Windows::Forms::Label());
            this->btnRefresh = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();

            this->ClientSize = System::Drawing::Size(420, 350);
            this->Text = L"Election Results";
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;

            this->lblWinner->Location = System::Drawing::Point(15, 15);
            this->lblWinner->Size = System::Drawing::Size(380, 25);
            this->lblWinner->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.0F, System::Drawing::FontStyle::Bold));
            this->lblWinner->ForeColor = System::Drawing::Color::Green;

            this->listResults->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^ >(3) {
                this->colCand, this->colVotes, this->colPercent
            });
            this->listResults->Location = System::Drawing::Point(15, 50);
            this->listResults->Size = System::Drawing::Size(380, 240);
            this->listResults->View = System::Windows::Forms::View::Details;
            this->listResults->FullRowSelect = true;
            this->listResults->GridLines = true;

            this->colCand->Text = L"Candidate / Party";
            this->colCand->Width = 180;
            this->colVotes->Text = L"Total Votes";
            this->colVotes->Width = 80;
            this->colPercent->Text = L"Percentage";
            this->colPercent->Width = 100;

            this->btnRefresh->Location = System::Drawing::Point(160, 305);
            this->btnRefresh->Size = System::Drawing::Size(100, 30);
            this->btnRefresh->Text = L"Refresh Results";
            this->btnRefresh->Click += gcnew System::EventHandler(this, &ElectionResults::btnRefresh_Click);

            this->Controls->Add(this->listResults);
            this->Controls->Add(this->lblWinner);
            this->Controls->Add(this->btnRefresh);

            this->Load += gcnew System::EventHandler(this, &ElectionResults::ElectionResults_Load);
            this->ResumeLayout(false);
            this->PerformLayout();
        }

        System::Void ElectionResults_Load(System::Object^ sender, System::EventArgs^ e) {
            CalculateResults();
        }

        System::Void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e) {
            CalculateResults();
        }

        void CalculateResults() {
            listResults->Items->Clear();

            std::map<std::string, CandData> candidates;

            // Load Candidates
            std::ifstream candIn("Candidates.txt");
            std::string line;
            if (candIn.is_open()) {
                while (std::getline(candIn, line)) {
                    if (line.empty()) continue;
                    std::stringstream ss(line);
                    std::string n, p, c;
                    std::getline(ss, n, '|');
                    std::getline(ss, p, '|');
                    std::getline(ss, c, '|');
                    // Remove possible trailing carriage returns
                    if (!c.empty() && c.back() == '\r') c.pop_back();

                    candidates[c] = { n, p, 0 };
                }
                candIn.close();
            }

            // Tally Votes
            int totalVotes = 0;
            std::ifstream voteIn("Votes.txt");
            if (voteIn.is_open()) {
                while (std::getline(voteIn, line)) {
                    if (line.empty()) continue;
                    std::stringstream ss(line);
                    std::string vid, cid, dt;
                    std::getline(ss, vid, '|');
                    std::getline(ss, cid, '|');
                    std::getline(ss, dt, '|');

                    // If candidate exists in registry
                    if (candidates.find(cid) != candidates.end()) {
                        candidates[cid].votes++;
                        totalVotes++;
                    }
                }
                voteIn.close();
            }

            if (totalVotes == 0) {
                lblWinner->Text = L"No votes have been cast yet.";
            }

            int maxVotes = -1;
            std::string winnerName = "";
            bool tie = false;

            // Populate view
            for (auto const& pair : candidates) {
                CandData cd = pair.second;
                double percent = (totalVotes > 0) ? ((double)cd.votes / totalVotes) * 100.0 : 0.0;

                String^ viewCand = gcnew String((cd.name + " (" + cd.party + ")").c_str());
                String^ viewVotes = cd.votes.ToString();
                String^ viewPercent = percent.ToString("0.00") + "%";

                ListViewItem^ item = gcnew ListViewItem(viewCand);
                item->SubItems->Add(viewVotes);
                item->SubItems->Add(viewPercent);
                listResults->Items->Add(item);

                if (cd.votes > maxVotes) {
                    maxVotes = cd.votes;
                    winnerName = cd.name + " (" + cd.party + ")";
                    tie = false;
                } else if (cd.votes == maxVotes && maxVotes > 0) {
                    tie = true;
                }
            }

            if (totalVotes > 0) {
                if (tie) {
                    lblWinner->Text = L"Current Status: TIE between top candidates.";
                    lblWinner->ForeColor = System::Drawing::Color::Orange;
                } else {
                    lblWinner->Text = L"Current Winner: " + gcnew String(winnerName.c_str()) + " (" + maxVotes + " Vote(s))";
                    lblWinner->ForeColor = System::Drawing::Color::Green;
                }
            }
        }
    };
}