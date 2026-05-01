#pragma once
#include "Backend.h"
#include "CandidateSearch.h" // Add the new form here
#include <msclr\marshal_cppstd.h>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime> // Add ctime for timestamps

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
        VoterDashboard(String^ voterId, bool hasVoted)
        {
            InitializeComponent();
            this->voterId = voterId;
            this->hasVoted = hasVoted;
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

    private:
        System::Windows::Forms::ListBox^ lstCandidates;
        System::Windows::Forms::Button^ btnVote;
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Label^ lblStatus;
        System::Windows::Forms::Button^ btnRefresh;
        System::Windows::Forms::Button^ btnOpenSlip;
        System::ComponentModel::Container^ components;
        String^ voterId;
        bool hasVoted;

        System::ComponentModel::Container ^components;

        void InitializeComponent(void)
        {
            this->lstCandidates = (gcnew System::Windows::Forms::ListBox());
            this->btnVote = (gcnew System::Windows::Forms::Button());
            this->lblTitle = (gcnew System::Windows::Forms::Label());
            this->lblStatus = (gcnew System::Windows::Forms::Label());
            this->btnRefresh = (gcnew System::Windows::Forms::Button());
            this->btnOpenSlip = (gcnew System::Windows::Forms::Button());
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
            this->btnOpenSlip->Size = System::Drawing::Size(148, 36);
            this->btnOpenSlip->Text = L"Open My Receipt";
            this->btnOpenSlip->Click += gcnew System::EventHandler(this, &VoterDashboard::btnOpenSlip_Click);
            // 
            // VoterDashboard
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(460, 352);
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
                catch (...) { /* ignore if cannot open */ }
        }
            else {
                MessageBox::Show("Failed to record vote. Try again.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }

                msclr::interop::marshal_context context;
                std::string n_vId = context.marshal_as<std::string>(voterId);
                String^ selCid = searchForm->SelectedCandidateId;
                std::string n_cId = context.marshal_as<std::string>(selCid);

                Filehandler fh;
                if (fh.markVoted(n_vId)) {
                    std::ofstream voteOut("Votes.txt", std::ios::app);
                    std::string dt = "";
                    if (voteOut.is_open()) {
                        time_t now = time(0);
                        dt = ctime(&now);
                        if (!dt.empty() && dt.back() == '\n') dt.pop_back();

                        voteOut << n_vId << "|" << n_cId << "|" << dt << "\n";
                        voteOut.close();
                    }

        System::Void btnOpenSlip_Click(System::Object^ sender, System::EventArgs^ e) {
            String^ slipPath = "slip_" + voterId + ".txt";
            try {
                System::Diagnostics::Process::Start(slipPath);
            }
            catch (...) {
                MessageBox::Show("Receipt not found.", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        System::Void btnLogout_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }
    };
}