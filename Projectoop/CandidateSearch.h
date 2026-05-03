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

    public ref class CandidateSearch : public System::Windows::Forms::Form
    {
    private:
        System::Windows::Forms::TextBox^ txtSearchTerm;
        System::Windows::Forms::Button^ btnSearch;
        System::Windows::Forms::Button^ btnCastVote;
        System::Windows::Forms::ListView^ listCandidates;
        System::Windows::Forms::ColumnHeader^ colID;
        System::Windows::Forms::ColumnHeader^ colName;
        System::Windows::Forms::ColumnHeader^ colParty;

        bool isVoterMode;
        bool hasAlreadyVoted;

        System::ComponentModel::Container^ components;

    public:
        String^ SelectedCandidateId;

        CandidateSearch(void)
        {
            isVoterMode = false;
            hasAlreadyVoted = false;
            InitializeComponent();
            UITheme::ApplyTheme(this);
            btnCastVote->Visible = false;
        }

        CandidateSearch(bool isVoter, bool hasVoted)
        {
            isVoterMode = isVoter;
            hasAlreadyVoted = hasVoted;
            InitializeComponent();
            UITheme::ApplyTheme(this);
            if (isVoterMode) {
                btnCastVote->Visible = true;
                if (hasAlreadyVoted) {
                    btnCastVote->Enabled = false;
                    btnCastVote->Text = L"Already Voted";
                }
            } else {
                btnCastVote->Visible = false;
            }
        }

    protected:
        ~CandidateSearch()
        {
            if (components) delete components;
        }

    private:
        void InitializeComponent(void)
        {
            this->txtSearchTerm = (gcnew System::Windows::Forms::TextBox());
            this->btnSearch = (gcnew System::Windows::Forms::Button());
            this->btnCastVote = (gcnew System::Windows::Forms::Button());
            this->listCandidates = (gcnew System::Windows::Forms::ListView());
            this->colID = (gcnew System::Windows::Forms::ColumnHeader());
            this->colName = (gcnew System::Windows::Forms::ColumnHeader());
            this->colParty = (gcnew System::Windows::Forms::ColumnHeader());
            this->SuspendLayout();

            this->ClientSize = System::Drawing::Size(800, 600);
            this->Text = L"Candidate Search";
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;

            this->txtSearchTerm->Location = System::Drawing::Point(20, 20);
            this->txtSearchTerm->Size = System::Drawing::Size(400, 28);

            this->btnSearch->Location = System::Drawing::Point(440, 18);
            this->btnSearch->Size = System::Drawing::Size(120, 28);
            this->btnSearch->Text = L"Search";
            this->btnSearch->Click += gcnew System::EventHandler(this, &CandidateSearch::btnSearch_Click);

            this->btnCastVote->Location = System::Drawing::Point(20, 520);
            this->btnCastVote->Size = System::Drawing::Size(140, 36);
            this->btnCastVote->Text = L"Cast Vote";
            this->btnCastVote->Click += gcnew System::EventHandler(this, &CandidateSearch::btnCastVote_Click);

            this->listCandidates->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^ >(3) {
                this->colID, this->colName, this->colParty
            });
            this->listCandidates->Location = System::Drawing::Point(20, 60);
            this->listCandidates->Size = System::Drawing::Size(760, 440);
            this->listCandidates->View = System::Windows::Forms::View::Details;
            this->listCandidates->FullRowSelect = true;
            this->listCandidates->GridLines = true;

            this->colID->Text = L"ID";
            this->colID->Width = 60;
            this->colName->Text = L"Name";
            this->colName->Width = 150;
            this->colParty->Text = L"Party";
            this->colParty->Width = 140;

            this->Controls->Add(this->listCandidates);
            this->Controls->Add(this->btnSearch);
            this->Controls->Add(this->btnCastVote);
            this->Controls->Add(this->txtSearchTerm);

            this->Load += gcnew System::EventHandler(this, &CandidateSearch::CandidateSearch_Load);
            this->ResumeLayout(false);
            this->PerformLayout();
        }

        System::Void CandidateSearch_Load(System::Object^ sender, System::EventArgs^ e) {
            PerformSearch();
        }

        System::Void btnSearch_Click(System::Object^ sender, System::EventArgs^ e) {
            PerformSearch();
        }

        System::Void btnCastVote_Click(System::Object^ sender, System::EventArgs^ e) {
            if (hasAlreadyVoted) {
                MessageBox::Show("You have already voted!");
                return;
            }
            if (listCandidates->SelectedItems->Count == 0) {
                MessageBox::Show("Please select a candidate first.");
                return;
            }
            SelectedCandidateId = listCandidates->SelectedItems[0]->Text;
            this->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->Close();
        }

        void PerformSearch() {
            listCandidates->Items->Clear();
            std::ifstream in("Candidates.txt");
            if (!in.is_open()) return;

            String^ searchTerm = txtSearchTerm->Text->ToLower();
            std::string line;

            while (std::getline(in, line)) {
                if (line.empty()) continue;
                std::stringstream ss(line);
                std::string name, party, cid;
                std::getline(ss, name, '|');
                std::getline(ss, party, '|');
                std::getline(ss, cid, '|');

                String^ guiName = gcnew String(name.c_str());
                String^ guiParty = gcnew String(party.c_str());
                String^ guiCid = gcnew String(cid.c_str());

                bool match = String::IsNullOrWhiteSpace(searchTerm) ||
                             guiName->ToLower()->Contains(searchTerm) ||
                             guiCid->ToLower()->Contains(searchTerm) ||
                             guiParty->ToLower()->Contains(searchTerm);

                if (match) {
                    ListViewItem^ item = gcnew ListViewItem(guiCid);
                    item->SubItems->Add(guiName);
                    item->SubItems->Add(guiParty);
                    listCandidates->Items->Add(item);
                }
            }
            in.close();
        }
    };
}