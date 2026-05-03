#pragma once
#include "BackendAdmin.h"
#include "UITheme.h"
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Data;
using namespace System::Drawing;

namespace Projectoop {

    // Forward declarations
    ref class AdminDashboard;
    ref class AddCandidateForm;
    ref class RemoveCandidateForm;
    ref class DeleteVoterForm;

    // Add Candidate Form - Dialog 1
    public ref class AddCandidateForm : public System::Windows::Forms::Form
    {
    private:
        Admin* adminObj;
        System::Windows::Forms::Label^ labelName;
        System::Windows::Forms::Label^ labelParty;
        System::Windows::Forms::TextBox^ txtCandidateName;
        System::Windows::Forms::TextBox^ txtCandidateParty;
        System::Windows::Forms::Button^ btnAddCandidate;
        System::Windows::Forms::Button^ btnCancel;
        System::ComponentModel::Container^ components;

    public:
        AddCandidateForm(Admin* admin)
        {
            InitializeComponent();
            UITheme::ApplyTheme(this);
            adminObj = admin;
        }

    protected:
        ~AddCandidateForm()
        {
            if (components)
            {
                delete components;
            }
        }

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->labelName = (gcnew System::Windows::Forms::Label());
            this->labelParty = (gcnew System::Windows::Forms::Label());
            this->txtCandidateName = (gcnew System::Windows::Forms::TextBox());
            this->txtCandidateParty = (gcnew System::Windows::Forms::TextBox());
            this->btnAddCandidate = (gcnew System::Windows::Forms::Button());
            this->btnCancel = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();

            // labelName
            this->labelName->AutoSize = true;
            this->labelName->Location = System::Drawing::Point(30, 30);
            this->labelName->Name = L"labelName";
            this->labelName->Size = System::Drawing::Size(120, 13);
            this->labelName->TabIndex = 0;
            this->labelName->Text = L"Candidate Name:";
            this->labelName->ForeColor = System::Drawing::Color::White;

            // txtCandidateName
            this->txtCandidateName->Location = System::Drawing::Point(30, 50);
            this->txtCandidateName->Name = L"txtCandidateName";
            this->txtCandidateName->Size = System::Drawing::Size(200, 20);
            this->txtCandidateName->TabIndex = 1;
            this->txtCandidateName->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
            this->txtCandidateName->ForeColor = System::Drawing::Color::White;

            // labelParty
            this->labelParty->AutoSize = true;
            this->labelParty->Location = System::Drawing::Point(30, 90);
            this->labelParty->Name = L"labelParty";
            this->labelParty->Size = System::Drawing::Size(120, 13);
            this->labelParty->TabIndex = 2;
            this->labelParty->Text = L"Party Name:";
            this->labelParty->ForeColor = System::Drawing::Color::White;

            // txtCandidateParty
            this->txtCandidateParty->Location = System::Drawing::Point(30, 110);
            this->txtCandidateParty->Name = L"txtCandidateParty";
            this->txtCandidateParty->Size = System::Drawing::Size(200, 20);
            this->txtCandidateParty->TabIndex = 3;
            this->txtCandidateParty->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
            this->txtCandidateParty->ForeColor = System::Drawing::Color::White;

            // btnAddCandidate
            this->btnAddCandidate->Location = System::Drawing::Point(30, 160);
            this->btnAddCandidate->Name = L"btnAddCandidate";
            this->btnAddCandidate->Size = System::Drawing::Size(90, 30);
            this->btnAddCandidate->TabIndex = 4;
            this->btnAddCandidate->Text = L"Add";
            this->btnAddCandidate->BackColor = System::Drawing::Color::FromArgb(40, 180, 99);
            this->btnAddCandidate->ForeColor = System::Drawing::Color::White;
            this->btnAddCandidate->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnAddCandidate->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
            this->btnAddCandidate->Click += gcnew System::EventHandler(this, &AddCandidateForm::btnAddCandidate_Click);

            // btnCancel
            this->btnCancel->Location = System::Drawing::Point(140, 160);
            this->btnCancel->Name = L"btnCancel";
            this->btnCancel->Size = System::Drawing::Size(90, 30);
            this->btnCancel->TabIndex = 5;
            this->btnCancel->Text = L"Cancel";
            this->btnCancel->BackColor = System::Drawing::Color::FromArgb(45, 45, 45);
            this->btnCancel->ForeColor = System::Drawing::Color::White;
            this->btnCancel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnCancel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
            this->btnCancel->Click += gcnew System::EventHandler(this, &AddCandidateForm::btnCancel_Click);

            // AddCandidateForm
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(280, 220);
            this->BackColor = System::Drawing::Color::Black;
            this->ForeColor = System::Drawing::Color::White;
            this->Controls->Add(this->btnCancel);
            this->Controls->Add(this->btnAddCandidate);
            this->Controls->Add(this->txtCandidateParty);
            this->Controls->Add(this->labelParty);
            this->Controls->Add(this->txtCandidateName);
            this->Controls->Add(this->labelName);
            this->Name = L"AddCandidateForm";
            this->Text = L"Add Candidate";
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private: System::Void btnAddCandidate_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (String::IsNullOrWhiteSpace(txtCandidateName->Text) || String::IsNullOrWhiteSpace(txtCandidateParty->Text))
        {
            MessageBox::Show("Please enter both candidate name and party.", "Missing Info", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        msclr::interop::marshal_context context;
        std::string nativeName = context.marshal_as<std::string>(txtCandidateName->Text);
        std::string nativeParty = context.marshal_as<std::string>(txtCandidateParty->Text);

        if (adminObj->addCandidate(nativeName, nativeParty))
        {
            MessageBox::Show("Candidate added successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
            this->Close();
        }
        else
        {
            MessageBox::Show("Error adding candidate.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    private: System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->Close();
    }
    };

    // Remove Candidate Form - Dialog 2
    public ref class RemoveCandidateForm : public System::Windows::Forms::Form
    {
    private:
        Admin* adminObj;
        System::Windows::Forms::Label^ labelCandidateId;
        System::Windows::Forms::TextBox^ txtRemoveCandidateId;
        System::Windows::Forms::Button^ btnRemove;
        System::Windows::Forms::Button^ btnCancel;
        System::ComponentModel::Container^ components;

    public:
        RemoveCandidateForm(Admin* admin)
        {
            InitializeComponent();
            UITheme::ApplyTheme(this);
            adminObj = admin;
        }

    protected:
        ~RemoveCandidateForm()
        {
            if (components)
            {
                delete components;
            }
        }

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->labelCandidateId = (gcnew System::Windows::Forms::Label());
            this->txtRemoveCandidateId = (gcnew System::Windows::Forms::TextBox());
            this->btnRemove = (gcnew System::Windows::Forms::Button());
            this->btnCancel = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();

            // labelCandidateId
            this->labelCandidateId->AutoSize = true;
            this->labelCandidateId->Location = System::Drawing::Point(30, 30);
            this->labelCandidateId->Name = L"labelCandidateId";
            this->labelCandidateId->Size = System::Drawing::Size(100, 13);
            this->labelCandidateId->TabIndex = 0;
            this->labelCandidateId->Text = L"Candidate ID:";
            this->labelCandidateId->ForeColor = System::Drawing::Color::White;

            // txtRemoveCandidateId
            this->txtRemoveCandidateId->Location = System::Drawing::Point(30, 50);
            this->txtRemoveCandidateId->Name = L"txtRemoveCandidateId";
            this->txtRemoveCandidateId->Size = System::Drawing::Size(200, 20);
            this->txtRemoveCandidateId->TabIndex = 1;
            this->txtRemoveCandidateId->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
            this->txtRemoveCandidateId->ForeColor = System::Drawing::Color::White;

            // btnRemove
            this->btnRemove->Location = System::Drawing::Point(30, 100);
            this->btnRemove->Name = L"btnRemove";
            this->btnRemove->Size = System::Drawing::Size(90, 30);
            this->btnRemove->TabIndex = 2;
            this->btnRemove->Text = L"Remove";
            this->btnRemove->BackColor = System::Drawing::Color::FromArgb(231, 76, 60);
            this->btnRemove->ForeColor = System::Drawing::Color::White;
            this->btnRemove->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnRemove->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
            this->btnRemove->Click += gcnew System::EventHandler(this, &RemoveCandidateForm::btnRemove_Click);

            // btnCancel
            this->btnCancel->Location = System::Drawing::Point(140, 100);
            this->btnCancel->Name = L"btnCancel";
            this->btnCancel->Size = System::Drawing::Size(90, 30);
            this->btnCancel->TabIndex = 3;
            this->btnCancel->Text = L"Cancel";
            this->btnCancel->BackColor = System::Drawing::Color::FromArgb(45, 45, 45);
            this->btnCancel->ForeColor = System::Drawing::Color::White;
            this->btnCancel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnCancel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
            this->btnCancel->Click += gcnew System::EventHandler(this, &RemoveCandidateForm::btnCancel_Click);

            // RemoveCandidateForm
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(280, 180);
            this->BackColor = System::Drawing::Color::Black;
            this->ForeColor = System::Drawing::Color::White;
            this->BackColor = System::Drawing::Color::Black;
            this->ForeColor = System::Drawing::Color::White;
            this->Controls->Add(this->btnCancel);
            this->Controls->Add(this->btnRemove);
            this->Controls->Add(this->txtRemoveCandidateId);
            this->Controls->Add(this->labelCandidateId);
            this->Name = L"RemoveCandidateForm";
            this->Text = L"Remove Candidate";
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private: System::Void btnRemove_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (String::IsNullOrWhiteSpace(txtRemoveCandidateId->Text))
        {
            MessageBox::Show("Please enter a candidate ID.", "Missing Info", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        msclr::interop::marshal_context context;
        std::string nativeId = context.marshal_as<std::string>(txtRemoveCandidateId->Text);

        if (adminObj->removeCandidate(nativeId))
        {
            MessageBox::Show("Candidate removed successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
        else
        {
            MessageBox::Show("Candidate ID not found.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
        this->Close();
    }

    private: System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->Close();
    }
    };

    // Delete Voter Form - Dialog 3
    public ref class DeleteVoterForm : public System::Windows::Forms::Form
    {
    private:
        Admin* adminObj;
        System::Windows::Forms::Label^ labelVoterId;
        System::Windows::Forms::TextBox^ txtDeleteVoterId;
        System::Windows::Forms::Button^ btnDelete;
        System::Windows::Forms::Button^ btnCancel;
        System::ComponentModel::Container^ components;

    public:
        DeleteVoterForm(Admin* admin)
        {
            InitializeComponent();
            UITheme::ApplyTheme(this);
            adminObj = admin;
        }

    protected:
        ~DeleteVoterForm()
        {
            if (components)
            {
                delete components;
            }
        }

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->labelVoterId = (gcnew System::Windows::Forms::Label());
            this->txtDeleteVoterId = (gcnew System::Windows::Forms::TextBox());
            this->btnDelete = (gcnew System::Windows::Forms::Button());
            this->btnCancel = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();

            // labelVoterId
            this->labelVoterId->AutoSize = true;
            this->labelVoterId->ForeColor = System::Drawing::Color::White;
            this->labelVoterId->Location = System::Drawing::Point(30, 30);
            this->labelVoterId->Name = L"labelVoterId";
            this->labelVoterId->Size = System::Drawing::Size(100, 13);
            this->labelVoterId->TabIndex = 0;
            this->labelVoterId->Text = L"Voter ID:";

            // txtDeleteVoterId
            this->txtDeleteVoterId->Location = System::Drawing::Point(30, 50);
            this->txtDeleteVoterId->Name = L"txtDeleteVoterId";
            this->txtDeleteVoterId->Size = System::Drawing::Size(200, 20);
            this->txtDeleteVoterId->TabIndex = 1;
            this->txtDeleteVoterId->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
            this->txtDeleteVoterId->ForeColor = System::Drawing::Color::White;

            // btnDelete
            this->btnDelete->Location = System::Drawing::Point(30, 100);
            this->btnDelete->Name = L"btnDelete";
            this->btnDelete->Size = System::Drawing::Size(90, 30);
            this->btnDelete->TabIndex = 2;
            this->btnDelete->Text = L"Delete";
            this->btnDelete->BackColor = System::Drawing::Color::FromArgb(231, 76, 60);
            this->btnDelete->ForeColor = System::Drawing::Color::White;
            this->btnDelete->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnDelete->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
            this->btnDelete->Click += gcnew System::EventHandler(this, &DeleteVoterForm::btnDelete_Click);

            // btnCancel
            this->btnCancel->Location = System::Drawing::Point(140, 100);
            this->btnCancel->Name = L"btnCancel";
            this->btnCancel->Size = System::Drawing::Size(90, 30);
            this->btnCancel->TabIndex = 3;
            this->btnCancel->Text = L"Cancel";
            this->btnCancel->BackColor = System::Drawing::Color::FromArgb(45, 45, 45);
            this->btnCancel->ForeColor = System::Drawing::Color::White;
            this->btnCancel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnCancel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
            this->btnCancel->Click += gcnew System::EventHandler(this, &DeleteVoterForm::btnCancel_Click);

            // DeleteVoterForm
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(280, 180);
            this->Controls->Add(this->btnCancel);
            this->Controls->Add(this->btnDelete);
            this->Controls->Add(this->txtDeleteVoterId);
            this->Controls->Add(this->labelVoterId);
            this->Name = L"DeleteVoterForm";
            this->Text = L"Delete Voter";
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private: System::Void btnDelete_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (String::IsNullOrWhiteSpace(txtDeleteVoterId->Text))
        {
            MessageBox::Show("Please enter a voter ID.", "Missing Info", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        msclr::interop::marshal_context context;
        std::string nativeVoterId = context.marshal_as<std::string>(txtDeleteVoterId->Text);

        if (adminObj->deleteVoter(nativeVoterId))
        {
            MessageBox::Show("Voter deleted successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
        else
        {
            MessageBox::Show("Voter ID not found.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
        this->Close();
    }

    private: System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->Close();
    }
    };

    // Admin Dashboard Form - Main panel
    public ref class AdminDashboard : public System::Windows::Forms::Form
    {
    private:
        Admin* adminObj;
        Filehandler* fh;
        System::Windows::Forms::Button^ btnAddCandidate;
        System::Windows::Forms::Button^ btnRemoveCandidate;
        System::Windows::Forms::Button^ btnDeleteVoter;
        System::Windows::Forms::Button^ btnViewCandidates;
        System::Windows::Forms::Button^ btnResetElection;
        System::Windows::Forms::Button^ btnLogout;
        System::Windows::Forms::ListBox^ lstCandidates;
        System::Windows::Forms::Label^ labelTitle;
        System::ComponentModel::Container^ components;

    public:
        AdminDashboard(Admin* admin, Filehandler* filehandler)
        {
            InitializeComponent();
            UITheme::ApplyTheme(this);
            adminObj = admin;
            fh = filehandler;
            RefreshCandidateList();
        }

    protected:
        ~AdminDashboard()
        {
            if (components)
            {
                delete components;
            }
        }

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->btnAddCandidate = (gcnew System::Windows::Forms::Button());
            this->btnRemoveCandidate = (gcnew System::Windows::Forms::Button());
            this->btnDeleteVoter = (gcnew System::Windows::Forms::Button());
            this->btnViewCandidates = (gcnew System::Windows::Forms::Button());
            this->btnResetElection = (gcnew System::Windows::Forms::Button());
            this->btnLogout = (gcnew System::Windows::Forms::Button());
            this->lstCandidates = (gcnew System::Windows::Forms::ListBox());
            this->labelTitle = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();

            // labelTitle
            this->labelTitle->AutoSize = true;
            this->labelTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold));
            this->labelTitle->Location = System::Drawing::Point(120, 10);
            this->labelTitle->Name = L"labelTitle";
            this->labelTitle->Size = System::Drawing::Size(240, 24);
            this->labelTitle->TabIndex = 0;
            this->labelTitle->Text = L"ADMIN DASHBOARD";

            // btnAddCandidate
            this->btnAddCandidate->Location = System::Drawing::Point(30, 50);
            this->btnAddCandidate->Name = L"btnAddCandidate";
            this->btnAddCandidate->Size = System::Drawing::Size(150, 40);
            this->btnAddCandidate->TabIndex = 1;
            this->btnAddCandidate->Text = L"Add Candidate";
            this->btnAddCandidate->UseVisualStyleBackColor = true;
            this->btnAddCandidate->Click += gcnew System::EventHandler(this, &AdminDashboard::btnAddCandidate_Click);

            // btnRemoveCandidate
            this->btnRemoveCandidate->Location = System::Drawing::Point(190, 50);
            this->btnRemoveCandidate->Name = L"btnRemoveCandidate";
            this->btnRemoveCandidate->Size = System::Drawing::Size(150, 40);
            this->btnRemoveCandidate->TabIndex = 2;
            this->btnRemoveCandidate->Text = L"Remove Candidate";
            this->btnRemoveCandidate->UseVisualStyleBackColor = true;
            this->btnRemoveCandidate->Click += gcnew System::EventHandler(this, &AdminDashboard::btnRemoveCandidate_Click);

            // btnDeleteVoter
            this->btnDeleteVoter->Location = System::Drawing::Point(350, 50);
            this->btnDeleteVoter->Name = L"btnDeleteVoter";
            this->btnDeleteVoter->Size = System::Drawing::Size(120, 40);
            this->btnDeleteVoter->TabIndex = 3;
            this->btnDeleteVoter->Text = L"Delete Voter";
            this->btnDeleteVoter->UseVisualStyleBackColor = true;
            this->btnDeleteVoter->Click += gcnew System::EventHandler(this, &AdminDashboard::btnDeleteVoter_Click);

            // btnViewCandidates
            this->btnViewCandidates->Location = System::Drawing::Point(30, 110);
            this->btnViewCandidates->Name = L"btnViewCandidates";
            this->btnViewCandidates->Size = System::Drawing::Size(150, 40);
            this->btnViewCandidates->TabIndex = 4;
            this->btnViewCandidates->Text = L"View Candidates";
            this->btnViewCandidates->UseVisualStyleBackColor = true;
            this->btnViewCandidates->Click += gcnew System::EventHandler(this, &AdminDashboard::btnViewCandidates_Click);

            // btnResetElection
            this->btnResetElection->Location = System::Drawing::Point(190, 110);
            this->btnResetElection->Name = L"btnResetElection";
            this->btnResetElection->Size = System::Drawing::Size(150, 40);
            this->btnResetElection->TabIndex = 5;
            this->btnResetElection->Text = L"Reset Election";
            this->btnResetElection->UseVisualStyleBackColor = true;
            this->btnResetElection->Click += gcnew System::EventHandler(this, &AdminDashboard::btnResetElection_Click);

            // btnLogout
            this->btnLogout->Location = System::Drawing::Point(350, 110);
            this->btnLogout->Name = L"btnLogout";
            this->btnLogout->Size = System::Drawing::Size(120, 40);
            this->btnLogout->TabIndex = 6;
            this->btnLogout->Text = L"Logout";
            this->btnLogout->UseVisualStyleBackColor = true;
            this->btnLogout->Click += gcnew System::EventHandler(this, &AdminDashboard::btnLogout_Click);

            // lstCandidates
            this->lstCandidates->FormattingEnabled = true;
            this->lstCandidates->Location = System::Drawing::Point(30, 180);
            this->lstCandidates->Name = L"lstCandidates";
            this->lstCandidates->Size = System::Drawing::Size(440, 200);
            this->lstCandidates->TabIndex = 7;

            // AdminDashboard
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::Black;
            this->ForeColor = System::Drawing::Color::White;
            this->ClientSize = System::Drawing::Size(500, 400);
            this->Controls->Add(this->lstCandidates);
            this->Controls->Add(this->btnLogout);
            this->Controls->Add(this->btnResetElection);
            this->Controls->Add(this->btnViewCandidates);
            this->Controls->Add(this->btnDeleteVoter);
            this->Controls->Add(this->btnRemoveCandidate);
            this->Controls->Add(this->btnAddCandidate);
            this->Controls->Add(this->labelTitle);
            this->Name = L"AdminDashboard";
            this->Text = L"Admin Dashboard";
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private: System::Void btnAddCandidate_Click(System::Object^ sender, System::EventArgs^ e)
    {
        AddCandidateForm^ addForm = gcnew AddCandidateForm(adminObj);
        addForm->ShowDialog();
        RefreshCandidateList();
    }

    private: System::Void btnRemoveCandidate_Click(System::Object^ sender, System::EventArgs^ e)
    {
        RemoveCandidateForm^ removeForm = gcnew RemoveCandidateForm(adminObj);
        removeForm->ShowDialog();
        RefreshCandidateList();
    }

    private: System::Void btnDeleteVoter_Click(System::Object^ sender, System::EventArgs^ e)
    {
        DeleteVoterForm^ deleteForm = gcnew DeleteVoterForm(adminObj);
        deleteForm->ShowDialog();
    }

    private: System::Void btnViewCandidates_Click(System::Object^ sender, System::EventArgs^ e)
    {
        RefreshCandidateList();
    }

    private: System::Void btnResetElection_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (MessageBox::Show("Are you sure you want to reset the election? This will clear all votes.", "Confirm Reset", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) == System::Windows::Forms::DialogResult::Yes)
        {
            adminObj->resetElection();
            MessageBox::Show("Election reset successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
    }

    private: System::Void btnLogout_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->Close();
    }

    private: void RefreshCandidateList()
    {
        lstCandidates->Items->Clear();
        ifstream in("Candidates.txt");
        if (!in.is_open())
        {
            lstCandidates->Items->Add("No candidates found.");
            return;
        }

        string line;
        while (getline(in, line))
        {
            if (line != "")
            {
                msclr::interop::marshal_context context;
                String^ managedLine = context.marshal_as<String^>(line);
                lstCandidates->Items->Add(managedLine);
            }
        }
        in.close();
    }
    };

    // Admin Login Form - Main entry point
    public ref class AdminForm : public System::Windows::Forms::Form
    {
    private:
        Admin* adminObj;
        Filehandler* fh;
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::Label^ label2;
        System::Windows::Forms::Label^ label3;
        System::Windows::Forms::TextBox^ txtAdminUsername;
        System::Windows::Forms::TextBox^ txtAdminPassword;
        System::Windows::Forms::Button^ btnAdminLogin;
        System::ComponentModel::Container^ components;

    public:
        AdminForm(void)
        {
            InitializeComponent();
            UITheme::ApplyTheme(this);
            adminObj = new Admin();
            fh = new Filehandler();
        }

    protected:
        ~AdminForm()
        {
            if (components)
            {
                delete components;
            }
            if (adminObj) delete adminObj;
            if (fh) delete fh;
        }

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->txtAdminUsername = (gcnew System::Windows::Forms::TextBox());
            this->txtAdminPassword = (gcnew System::Windows::Forms::TextBox());
            this->btnAdminLogin = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();

            // label1 - Title
            this->label1->AutoSize = true;
            this->label1->BackColor = System::Drawing::Color::Transparent;
            this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
            this->label1->Location = System::Drawing::Point(150, 30);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(180, 20);
            this->label1->TabIndex = 0;
            this->label1->Text = L"ADMIN LOGIN";
            this->label1->TextAlign = System::Drawing::ContentAlignment::TopCenter;

            // label2 - Username
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(150, 80);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(70, 13);
            this->label2->TabIndex = 1;
            this->label2->Text = L"Username:";

            // txtAdminUsername
            this->txtAdminUsername->Location = System::Drawing::Point(150, 100);
            this->txtAdminUsername->Name = L"txtAdminUsername";
            this->txtAdminUsername->Size = System::Drawing::Size(180, 20);
            this->txtAdminUsername->TabIndex = 2;

            // label3 - Password
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(150, 130);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(70, 13);
            this->label3->TabIndex = 3;
            this->label3->Text = L"Password:";

            // txtAdminPassword
            this->txtAdminPassword->Location = System::Drawing::Point(150, 150);
            this->txtAdminPassword->Name = L"txtAdminPassword";
            this->txtAdminPassword->Size = System::Drawing::Size(180, 20);
            this->txtAdminPassword->TabIndex = 4;
            this->txtAdminPassword->UseSystemPasswordChar = true;

            // btnAdminLogin
            this->btnAdminLogin->Location = System::Drawing::Point(200, 200);
            this->btnAdminLogin->Name = L"btnAdminLogin";
            this->btnAdminLogin->Size = System::Drawing::Size(80, 30);
            this->btnAdminLogin->TabIndex = 5;
            this->btnAdminLogin->Text = L"Login";
            this->btnAdminLogin->UseVisualStyleBackColor = true;
            this->btnAdminLogin->Click += gcnew System::EventHandler(this, &AdminForm::btnAdminLogin_Click);

            // AdminForm
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::Black;
            this->ForeColor = System::Drawing::Color::White;
            this->ClientSize = System::Drawing::Size(480, 326);
            this->Controls->Add(this->btnAdminLogin);
            this->Controls->Add(this->txtAdminPassword);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->txtAdminUsername);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->Name = L"AdminForm";
            this->Text = L"Admin Login";
            // Theme styling
            this->label1->ForeColor = System::Drawing::Color::White;
            this->label2->ForeColor = System::Drawing::Color::White;
            this->label3->ForeColor = System::Drawing::Color::White;
            System::Drawing::Color primaryGreen = System::Drawing::Color::FromArgb(40, 180, 99);
            System::Drawing::Color darkBg = System::Drawing::Color::FromArgb(30, 30, 30);
            this->txtAdminUsername->BackColor = darkBg;
            this->txtAdminUsername->ForeColor = System::Drawing::Color::White;
            this->txtAdminPassword->BackColor = darkBg;
            this->txtAdminPassword->ForeColor = System::Drawing::Color::White;
            this->btnAdminLogin->BackColor = primaryGreen;
            this->btnAdminLogin->ForeColor = System::Drawing::Color::White;
            this->btnAdminLogin->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnAdminLogin->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private: System::Void btnAdminLogin_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (String::IsNullOrWhiteSpace(txtAdminUsername->Text) || String::IsNullOrWhiteSpace(txtAdminPassword->Text))
        {
            MessageBox::Show("Please enter both username and password.", "Missing Info", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        msclr::interop::marshal_context context;
        std::string nativeAdminUser = context.marshal_as<std::string>(txtAdminUsername->Text);
        std::string nativeAdminPass = context.marshal_as<std::string>(txtAdminPassword->Text);

        if (adminObj->loginFromForm(nativeAdminUser, nativeAdminPass))
        {
            MessageBox::Show("Admin Login Successful!", "Welcome Admin", MessageBoxButtons::OK, MessageBoxIcon::Information);

            // Hide login form and open admin dashboard
            this->Hide();
            AdminDashboard^ dashboard = gcnew AdminDashboard(adminObj, fh);
            dashboard->ShowDialog();
            this->Show();

            // Clear fields after logout
            txtAdminUsername->Clear();
            txtAdminPassword->Clear();
        }
        else
        {
            MessageBox::Show("Invalid admin username or password.", "Login Failed", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
    };
}
