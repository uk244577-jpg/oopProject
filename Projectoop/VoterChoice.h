#pragma once
#include "UITheme.h"
namespace Projectoop {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class VoterChoice : public System::Windows::Forms::Form
    {
    public:
        VoterChoice(void)
        {
            InitializeComponent();
            UITheme::ApplyTheme(this);
        }

    protected:
        ~VoterChoice()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Button^ btnLogin;
        System::Windows::Forms::Button^ btnRegister;
        System::Windows::Forms::Button^ btnCancel;
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->btnLogin = (gcnew System::Windows::Forms::Button());
            this->btnRegister = (gcnew System::Windows::Forms::Button());
            this->btnCancel = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();
            // 
            // btnLogin
            // 
            this->btnLogin->Location = System::Drawing::Point(20, 70);
            this->btnLogin->Name = L"btnLogin";
            this->btnLogin->Size = System::Drawing::Size(100, 30);
            this->btnLogin->TabIndex = 0;
            this->btnLogin->Text = L"Login";
            this->btnLogin->BackColor = System::Drawing::Color::FromArgb(40, 180, 99);
            this->btnLogin->ForeColor = System::Drawing::Color::White;
            this->btnLogin->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnLogin->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
            this->btnLogin->Click += gcnew System::EventHandler(this, &VoterChoice::btnLogin_Click);
            // 
            // btnRegister
            // 
            this->btnRegister->Location = System::Drawing::Point(140, 70);
            this->btnRegister->Name = L"btnRegister";
            this->btnRegister->Size = System::Drawing::Size(100, 30);
            this->btnRegister->TabIndex = 1;
            this->btnRegister->Text = L"Register";
            this->btnRegister->BackColor = System::Drawing::Color::FromArgb(40, 180, 99);
            this->btnRegister->ForeColor = System::Drawing::Color::White;
            this->btnRegister->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnRegister->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
            this->btnRegister->Click += gcnew System::EventHandler(this, &VoterChoice::btnRegister_Click);
            // 
            // btnCancel
            // 
            this->btnCancel->Location = System::Drawing::Point(260, 70);
            this->btnCancel->Name = L"btnCancel";
            this->btnCancel->Size = System::Drawing::Size(75, 30);
            this->btnCancel->TabIndex = 2;
            this->btnCancel->Text = L"Cancel";
            this->btnCancel->BackColor = System::Drawing::Color::FromArgb(45, 45, 45);
            this->btnCancel->ForeColor = System::Drawing::Color::White;
            this->btnCancel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnCancel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
            this->btnCancel->Click += gcnew System::EventHandler(this, &VoterChoice::btnCancel_Click);
            // 
            // VoterChoice
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::Black;
            this->ForeColor = System::Drawing::Color::White;
            this->ClientSize = System::Drawing::Size(360, 130);
            this->Controls->Add(this->btnCancel);
            this->Controls->Add(this->btnRegister);
            this->Controls->Add(this->btnLogin);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"VoterChoice";
            this->StartPosition = FormStartPosition::CenterParent;
            this->Text = L"Voter - Choose Action";
            // Add a label for instructions
            System::Windows::Forms::Label^ lbl = gcnew System::Windows::Forms::Label();
            lbl->AutoSize = true;
            lbl->Location = System::Drawing::Point(20, 20);
            lbl->Size = System::Drawing::Size(320, 30);
            lbl->Text = L"Do you already have an account? Choose Login to sign in, or Register to create one.";
            lbl->ForeColor = System::Drawing::Color::White;
            this->Controls->Add(lbl);

            this->ResumeLayout(false);
            this->PerformLayout();
        }

    private: System::Void btnLogin_Click(System::Object^ sender, System::EventArgs^ e) {
        this->DialogResult = System::Windows::Forms::DialogResult::Yes; // Yes = Login
        this->Close();
    }

    private: System::Void btnRegister_Click(System::Object^ sender, System::EventArgs^ e) {
        this->DialogResult = System::Windows::Forms::DialogResult::No; // No = Register
        this->Close();
    }

    private: System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e) {
        this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
        this->Close();
    }
    };
}
