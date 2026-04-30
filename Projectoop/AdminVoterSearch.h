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

    public ref class AdminVoterSearch : public System::Windows::Forms::Form
    {
    public:
        AdminVoterSearch(void)
        {
            InitializeComponent();
        }

    protected:
        ~AdminVoterSearch()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::TextBox^ txtSearchTerm;
        System::Windows::Forms::ComboBox^ cmbFilter;
        System::Windows::Forms::Button^ btnSearch;
        System::Windows::Forms::ListView^ listVoters;
        System::Windows::Forms::ColumnHeader^ colUsername;
        System::Windows::Forms::ColumnHeader^ colID;
        System::Windows::Forms::ColumnHeader^ colStatus;

        System::ComponentModel::Container ^components;

        void InitializeComponent(void)
        {
            this->txtSearchTerm = (gcnew System::Windows::Forms::TextBox());
            this->cmbFilter = (gcnew System::Windows::Forms::ComboBox());
            this->btnSearch = (gcnew System::Windows::Forms::Button());
            this->listVoters = (gcnew System::Windows::Forms::ListView());
            this->colUsername = (gcnew System::Windows::Forms::ColumnHeader());
            this->colID = (gcnew System::Windows::Forms::ColumnHeader());
            this->colStatus = (gcnew System::Windows::Forms::ColumnHeader());
            this->SuspendLayout();

            this->ClientSize = System::Drawing::Size(400, 350);
            this->Text = L"Voter Search & Filter";
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;

            this->txtSearchTerm->Location = System::Drawing::Point(12, 12);
            this->txtSearchTerm->Size = System::Drawing::Size(150, 20);

            this->cmbFilter->FormattingEnabled = true;
            this->cmbFilter->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"All", L"Voted", L"Not Voted" });
            this->cmbFilter->Location = System::Drawing::Point(170, 12);
            this->cmbFilter->Size = System::Drawing::Size(120, 21);
            this->cmbFilter->SelectedIndex = 0;

            this->btnSearch->Location = System::Drawing::Point(300, 10);
            this->btnSearch->Size = System::Drawing::Size(80, 23);
            this->btnSearch->Text = L"Search";
            this->btnSearch->Click += gcnew System::EventHandler(this, &AdminVoterSearch::btnSearch_Click);

            this->listVoters->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {
                this->colUsername, this->colID, this->colStatus
            });
            this->listVoters->View = System::Windows::Forms::View::Details;
            this->listVoters->FullRowSelect = true;
            this->listVoters->GridLines = true;
            this->listVoters->Location = System::Drawing::Point(12, 50);
            this->listVoters->Size = System::Drawing::Size(368, 280);

            this->colUsername->Text = L"Username";
            this->colUsername->Width = 120;
            this->colID->Text = L"Voter ID";
            this->colID->Width = 100;
            this->colStatus->Text = L"Status";
            this->colStatus->Width = 120;

            this->Controls->Add(this->listVoters);
            this->Controls->Add(this->btnSearch);
            this->Controls->Add(this->cmbFilter);
            this->Controls->Add(this->txtSearchTerm);

            this->Load += gcnew System::EventHandler(this, &AdminVoterSearch::AdminVoterSearch_Load);
            this->ResumeLayout(false);
            this->PerformLayout();
        }

        System::Void AdminVoterSearch_Load(System::Object^ sender, System::EventArgs^ e) {
            PerformSearch();
        }

        System::Void btnSearch_Click(System::Object^ sender, System::EventArgs^ e) {
            PerformSearch();
        }

        void PerformSearch() {
            listVoters->Items->Clear();
            std::ifstream voters("voter.txt");
            if (!voters.is_open()) return;

            std::string line;
            String^ searchTerm = txtSearchTerm->Text->ToLower();
            String^ filter = cmbFilter->SelectedItem->ToString();

            while (std::getline(voters, line)) {
                if (line.empty()) continue;
                std::string f_name, f_pass, f_id, f_votedStr;
                std::stringstream ss(line);
                std::getline(ss, f_name, '|');
                std::getline(ss, f_pass, '|');
                std::getline(ss, f_id, '|');
                std::getline(ss, f_votedStr, '|');

                String^ guiName = gcnew String(f_name.c_str());
                String^ guiId = gcnew String(f_id.c_str());
                bool hasVoted = (f_votedStr == "1" || f_votedStr == "1\r");
                String^ guiStatus = hasVoted ? "Voted" : "Not Voted";

                if (!String::IsNullOrWhiteSpace(searchTerm)) {
                    if (!guiName->ToLower()->Contains(searchTerm) && !guiId->ToLower()->Contains(searchTerm)) {
                        continue;
                    }
                }

                if (filter == "Voted" && !hasVoted) continue;
                if (filter == "Not Voted" && hasVoted) continue;

                ListViewItem^ item = gcnew ListViewItem(guiName);
                item->SubItems->Add(guiId);
                item->SubItems->Add(guiStatus);
                listVoters->Items->Add(item);
            }
            voters.close();
        }
    };
}