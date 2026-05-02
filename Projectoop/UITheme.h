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
                    btn->BackColor = Color::FromArgb(0, 150, 136); // Attractive Teal
                    btn->ForeColor = Color::White;
                    btn->Font = gcnew Drawing::Font("Segoe UI", 10.0f, FontStyle::Bold);
                    btn->Cursor = Cursors::Hand;
                }
                else
                {
                    // For labels, checkboxes etc., apply white forecolor for contrast against dark background
                    if (c->GetType() == Label::typeid || c->GetType() == CheckBox::typeid)
                    {
                        c->ForeColor = Color::White;
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
            form->BackColor = Color::FromArgb(43, 48, 53); // Attractive deep dark slate base
            form->ForeColor = Color::White;
            ApplyColorToControls(form);
        }
    };
}
