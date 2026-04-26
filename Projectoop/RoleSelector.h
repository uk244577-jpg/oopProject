#pragma once
#include "MyForm.h"
#include "VoterChoice.h"
#include "RegisterVoter.h"
#include "AdminForm.h"

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
            this->btnVoter->Location = System::Drawing::Point(40, 30);
            this->btnVoter->Name = L"btnVoter";
            this->btnVoter->Size = System::Drawing::Size(120, 40);
            this->btnVoter->TabIndex = 0;
            this->btnVoter->Text = L"Voter";
            this->btnVoter->UseVisualStyleBackColor = true;
            this->btnVoter->Click += gcnew System::EventHandler(this, &RoleSelector::btnVoter_Click);
            // 
            // btnAdmin
            // 
            this->btnAdmin->Location = System::Drawing::Point(40, 90);
            this->btnAdmin->Name = L"btnAdmin";
            this->btnAdmin->Size = System::Drawing::Size(120, 40);
            this->btnAdmin->TabIndex = 1;
            this->btnAdmin->Text = L"Admin";
            this->btnAdmin->UseVisualStyleBackColor = true;
            this->btnAdmin->Click += gcnew System::EventHandler(this, &RoleSelector::btnAdmin_Click);
            // 
            // RoleSelector
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(200, 160);
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
        // Hide role selector
        this->Hide();

        // Open the Admin login form
        Projectoop::AdminForm^ adminForm = gcnew Projectoop::AdminForm();
        System::Windows::Forms::DialogResult result = adminForm->ShowDialog();

        // After admin form closes, show role selector again
        this->Show();
    }
    };
}
