#pragma once
#include "Backend.h"
#include <msclr\marshal_cppstd.h>

namespace Projectoop {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class RegisterVoter : public System::Windows::Forms::Form
    {
    public:
        RegisterVoter(void)
        {
            InitializeComponent();
        }

    protected:
        ~RegisterVoter()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Label^ lblUser;
        System::Windows::Forms::Label^ lblPass;
        System::Windows::Forms::Label^ lblVoterId;
        System::Windows::Forms::TextBox^ txtUser;
        System::Windows::Forms::TextBox^ txtPass;
        System::Windows::Forms::TextBox^ txtVoterId;
        System::Windows::Forms::Button^ btnRegister;
        System::Windows::Forms::Button^ btnCancel;
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->lblUser = (gcnew System::Windows::Forms::Label());
            this->lblPass = (gcnew System::Windows::Forms::Label());
            this->lblVoterId = (gcnew System::Windows::Forms::Label());
            this->txtUser = (gcnew System::Windows::Forms::TextBox());
            this->txtPass = (gcnew System::Windows::Forms::TextBox());
            this->txtVoterId = (gcnew System::Windows::Forms::TextBox());
            this->btnRegister = (gcnew System::Windows::Forms::Button());
            this->btnCancel = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();
            // 
            // lblUser
            // 
            this->lblUser->AutoSize = true;
            this->lblUser->Location = System::Drawing::Point(24, 20);
            this->lblUser->Name = L"lblUser";
            this->lblUser->Size = System::Drawing::Size(55, 13);
            this->lblUser->TabIndex = 0;
            this->lblUser->Text = L"Username";
            this->lblUser->ForeColor = System::Drawing::Color::White;
            // 
            // txtUser
            // 
            this->txtUser->Location = System::Drawing::Point(24, 40);
            this->txtUser->Name = L"txtUser";
            this->txtUser->Size = System::Drawing::Size(200, 20);
            this->txtUser->TabIndex = 1;
            this->txtUser->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
            this->txtUser->ForeColor = System::Drawing::Color::White;
            // 
            // lblPass
            // 
            this->lblPass->AutoSize = true;
            this->lblPass->Location = System::Drawing::Point(24, 70);
            this->lblPass->Name = L"lblPass";
            this->lblPass->Size = System::Drawing::Size(53, 13);
            this->lblPass->TabIndex = 2;
            this->lblPass->Text = L"Password";
            this->lblPass->ForeColor = System::Drawing::Color::White;
            // 
            // txtPass
            // 
            this->txtPass->Location = System::Drawing::Point(24, 90);
            this->txtPass->Name = L"txtPass";
            this->txtPass->Size = System::Drawing::Size(200, 20);
            this->txtPass->TabIndex = 3;
            this->txtPass->UseSystemPasswordChar = true;
            this->txtPass->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
            this->txtPass->ForeColor = System::Drawing::Color::White;
            // 
            // lblVoterId
            // 
            this->lblVoterId->AutoSize = true;
            this->lblVoterId->Location = System::Drawing::Point(24, 120);
            this->lblVoterId->Name = L"lblVoterId";
            this->lblVoterId->Size = System::Drawing::Size(50, 13);
            this->lblVoterId->TabIndex = 4;
            this->lblVoterId->Text = L"Voter ID";
            this->lblVoterId->ForeColor = System::Drawing::Color::White;
            // 
            // txtVoterId
            // 
            this->txtVoterId->Location = System::Drawing::Point(24, 140);
            this->txtVoterId->Name = L"txtVoterId";
            this->txtVoterId->Size = System::Drawing::Size(200, 20);
            this->txtVoterId->TabIndex = 5;
            this->txtVoterId->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
            this->txtVoterId->ForeColor = System::Drawing::Color::White;
            // 
            // btnRegister
            // 
            this->btnRegister->Location = System::Drawing::Point(24, 180);
            this->btnRegister->Name = L"btnRegister";
            this->btnRegister->Size = System::Drawing::Size(90, 30);
            this->btnRegister->TabIndex = 6;
            this->btnRegister->Text = L"Register";
            this->btnRegister->BackColor = System::Drawing::Color::FromArgb(40, 180, 99);
            this->btnRegister->ForeColor = System::Drawing::Color::White;
            this->btnRegister->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnRegister->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
            this->btnRegister->Click += gcnew System::EventHandler(this, &RegisterVoter::btnRegister_Click);
            // 
            // btnCancel
            // 
            this->btnCancel->Location = System::Drawing::Point(134, 180);
            this->btnCancel->Name = L"btnCancel";
            this->btnCancel->Size = System::Drawing::Size(90, 30);
            this->btnCancel->TabIndex = 7;
            this->btnCancel->Text = L"Cancel";
            this->btnCancel->BackColor = System::Drawing::Color::FromArgb(45, 45, 45);
            this->btnCancel->ForeColor = System::Drawing::Color::White;
            this->btnCancel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnCancel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
            this->btnCancel->Click += gcnew System::EventHandler(this, &RegisterVoter::btnCancel_Click);
            // 
            // RegisterVoter
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::Black;
            this->ForeColor = System::Drawing::Color::White;
            this->ClientSize = System::Drawing::Size(260, 230);
            this->Controls->Add(this->btnCancel);
            this->Controls->Add(this->btnRegister);
            this->Controls->Add(this->txtVoterId);
            this->Controls->Add(this->lblVoterId);
            this->Controls->Add(this->txtPass);
            this->Controls->Add(this->lblPass);
            this->Controls->Add(this->txtUser);
            this->Controls->Add(this->lblUser);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"RegisterVoter";
            this->StartPosition = FormStartPosition::CenterParent;
            this->Text = L"Register Voter";
            this->ResumeLayout(false);
            this->PerformLayout();
        }

    private: System::Void btnRegister_Click(System::Object^ sender, System::EventArgs^ e) {
        // Validate inputs
        if (String::IsNullOrWhiteSpace(txtUser->Text) || String::IsNullOrWhiteSpace(txtPass->Text) || String::IsNullOrWhiteSpace(txtVoterId->Text)) {
            MessageBox::Show("Please fill out all fields.", "Missing Info", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        if (txtPass->Text->Length < 6) {
            MessageBox::Show("Password must be at least 6 characters.", "Weak Password", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        msclr::interop::marshal_context ctx;
        std::string nativeUser = ctx.marshal_as<std::string>(txtUser->Text);
        std::string nativePass = ctx.marshal_as<std::string>(txtPass->Text);
        std::string nativeId = ctx.marshal_as<std::string>(txtVoterId->Text);

        Filehandler fh;
        if (fh.checkusernameExist(nativeUser)) {
            MessageBox::Show("Username already exists. Choose a different username.", "Duplicate", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        if (fh.savevoter(nativeUser, nativePass, nativeId)) {
            MessageBox::Show("Registration successful! You can now login.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
            this->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->Close();
            return;
        }

        MessageBox::Show("Registration failed due to file error.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }

    private: System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e) {
        this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
        this->Close();
    }
    };

}
