#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
using namespace std;

string readQRCode(const string & imagePath) {
    Mat img = imread(imagePath);
    QRCodeDetector qrDecoder;
    string data = qrDecoder.detectAndDecode(img);
    return data;
}