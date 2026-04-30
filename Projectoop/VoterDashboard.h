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
        System::Windows::Forms::Button^ btnSearchCand;
        System::Windows::Forms::Button^ btnLogout;

        System::ComponentModel::Container ^components;

        void InitializeComponent(void)
        {
            this->listCandidates = (gcnew System::Windows::Forms::ListBox());
            this->btnCastVote = (gcnew System::Windows::Forms::Button());
            this->lblWelcome = (gcnew System::Windows::Forms::Label());
            this->lblStatus = (gcnew System::Windows::Forms::Label());
            this->btnSearchCand = (gcnew System::Windows::Forms::Button());
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
            this->btnCastVote->Size = System::Drawing::Size(110, 30);
            this->btnCastVote->Text = L"Cast Vote";
            this->btnCastVote->Click += gcnew System::EventHandler(this, &VoterDashboard::btnCastVote_Click);

            this->btnSearchCand->Location = System::Drawing::Point(140, 300);
            this->btnSearchCand->Size = System::Drawing::Size(110, 30);
            this->btnSearchCand->Text = L"Search Candidates";
            this->btnSearchCand->Click += gcnew System::EventHandler(this, &VoterDashboard::btnSearchCand_Click);

            this->btnLogout->Location = System::Drawing::Point(260, 300);
            this->btnLogout->Size = System::Drawing::Size(110, 30);
            this->btnLogout->Text = L"Logout";
            this->btnLogout->Click += gcnew System::EventHandler(this, &VoterDashboard::btnLogout_Click);

            this->Controls->Add(this->lblWelcome);
            this->Controls->Add(this->lblStatus);
            this->Controls->Add(this->listCandidates);
            this->Controls->Add(this->btnCastVote);
            this->Controls->Add(this->btnSearchCand);
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

        void GenerateSlip(std::string vId, std::string cId, std::string dt) {
            time_t t = time(0);
            std::string refId = "VOTE_REF_" + vId + "_" + std::to_string(t);

            std::string slip = "=================================================\n";
            slip += "             DIGITAL VOTING SLIP             \n";
            slip += "=================================================\n";
            slip += " Voter Profile ID    : " + vId + "\n";
            slip += " Candidate Voted For : " + cId + "\n";
            slip += " Official Timestamp  : " + dt + "\n";
            slip += " Secure Reference ID : " + refId + "\n";
            slip += "=================================================\n";
            slip += " Keep this slip as cryptographic proof of your   \n";
            slip += " participation in the election protocol.         \n";
            slip += "=================================================\n";

            std::string filename = "Slip_" + vId + ".txt";
            std::ofstream out(filename);
            if (out.is_open()) {
                out << slip;
                out.close();
            }

            String^ sysSlip = gcnew String(slip.c_str());
            MessageBox::Show("Vote Registered Successfully!\n\nA digital confirmation slip has been generated and saved locally as 'Slip_" + gcnew String(vId.c_str()) + ".txt'.\n\n" + sysSlip,
                             "Confirmation Slip", MessageBoxButtons::OK, MessageBoxIcon::Information);
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

            // Extract candidate ID from selected string
            String^ selItem = listCandidates->SelectedItem->ToString();
            cli::array<String^>^ parts = selItem->Split('-');
            String^ selCid = parts[0]->Trim();
            std::string n_cId = context.marshal_as<std::string>(selCid);

            Filehandler fh;
            if (fh.markVoted(n_vId)) {
                // Record the vote explicitly for the candidate
                std::ofstream voteOut("Votes.txt", std::ios::app);
                std::string dt = "";
                if (voteOut.is_open()) {
                    time_t now = time(0);
                    dt = ctime(&now);
                    if (!dt.empty() && dt.back() == '\n') dt.pop_back();

                    voteOut << n_vId << "|" << n_cId << "|" << dt << "\n";
                    voteOut.close();
                }

                GenerateSlip(n_vId, n_cId, dt);

                hasVoted = true;
                btnCastVote->Enabled = false;
                lblStatus->Text = "You have already cast your vote. Thank you!";
                lblStatus->ForeColor = System::Drawing::Color::Red;
            } else {
                MessageBox::Show("An error occurred while casting your vote.");
            }
        }

        System::Void btnSearchCand_Click(System::Object^ sender, System::EventArgs^ e) {
            Projectoop::CandidateSearch^ searchForm = gcnew Projectoop::CandidateSearch(true, hasVoted);
            if (searchForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                if (hasVoted) {
                    MessageBox::Show("You have already voted!", "Denied", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return;
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

                    GenerateSlip(n_vId, n_cId, dt);

                    hasVoted = true;
                    btnCastVote->Enabled = false;
                    lblStatus->Text = "You have already cast your vote. Thank you!";
                    lblStatus->ForeColor = System::Drawing::Color::Red;
                } else {
                    MessageBox::Show("An error occurred while casting your vote.");
                }
            }
        }

        System::Void btnLogout_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }
    };
}