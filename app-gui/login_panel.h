#pragma once
#include <wx/wx.h>

class LoginPanel : public wxPanel {
public:
    LoginPanel(wxWindow* parent);

private:
    wxTextCtrl* usernameField;
    wxTextCtrl* passwordField;
    wxButton* loginButton;

    void OnLogin(wxCommandEvent& event);
};
