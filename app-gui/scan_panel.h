#pragma once
#include <wx/wx.h>

class ScanPanel : public wxPanel {
public:
    ScanPanel(wxWindow* parent);
    void StartCameraScan();
};
