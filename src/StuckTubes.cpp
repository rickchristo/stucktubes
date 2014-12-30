#include <iostream>
#include <sstream>
using namespace std;

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

#include "StuckTubesConfig.h"

int main(int argc, char* argv[])
{
    cout << "StuckTubes v" << VERSION_MAJOR << "." << VERSION_MINOR << endl;

    VideoCapture videoStream;
    if (argc < 3)
    {
        videoStream.open(0);
    }
    else
    {
        videoStream.open(argv[2]);
    }

    if (!videoStream.isOpened())
    {
        cout << "Could not open video stream." << endl;
        return -1;
    }

    Mat frame;
    Mat edges;
    Mat fgMask;
    Mat bgModel;
    Mat fgMask2;
    Mat bgModel2;
    istringstream ss(argv[1]);
    int history;
    if (!(ss >> history))
    {
        cout << "Bad command line input." << endl;
    }
    else if (history < 0)
    {
        cout << "Enter a history > 0." << endl;
    }
    Ptr<BackgroundSubtractorKNN> const pKNN = createBackgroundSubtractorKNN(history, 800.0, false);
    Ptr<BackgroundSubtractorKNN> const pKNN2 = createBackgroundSubtractorKNN(history/5, 800.0, false);
    //namedWindow("Background Model", 1);
    //namedWindow("Background Model 2", 1);
    namedWindow("Foreground Mask", 1);
    namedWindow("Foreground Mask 2", 1);
    //namedWindow("Webcam", 1);
    
    while (waitKey(10) < 0)
    {
        videoStream >> frame;

        pyrDown(frame, frame);
        pyrDown(frame, frame);

        //blur(frame, frame, Size(5, 5));
        //Canny(frame, edges, 0, 30, 3);

        pKNN->apply(frame, fgMask);
        //pKNN->apply(edges, fgMask);
        pKNN->getBackgroundImage(bgModel);
        pKNN2->apply(fgMask, fgMask2);
        pKNN2->getBackgroundImage(bgModel2);

        //imshow("Background Model", bgModel);
        imshow("Foreground Mask", fgMask);
        //imshow("Background Model 2", bgModel2);
        imshow("Foreground Mask 2", fgMask2);
        //imshow("Webcam", edges);
    }

    videoStream.release();
    return 0;
}
