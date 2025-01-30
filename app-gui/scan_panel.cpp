#include "scan_panel.h"
#include <opencv2/opencv.hpp>

ScanPanel::ScanPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY) {
    wxBoxSizer* vSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* infoText = new wxStaticText(this, wxID_ANY, "Scan your QR Code:");
    vSizer->Add(infoText, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(vSizer);
    StartCameraScan();
}

void ScanPanel::StartCameraScan() {
    cv::VideoCapture camera(0);
    if (!camera.isOpened()) {
        wxMessageBox("Could not open camera", "Error", wxOK | wxICON_ERROR);
        return;
    }

    cv::Mat frame;
    cv::QRCodeDetector detector;

    while (true) {
        camera >> frame;
        std::string qrData = detector.detectAndDecode(frame);

        if (!qrData.empty()) {
            wxMessageBox("Connexion réussie!", "Success", wxOK | wxICON_INFORMATION);
            camera.release();
            return;
        }

        cv::imshow("Scan QR Code", frame);
        if (cv::waitKey(30) >= 0) break;
    }

    camera.release();
    cv::destroyAllWindows();
}
