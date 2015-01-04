#include <iostream>
#include <sstream>
using namespace std;

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

#include "StuckTubesConfig.h"

#define CONTOUR_AREA_THRESHOLD 250

int main(int argc, char* argv[])
{
    cout << "StuckTubes v" << VERSION_MAJOR << "." << VERSION_MINOR << endl;

    if (argc < 2)
    {
        cout << "Not enough arguments." << endl;
        return -1;
    }

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
    Mat blurredFrame;
    Mat fgMask;
    Mat contourFrame;
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

    namedWindow("Raw Footage", 1);
    namedWindow("Filled Contours", 1);
   
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    while (waitKey(10) < 0)
    {
        videoStream >> frame;

        pyrDown(frame, frame);
        pyrDown(frame, frame);

        cvtColor(frame, frame, COLOR_BGR2HSV);

        GaussianBlur(frame, blurredFrame, Size(5, 5), 50, 2);

        pKNN->apply(blurredFrame, fgMask);
        fgMask.copyTo(contourFrame);

        findContours(fgMask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE,
                     Point(0, 0));

        //calculate moments on the contours while the frame is still binary
        //Moments contourMoments = moments(contours, true);
        
        cvtColor(contourFrame, contourFrame, COLOR_GRAY2BGR);

        for (int ii = 0; ii < contours.size(); ++ii)
        {
            if (contourArea(contours[ii]) > CONTOUR_AREA_THRESHOLD)
            {
                //draw the contour in blue
                drawContours(contourFrame, contours, ii, Scalar(255, 0, 0), FILLED, 8, hierarchy, 0, Point());
                //draw the centroid in green
                Moments contourMoments = moments(contours[ii]);
                double centroidX = contourMoments.m10 / contourMoments.m00;
                double centroidY = contourMoments.m01 / contourMoments.m00;
                circle(contourFrame, Point((int)centroidX, (int)centroidY), 3, Scalar(0, 255, 0));
            }
        }

        imshow("Raw Footage", frame);
        imshow("Filled Contours", contourFrame);
     }

    videoStream.release();
    return 0;
}
