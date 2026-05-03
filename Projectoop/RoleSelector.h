
#pragma once
#include "MyForm.h"
#include "AdminLogin.h"
#include "VoterChoice.h"
#include "RegisterVoter.h"
#include "UITheme.h"

namespace Projectoop {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class RoleSelector : public System::Windows::Forms::Form
    {
    public:
        RoleSelector(void)
        {
            InitializeComponent();
            UITheme::ApplyTheme(this);
        }

    protected:
        ~RoleSelector()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Button^ btnVoter;
        System::Windows::Forms::Button^ btnAdmin;
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->btnVoter = (gcnew System::Windows::Forms::Button());
            this->btnAdmin = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();
            // 
            // btnVoter
            // 
            this->btnVoter->Location = System::Drawing::Point(60, 80);
            this->btnVoter->Name = L"btnVoter";
            this->btnVoter->Size = System::Drawing::Size(280, 60);
            this->btnVoter->TabIndex = 0;
            this->btnVoter->Text = L"Voter";
            this->btnVoter->BackColor = System::Drawing::Color::FromArgb(40, 180, 99);
            this->btnVoter->ForeColor = System::Drawing::Color::White;
            this->btnVoter->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnVoter->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
            this->btnVoter->Click += gcnew System::EventHandler(this, &RoleSelector::btnVoter_Click);
            // 
            // btnAdmin
            // 
            this->btnAdmin->Location = System::Drawing::Point(60, 170);
            this->btnAdmin->Name = L"btnAdmin";
            this->btnAdmin->Size = System::Drawing::Size(280, 60);
            this->btnAdmin->TabIndex = 1;
            this->btnAdmin->Text = L"Admin";
            this->btnAdmin->BackColor = System::Drawing::Color::FromArgb(40, 180, 99);
            this->btnAdmin->ForeColor = System::Drawing::Color::White;
            this->btnAdmin->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnAdmin->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
            this->btnAdmin->Click += gcnew System::EventHandler(this, &RoleSelector::btnAdmin_Click);
            // 
            // RoleSelector
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::Black;
            this->ForeColor = System::Drawing::Color::White;
            this->ClientSize = System::Drawing::Size(400, 320);
            this->Controls->Add(this->btnAdmin);
            this->Controls->Add(this->btnVoter);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"RoleSelector";
            this->StartPosition = FormStartPosition::CenterScreen;
            this->Text = L"Select Role";
            this->ResumeLayout(false);
        }

    private: System::Void btnVoter_Click(System::Object^ sender, System::EventArgs^ e) {
        // Hide this selector, open the existing MyForm for voter, then close selector
        this->Hide();

        // Show a nicer modal dialog that asks user to Login or Register
        Projectoop::VoterChoice^ choice = gcnew Projectoop::VoterChoice();
        System::Windows::Forms::DialogResult result = choice->ShowDialog();

        if (result == System::Windows::Forms::DialogResult::Yes) {
            // Open the login form (MyForm)
            Projectoop::MyForm^ voterForm = gcnew Projectoop::MyForm();
            voterForm->ShowDialog(); // modal; returns when MyForm is closed
        }
        else if (result == System::Windows::Forms::DialogResult::No) {
            // Open RegisterVoter form
            Projectoop::RegisterVoter^ regForm = gcnew Projectoop::RegisterVoter();
            System::Windows::Forms::DialogResult regResult = regForm->ShowDialog();
            if (regResult == System::Windows::Forms::DialogResult::OK) {
                // After successful registration, open login form
                Projectoop::MyForm^ voterForm = gcnew Projectoop::MyForm();
                voterForm->ShowDialog();
            }
        }
        else {
            // User cancelled, show selector again
            this->Show();
            return;
        }

        this->Close();
    }

    private: System::Void btnAdmin_Click(System::Object^ sender, System::EventArgs^ e) {
        // Hide the selector, open the AdminLogin form
        this->Hide();

        Projectoop::AdminLogin^ adminForm = gcnew Projectoop::AdminLogin();
        adminForm->ShowDialog(); // modal; returns when AdminLogin is closed

        this->Close();
    }
    };
}
