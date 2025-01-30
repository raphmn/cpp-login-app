#pragma once
#include <wx/wx.h>

class LoginPanel;
class ScanPanel;

class MainFrame : public wxFrame {
public:
    MainFrame();

private:
    LoginPanel* loginPanel;
    ScanPanel* scanPanel;

    void ShowScanPanel();
};

class MainApp : public wxApp {
public:
    virtual bool OnInit() override;
};

wxDECLARE_EVENT(wxEVT_SHOW_SCAN_PANEL, wxCommandEvent);
