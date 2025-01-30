#include "Main.h"
#include "login_panel.h"
#include "scan_panel.h"

wxDEFINE_EVENT(wxEVT_SHOW_SCAN_PANEL, wxCommandEvent);

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Secure App", wxDefaultPosition, wxSize(800, 600)) {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    loginPanel = new LoginPanel(this);
    scanPanel = new ScanPanel(this);
    scanPanel->Hide();

    mainSizer->Add(loginPanel, 1, wxEXPAND | wxALL, 10);
    mainSizer->Add(scanPanel, 2, wxEXPAND | wxALL, 10);

    SetSizer(mainSizer);

}

void MainFrame::ShowScanPanel() {
    loginPanel->Hide();
    scanPanel->Show();
    Layout();
}

bool MainApp::OnInit() {
    MainFrame* mainFrame = new MainFrame();
    mainFrame->Show();
    return true;
}

wxIMPLEMENT_APP(MainApp);
