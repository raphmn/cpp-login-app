#include "login_panel.h"
#include "auth.h"
#include "main.h"

LoginPanel::LoginPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY) {
    wxBoxSizer* vSizer = new wxBoxSizer(wxVERTICAL);
    
    wxStaticText* title = new wxStaticText(this, wxID_ANY, "Login");
    title->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    vSizer->Add(title, 0, wxALIGN_CENTER | wxALL, 10);

    usernameField = new wxTextCtrl(this, wxID_ANY);
    vSizer->Add(new wxStaticText(this, wxID_ANY, "Username"), 0, wxLEFT, 5);
    vSizer->Add(usernameField, 0, wxEXPAND | wxALL, 5);

    passwordField = new wxTextCtrl(this, wxID_ANY, "");
    vSizer->Add(new wxStaticText(this, wxID_ANY, "Password"), 0, wxLEFT, 5);
    vSizer->Add(passwordField, 0, wxEXPAND | wxALL, 5);

    loginButton = new wxButton(this, wxID_ANY, "Login");
    vSizer->Add(loginButton, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(vSizer);
    loginButton->Bind(wxEVT_BUTTON, &LoginPanel::OnLogin, this);
}

void LoginPanel::OnLogin(wxCommandEvent& event) {
    wxString username = usernameField->GetValue();
    wxString password = passwordField->GetValue();

    if (AuthenticateUser(std::string(username.mb_str()), std::string(password.mb_str()))) {
        wxCommandEvent evt(wxEVT_SHOW_SCAN_PANEL);
        wxPostEvent(GetParent(), evt);
    } else {
        wxMessageBox("Incorrect username or password!", "Error", wxOK | wxICON_ERROR);
    }
}
