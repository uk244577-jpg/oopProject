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

    public ref class VoterDashboard : public System::Windows::Forms::Form
    {
    private:
        String^ voterId;
        String^ voterUsername;
        bool hasVoted;

    public:
        VoterDashboard(String^ username, String^ vId, bool voted)
        {
            InitializeComponent();
            this->voterUsername = username;
            this->voterId = vId;
            this->hasVoted = voted;
        }

    protected:
        ~VoterDashboard()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::ListBox^ listCandidates;
        System::Windows::Forms::Button^ btnCastVote;
        System::Windows::Forms::Label^ lblWelcome;
        System::Windows::Forms::Label^ lblStatus;
        System::Windows::Forms::Button^ btnLogout;

        System::ComponentModel::Container ^components;

        void InitializeComponent(void)
        {
            this->listCandidates = (gcnew System::Windows::Forms::ListBox());
            this->btnCastVote = (gcnew System::Windows::Forms::Button());
            this->lblWelcome = (gcnew System::Windows::Forms::Label());
            this->lblStatus = (gcnew System::Windows::Forms::Label());
            this->btnLogout = (gcnew System::Windows::Forms::Button());

            this->ClientSize = System::Drawing::Size(400, 350);
            this->Text = L"Voter Dashboard";
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;

            this->lblWelcome->Location = System::Drawing::Point(20, 20);
            this->lblWelcome->Size = System::Drawing::Size(300, 20);

            this->lblStatus->Location = System::Drawing::Point(20, 50);
            this->lblStatus->Size = System::Drawing::Size(300, 20);
            this->lblStatus->ForeColor = System::Drawing::Color::Red;

            this->listCandidates->FormattingEnabled = true;
            this->listCandidates->Location = System::Drawing::Point(20, 80);
            this->listCandidates->Size = System::Drawing::Size(350, 200);

            this->btnCastVote->Location = System::Drawing::Point(20, 300);
            this->btnCastVote->Size = System::Drawing::Size(150, 30);
            this->btnCastVote->Text = L"Cast Vote";
            this->btnCastVote->Click += gcnew System::EventHandler(this, &VoterDashboard::btnCastVote_Click);

            this->btnLogout->Location = System::Drawing::Point(220, 300);
            this->btnLogout->Size = System::Drawing::Size(150, 30);
            this->btnLogout->Text = L"Logout";
            this->btnLogout->Click += gcnew System::EventHandler(this, &VoterDashboard::btnLogout_Click);

            this->Controls->Add(this->lblWelcome);
            this->Controls->Add(this->lblStatus);
            this->Controls->Add(this->listCandidates);
            this->Controls->Add(this->btnCastVote);
            this->Controls->Add(this->btnLogout);

            this->Load += gcnew System::EventHandler(this, &VoterDashboard::VoterDashboard_Load);
        }

        System::Void VoterDashboard_Load(System::Object^ sender, System::EventArgs^ e) {
            lblWelcome->Text = "Welcome, " + voterUsername + " (ID: " + voterId + ")";
            if (hasVoted) {
                lblStatus->Text = "You have already cast your vote. Thank you!";
                btnCastVote->Enabled = false;
            } else {
                lblStatus->Text = "Please select a candidate and cast your vote.";
                lblStatus->ForeColor = System::Drawing::Color::Green;
            }

            LoadCandidates();
        }

        void LoadCandidates() {
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

                String^ displayStr = gcnew String((cid + " - " + name + " (" + party + ")").c_str());
                listCandidates->Items->Add(displayStr);
            }
            in.close();
        }

        System::Void btnCastVote_Click(System::Object^ sender, System::EventArgs^ e) {
            if (hasVoted) {
                MessageBox::Show("You have already voted! Duplicate voting is prevented.", "Denied", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }
            if (listCandidates->SelectedIndex == -1) {
                MessageBox::Show("Please select a candidate first.");
                return;
            }

            msclr::interop::marshal_context context;
            std::string n_vId = context.marshal_as<std::string>(voterId);

            Filehandler fh;
            if (fh.markVoted(n_vId)) {
                MessageBox::Show("Your vote has been cast securely. Thank you!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                hasVoted = true;
                btnCastVote->Enabled = false;
                lblStatus->Text = "You have already cast your vote. Thank you!";
                lblStatus->ForeColor = System::Drawing::Color::Red;
            } else {
                MessageBox::Show("An error occurred while casting your vote.");
            }
        }

        System::Void btnLogout_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }
    };
}