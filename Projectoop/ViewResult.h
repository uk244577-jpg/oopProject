// ViewResult.h - simple form to display election turnout
#pragma once

#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

// comparator for sorting pairs by count descending
static bool __cdecl vr_compare_desc(const std::pair<std::string,int>& a, const std::pair<std::string,int>& b) {
    return a.second > b.second;
}

namespace Projectoop {

    public ref class ViewResult : public System::Windows::Forms::Form
    {
    public:
        ViewResult(int total, int voted)
        {
            InitializeComponent();
            int yet = total - voted;
            int percent = total > 0 ? (voted * 100) / total : 0;

            this->lblTotal->Text = String::Format("Total Registered: {0}", total);
            this->lblVoted->Text = String::Format("Votes Cast: {0}", voted);
            this->lblYet->Text = String::Format("Yet to Vote: {0}", yet);
            this->lblPercent->Text = String::Format("Turnout: {0}%", percent);

            // Populate per-candidate results and determine winner
            try {
                // read candidate file: ID is third field
                std::map<std::string, std::string> candidateNames; // id -> name
                std::ifstream cinf("Candidates.txt");
                if (cinf.is_open()) {
                    std::string line;
                    while (std::getline(cinf, line)) {
                        if (line.empty()) continue;
                        std::string name, party, cid;
                        std::stringstream ss(line);
                        std::getline(ss, name, '|');
                        std::getline(ss, party, '|');
                        std::getline(ss, cid, '|');
                        candidateNames[cid] = name;
                    }
                    cinf.close();
                }

                // tally votes from votes.txt (format: voterID|candidateId|timestamp)
                std::map<std::string, int> counts; // candidateId -> count
                std::ifstream vinf("votes.txt");
                if (vinf.is_open()) {
                    std::string vline;
                    while (std::getline(vinf, vline)) {
                        if (vline.empty()) continue;
                        std::string vid, cid, ts;
                        std::stringstream ss(vline);
                        std::getline(ss, vid, '|');
                        std::getline(ss, cid, '|');
                        std::getline(ss, ts, '|');
                        if (!cid.empty()) counts[cid]++;
                    }
                    vinf.close();
                }

                // create sortable list of (candidateId, count)
                std::vector<std::pair<std::string,int>> list;
                for (auto &p : candidateNames) {
                    int c = 0;
                    auto it = counts.find(p.first);
                    if (it != counts.end()) c = it->second;
                    list.push_back({p.first, c});
                }
                // include any candidate ids present in votes but missing from Candidates.txt
                for (auto &p : counts) {
                    if (candidateNames.find(p.first) == candidateNames.end()) {
                        list.push_back({p.first, p.second});
                    }
                }

                std::sort(list.begin(), list.end(), vr_compare_desc);

                int bestCount = -1;
                std::string bestId = "";
                for (auto &pr : list) {
                    std::string id = pr.first;
                    int cnt = pr.second;
                    std::string name = "(Unknown)";
                    auto itn = candidateNames.find(id);
                    if (itn != candidateNames.end()) name = itn->second;
                    std::string display = name + " (" + id + ") : " + std::to_string(cnt) + " votes";
                    this->lstCandidateResults->Items->Add(gcnew String(display.c_str()));
                    if (cnt > bestCount) { bestCount = cnt; bestId = id; }
                }

                if (bestCount <= 0) {
                    this->lblWinner->Text = L"Winner: (no votes yet)";
                    this->lblWinner->ForeColor = System::Drawing::Color::White;
                }
                else {
                    std::string bestName = "(Unknown)";
                    auto itb = candidateNames.find(bestId);
                    if (itb != candidateNames.end()) bestName = itb->second;
                    std::string wstr = "Winner: " + bestName + " (" + bestId + ") - " + std::to_string(bestCount) + " votes";
                    this->lblWinner->Text = gcnew String(wstr.c_str());
                    this->lblWinner->ForeColor = System::Drawing::Color::FromArgb(40,180,99);
                }
            }
            catch (...) {
                // ignore errors, leave list empty
            }
        }

    protected:
        ~ViewResult()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Label^ lblTotal;
        System::Windows::Forms::Label^ lblVoted;
        System::Windows::Forms::Label^ lblYet;
        System::Windows::Forms::Label^ lblPercent;
        System::Windows::Forms::ListBox^ lstCandidateResults;
        System::Windows::Forms::Label^ lblWinner;
        System::Windows::Forms::Button^ btnClose;
        System::ComponentModel::Container ^components;

        void InitializeComponent(void)
        {
            this->lblTotal = (gcnew System::Windows::Forms::Label());
            this->lblVoted = (gcnew System::Windows::Forms::Label());
            this->lblYet = (gcnew System::Windows::Forms::Label());
            this->lblPercent = (gcnew System::Windows::Forms::Label());
            this->btnClose = (gcnew System::Windows::Forms::Button());

            this->SuspendLayout();

            // Form
            this->ClientSize = System::Drawing::Size(520, 180);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Text = L"Voting Results";
            this->BackColor = System::Drawing::Color::Black;
            this->ForeColor = System::Drawing::Color::White;

            // lblTotal
            this->lblTotal->Location = System::Drawing::Point(20, 20);
            this->lblTotal->ForeColor = System::Drawing::Color::White;
            this->lblTotal->Size = System::Drawing::Size(280, 20);
            this->lblTotal->Text = L"Total Registered: 0";

            // lblVoted
            this->lblVoted->Location = System::Drawing::Point(20, 50);
            this->lblVoted->ForeColor = System::Drawing::Color::White;
            this->lblVoted->Size = System::Drawing::Size(280, 20);
            this->lblVoted->Text = L"Votes Cast: 0";

            // lblYet
            this->lblYet->Location = System::Drawing::Point(20, 80);
            this->lblYet->ForeColor = System::Drawing::Color::White;
            this->lblYet->Size = System::Drawing::Size(280, 20);
            this->lblYet->Text = L"Yet to Vote: 0";

            // lblPercent
            this->lblPercent->Location = System::Drawing::Point(20, 110);
            this->lblPercent->ForeColor = System::Drawing::Color::White;
            this->lblPercent->Size = System::Drawing::Size(280, 20);
            this->lblPercent->Text = L"Turnout: 0%";

            // Candidate results list
            this->lstCandidateResults = (gcnew System::Windows::Forms::ListBox());
            this->lstCandidateResults->Location = System::Drawing::Point(320, 20);
            this->lstCandidateResults->Size = System::Drawing::Size(180, 120);
            this->lstCandidateResults->BackColor = System::Drawing::Color::FromArgb(30,30,30);
            this->lstCandidateResults->ForeColor = System::Drawing::Color::White;

            // Winner label
            this->lblWinner = (gcnew System::Windows::Forms::Label());
            this->lblWinner->Location = System::Drawing::Point(20, 140);
            this->lblWinner->Size = System::Drawing::Size(380, 20);
            this->lblWinner->ForeColor = System::Drawing::Color::White;
            this->lblWinner->Text = L"Winner: -";

            // btnClose
            this->btnClose->Location = System::Drawing::Point(420, 140);
            this->btnClose->Size = System::Drawing::Size(80, 28);
            this->btnClose->Text = L"Close";
            this->btnClose->BackColor = System::Drawing::Color::FromArgb(40, 180, 99);
            this->btnClose->ForeColor = System::Drawing::Color::White;
            this->btnClose->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnClose->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
            this->btnClose->Click += gcnew System::EventHandler(this, &ViewResult::btnClose_Click);

            this->Controls->Add(this->lblTotal);
            this->Controls->Add(this->lblVoted);
            this->Controls->Add(this->lblYet);
            this->Controls->Add(this->lblPercent);
            this->Controls->Add(this->lstCandidateResults);
            this->Controls->Add(this->lblWinner);
            this->Controls->Add(this->btnClose);

            this->ResumeLayout(false);
            this->PerformLayout();
        }

        System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e)
        {
            this->Close();
        }
    };

}
