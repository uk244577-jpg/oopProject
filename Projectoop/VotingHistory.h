#pragma once
#pragma once
#include "UITheme.h"
#include <msclr/marshal_cppstd.h>
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

    public ref class VotingHistory : public System::Windows::Forms::Form
    {
    private:
        System::Windows::Forms::ListView^ listHistory;
        System::Windows::Forms::ColumnHeader^ colVoter;
        System::Windows::Forms::ColumnHeader^ colCandidate;
        System::Windows::Forms::ColumnHeader^ colTime;

        System::ComponentModel::Container^ components;

    public:
        VotingHistory(void)
        {
            InitializeComponent();
            UITheme::ApplyTheme(this);
        }

    protected:
        ~VotingHistory()
        {
            if (components) delete components;
        }

    private:
        void InitializeComponent(void)
        {
            this->listHistory = (gcnew System::Windows::Forms::ListView());
            this->colVoter = (gcnew System::Windows::Forms::ColumnHeader());
            this->colCandidate = (gcnew System::Windows::Forms::ColumnHeader());
            this->colTime = (gcnew System::Windows::Forms::ColumnHeader());
            this->SuspendLayout();

            this->ClientSize = System::Drawing::Size(460, 360);
            this->Text = L"System Voting History / Audit Log";
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;

            this->listHistory->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^ >(3) {
                this->colVoter, this->colCandidate, this->colTime
            });
            this->listHistory->Location = System::Drawing::Point(15, 15);
            this->listHistory->Size = System::Drawing::Size(430, 320);
            this->listHistory->View = System::Windows::Forms::View::Details;
            this->listHistory->FullRowSelect = true;
            this->listHistory->GridLines = true;

            this->colVoter->Text = L"Voter ID";
            this->colVoter->Width = 100;
            this->colCandidate->Text = L"Candidate ID";
            this->colCandidate->Width = 120;
            this->colTime->Text = L"Timestamp";
            this->colTime->Width = 180;

            this->Controls->Add(this->listHistory);

            this->Load += gcnew System::EventHandler(this, &VotingHistory::VotingHistory_Load);
            this->ResumeLayout(false);
            this->PerformLayout();
        }

        System::Void VotingHistory_Load(System::Object^ sender, System::EventArgs^ e) {
            LoadHistory();
        }

        void LoadHistory() {
            listHistory->Items->Clear();
            std::ifstream in("Votes.txt");
            if (!in.is_open()) return;

            std::string line;
            while (std::getline(in, line)) {
                if (line.empty()) continue;
                std::stringstream ss(line);
                std::string vid, cid, dt;
                std::getline(ss, vid, '|');
                std::getline(ss, cid, '|');
                std::getline(ss, dt, '|');

                String^ guiVoter = gcnew String(vid.c_str());
                String^ guiCand = gcnew String(cid.c_str());
                String^ guiTime = gcnew String(dt.c_str());

                ListViewItem^ item = gcnew ListViewItem(guiVoter);
                item->SubItems->Add(guiCand);
                item->SubItems->Add(guiTime);
                listHistory->Items->Add(item);
            }
            in.close();
        }
    };
}