#include <iostream>
using namespace std;

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

#include "StuckTubesConfig.h"

int main(int argc, char* argv[])
{
    cout << "StuckTubes v" << VERSION_MAJOR << "." << VERSION_MINOR << endl;

    VideoCapture webcam(0);
    if (!webcam.isOpened())
    {
        cout << "Could not open webcam stream.\n" << endl;
        return -1;
    }

    Mat frame;
    //namedWindow("Background Model", 1);
    //namedWindow("Foreground Mask", 1);
    namedWindow("Webcam Test", 1);
    while (waitKey(10) < 0)
    {
        webcam >> frame;
        //imshow("Background Model", bgModel);
        //imshow("Foreground Mask", fgMask);
        imshow("Webcam Test", frame);
    }

    return 0;
}
