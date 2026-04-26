
#pragma once
#include "Backend.h"
#include "forgetpassword.h" // Add this line
#include <msclr\marshal_cppstd.h> 

using namespace System;
using namespace System::Windows::Forms;

namespace Projectoop {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ txtUsername;
	private: System::Windows::Forms::TextBox^ txtPassword;
	private: System::Windows::Forms::Button^ btnLogin;
	private: System::Windows::Forms::LinkLabel^ linkForgetPassword;

	protected:

	protected:

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->txtUsername = (gcnew System::Windows::Forms::TextBox());
			this->txtPassword = (gcnew System::Windows::Forms::TextBox());
			this->btnLogin = (gcnew System::Windows::Forms::Button());
			this->linkForgetPassword = (gcnew System::Windows::Forms::LinkLabel());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Location = System::Drawing::Point(184, 45);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(53, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"username";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(185, 117);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(52, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"password";
			// 
			// txtUsername
			// 
			this->txtUsername->Location = System::Drawing::Point(169, 65);
			this->txtUsername->Name = L"txtUsername";
			this->txtUsername->Size = System::Drawing::Size(100, 20);
			this->txtUsername->TabIndex = 5;
			// 
			// txtPassword
			// 
			this->txtPassword->Location = System::Drawing::Point(169, 145);
			this->txtPassword->Name = L"txtPassword";
			this->txtPassword->Size = System::Drawing::Size(100, 20);
			this->txtPassword->TabIndex = 6;
			this->txtPassword->UseSystemPasswordChar = true;
			// 
			// btnLogin
			// 
			this->btnLogin->Location = System::Drawing::Point(187, 202);
			this->btnLogin->Name = L"btnLogin";
			this->btnLogin->Size = System::Drawing::Size(75, 23);
			this->btnLogin->TabIndex = 7;
			this->btnLogin->Text = L"Login";
			this->btnLogin->UseVisualStyleBackColor = true;
			this->btnLogin->Click += gcnew System::EventHandler(this, &MyForm::btnLogin_Click);
			// 
			// linkForgetPassword
			// 
			this->linkForgetPassword->AutoSize = true;
			this->linkForgetPassword->Location = System::Drawing::Point(302, 173);
			this->linkForgetPassword->Name = L"linkForgetPassword";
			this->linkForgetPassword->Size = System::Drawing::Size(82, 13);
			this->linkForgetPassword->TabIndex = 8;
			this->linkForgetPassword->TabStop = true;
			this->linkForgetPassword->Text = L"forget password";
			this->linkForgetPassword->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MyForm::linkForgetPassword_LinkClicked);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->ClientSize = System::Drawing::Size(480, 326);
			this->Controls->Add(this->linkForgetPassword);
			this->Controls->Add(this->btnLogin);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->txtUsername);
			this->Controls->Add(this->txtPassword);
			this->Controls->Add(this->label1);
			this->Name = L"MyForm";
			this->Text = L"Username";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void btnLogin_Click(System::Object^ sender, System::EventArgs^ e) {
		// 1. Check if the textboxes are empty
		if (String::IsNullOrWhiteSpace(txtUsername->Text) || String::IsNullOrWhiteSpace(txtPassword->Text)) {
			MessageBox::Show("Please enter both username and password.", "Missing Info", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		// 2. Convert standard GUI strings (System::String^) into C++ strings (std::string)
		msclr::interop::marshal_context context;
		std::string nativeUser = context.marshal_as<std::string>(txtUsername->Text);
		std::string nativePass = context.marshal_as<std::string>(txtPassword->Text);

		// 3. Connect to your Backend code
		Filehandler fh;
		std::string foundId;
		bool foundVoted = false;

		// 4. Validate the user!
		if (fh.validateVoter(nativeUser, nativePass, foundId, foundVoted)) {
			MessageBox::Show("Login Successful!", "Welcome", MessageBoxButtons::OK, MessageBoxIcon::Information);

			// Later, you can add code here to open a Dashboard Form and hide this login screen.
		}
		else {
			MessageBox::Show("Invalid username or password.", "Login Failed", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
		   //private: System::Void linkForgetPassword_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {

		   //	// Hide the login screen
		   //	this->Hide();

		   //	// Open the Forget Password Form
		   //	ForgetPasswordForm^ fpForm = gcnew ForgetPasswordForm();
		   //	fpForm->ShowDialog(); // Waits here until the user closes the forget password window

		   //	// Show the login screen again after they finish
		   //	this->Show();
		   //}
	private: System::Void linkForgetPassword_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {

		// Hide the login screen
		this->Hide();

		// Open the Forget Password Form
		Projectoop::forgetpassword^ fpForm = gcnew Projectoop::forgetpassword(); // <--- Add Projectoop:: here
		fpForm->ShowDialog(); // Waits here until the user closes the forget password window

		// Show the login screen again after they finish
		this->Show();
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
};
}