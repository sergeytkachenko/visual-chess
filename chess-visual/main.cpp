#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core.hpp>
#include <math.h>

#include <iostream>
#include <stdio.h>

#define PI 3.14159265

using namespace cv;
using namespace std;


int main(int ac, char** av) {
    string example = "/Users/s/Documents/c++/chess-visual/chess-visual/images/example.jpg";
    string example2 = "/Users/s/Documents/c++/chess-visual/chess-visual/images/example2.jpg";
    string example3 = "/Users/s/Documents/c++/chess-visual/chess-visual/images/example3.jpg";
    string chessboard = "/Users/s/Documents/c++/chess-visual/chess-visual/images/chessboard2.jpg";
    string chessbig = "/Users/s/Documents/c++/chess-visual/chess-visual/images/chessbig.jpg";
    string chessboard2d = "/Users/s/Documents/c++/chess-visual/chess-visual/images/chessboard2d.jpg";
    Mat gray;
    Mat image = imread(chessbig);
    GaussianBlur(image, image, Size(5, 5), 0);
    cvtColor(image, gray, CV_RGB2GRAY);
    
    /*Mat result;
    
    Mat image = imread(chessboard);
    cvtColor(image, image, CV_RGB2GRAY);
    GaussianBlur(image, image, Size(1,1), 0);
    
    Laplacian(image, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);
    convertScaleAbs(dst, dst);
    //dilate(dst, dst, Mat(), Point(-1, -1));
    //cornerHarris(image, dst, 7, 15, 0.05);
    //normalize(dst, dst, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    convertScaleAbs(dst, dst);
    dilate(dst, dst, Mat(), Point(-1, -1));
    
    double thresh = 110;
    double maxValue = 200;
    threshold(dst, result, thresh, maxValue, THRESH_BINARY);
    
    imshow("result", result);
    imshow("dst", dst);
    imshow("image", image);*/
    
    // Shi-Tomasi corner detector
    
    int maxCorners = 800;
    int maxTrackbar = 100;
    
    RNG rng(12345);
    vector<Point2f> corners;
    double qualityLevel = 0.01;
    double minDistance = 20;
    int blockSize = 3;
    bool useHarrisDetector = true;
    double k = 0.1;
    
    goodFeaturesToTrack(gray, corners, maxCorners, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k);
    cout<<"** Number of corners detected: "<<corners.size()<<endl;
    
    int r = 10;
    for( int i = 0; i < corners.size(); i++ ) {
        circle(image, corners[i], r, Scalar(rng.uniform(0,255), rng.uniform(0,255), rng.uniform(0,255)), -1, 8, 0);
    }
    
    imshow("image", image);
    
    waitKey(0);
    return 0;
}