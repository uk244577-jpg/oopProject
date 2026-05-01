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

	
	public ref class forgetpassword : public System::Windows::Forms::Form
	{
	public:
		forgetpassword(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~forgetpassword()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^ txtUsername;
	private: System::Windows::Forms::Label^ txtVoterId;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Button^ btnReset;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->txtUsername = (gcnew System::Windows::Forms::Label());
			this->txtVoterId = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->btnReset = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
		
         this->txtUsername->AutoSize = true;
			this->txtUsername->Location = System::Drawing::Point(107, 24);
			this->txtUsername->Name = L"txtUsername";
			this->txtUsername->Size = System::Drawing::Size(53, 13);
			this->txtUsername->TabIndex = 0;
			this->txtUsername->Text = L"username";
			this->txtUsername->ForeColor = System::Drawing::Color::White;
			
          this->txtVoterId->AutoSize = true;
			this->txtVoterId->Location = System::Drawing::Point(110, 105);
			this->txtVoterId->Name = L"txtVoterId";
			this->txtVoterId->Size = System::Drawing::Size(43, 13);
			this->txtVoterId->TabIndex = 1;
			this->txtVoterId->Text = L"voter Id";
			this->txtVoterId->ForeColor = System::Drawing::Color::White;
		 
          this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(97, 168);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(75, 13);
			this->label3->TabIndex = 2;
			this->label3->Text = L"new password";
			this->label3->ForeColor = System::Drawing::Color::White;
		
          this->textBox1->Location = System::Drawing::Point(88, 53);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 3;
			this->textBox1->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
			this->textBox1->ForeColor = System::Drawing::Color::White;
			
         this->textBox2->Location = System::Drawing::Point(88, 131);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 20);
			this->textBox2->TabIndex = 4;
			this->textBox2->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
			this->textBox2->ForeColor = System::Drawing::Color::White;
			// 
			// textBox3
			// 
         this->textBox3->Location = System::Drawing::Point(88, 193);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 20);
			this->textBox3->TabIndex = 5;
			this->textBox3->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
			this->textBox3->ForeColor = System::Drawing::Color::White;
			// 
			// btnReset
			// 
         this->btnReset->Location = System::Drawing::Point(97, 226);
			this->btnReset->Name = L"btnReset";
			this->btnReset->Size = System::Drawing::Size(75, 23);
			this->btnReset->TabIndex = 6;
			this->btnReset->Text = L"Reset Password";
			this->btnReset->BackColor = System::Drawing::Color::FromArgb(40, 180, 99);
			this->btnReset->ForeColor = System::Drawing::Color::White;
			this->btnReset->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnReset->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->btnReset->Click += gcnew System::EventHandler(this, &forgetpassword::btnReset_Click);
			// 
			// forgetpassword
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
          this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Black;
			this->ForeColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->btnReset);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->txtVoterId);
			this->Controls->Add(this->txtUsername);
			this->Name = L"forgetpassword";
			this->Text = L"forgetpassword";
			this->Load += gcnew System::EventHandler(this, &forgetpassword::forgetpassword_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void forgetpassword_Load(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void btnReset_Click(System::Object^ sender, System::EventArgs^ e) {
		// 1. Check if the textboxes are empty
		if (String::IsNullOrWhiteSpace(textBox1->Text) ||
			String::IsNullOrWhiteSpace(textBox2->Text) ||
			String::IsNullOrWhiteSpace(textBox3->Text)) {
			MessageBox::Show("Please fill out all fields.", "Missing Info", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		// 2. Convert standard GUI strings into C++ strings
		msclr::interop::marshal_context context;
		std::string nativeUser = context.marshal_as<std::string>(textBox1->Text);
		std::string nativeId = context.marshal_as<std::string>(textBox2->Text);
		std::string nativeNewPass = context.marshal_as<std::string>(textBox3->Text);

		// 3. Connect to your Backend code
		Filehandler fh;

		// 4. Try to reset the password
		if (fh.resetPassword(nativeUser, nativeId, nativeNewPass)) {
			MessageBox::Show("Password reset successfully! You can now login.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);

			// Close the forget password window to return to the main login screen
			this->Close();
		}
		else {
			MessageBox::Show("Invalid Username or Voter ID. Please try again.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	};
}