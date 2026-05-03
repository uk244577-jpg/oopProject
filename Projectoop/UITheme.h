#pragma once

namespace Projectoop {
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class UITheme
    {
    private:
        static void ApplyColorToControls(Control^ parent)
        {
            for each (Control^ c in parent->Controls)
            {
                if (c->GetType() == Button::typeid)
                {
                    Button^ btn = safe_cast<Button^>(c);
                    btn->FlatStyle = FlatStyle::Flat;
                    btn->FlatAppearance->BorderSize = 0;
                    btn->UseVisualStyleBackColor = false;
                    if (btn->BackColor == SystemColors::Control)
                    {
                        btn->BackColor = Color::Crimson; // Attractive Red
                    }
                    if (btn->ForeColor == SystemColors::ControlText)
                    {
                        btn->ForeColor = Color::White;
                    }
                    if (btn->Font->FontFamily->Name == "Microsoft Sans Serif")
                    {
                        btn->Font = gcnew Drawing::Font("Segoe UI", 12.0f, FontStyle::Bold);
                    }
                    btn->Cursor = Cursors::Hand;
                }
                else
                {
                    // For labels, checkboxes etc., apply white forecolor for contrast against dark background
                    if (c->GetType() == Label::typeid || c->GetType() == CheckBox::typeid)
                    {
                        c->ForeColor = Color::White;
                    }
                    if (c->BackColor == SystemColors::Control || c->BackColor == SystemColors::ControlLight || c->BackColor == SystemColors::ControlDark)
                    {
                        c->BackColor = Color::FromArgb(20, 20, 20);
                    }
                    if (c->HasChildren)
                    {
                        ApplyColorToControls(c);
                    }
                }
            }
        }

    public:
        static void ApplyTheme(Form^ form)
        {
            form->BackColor = Color::FromArgb(20, 20, 20); // Deep black background
            form->ForeColor = Color::White;
            ApplyColorToControls(form);
        }
    };
}
