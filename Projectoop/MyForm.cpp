
#include "MyForm.h"
//hbdhduwdhduh
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(cli::array<String^>^ args)
{
    try
    {
        // Enable visual styles for the application
        Application::EnableVisualStyles();
        Application::SetCompatibleTextRenderingDefault(false);

        // Instantiate and run the main form
        Projectoop::MyForm mainForm;
        Application::Run(% mainForm);
    }
    catch (Exception^ ex)
    {
        // Catch any unhandled exceptions and display a message box
        MessageBox::Show(
            "An unexpected error occurred: " + ex->Message,
            "Critical Error",
            MessageBoxButtons::OK,
            MessageBoxIcon::Error
        );
    }

    return 0;
}