#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <math.h>

#include <iostream>
#include <stdio.h>

#define PI 3.14159265

using namespace cv;
using namespace std;

float angleBetween(const Point a, const Point b) {
    float angle = atan2(a.y - b.y, a.x - b.x);
    return (angle + 90);
}

double getSideLength(float diagonale) {
    double a = diagonale * diagonale / 2;
    return sqrt(a);
}

Point2f getEndPoint(Point2f p, float angle, float len) {
    double x = p.x + len * cos(angle);
    double y = p.y + len * sin(angle);
    Point2f p2 = Point2f(x, y);
    return p2;
}

vector<Point2f> findDiagonale(string imagePath) {
    Mat3b hsv;
    Mat image = imread(imagePath);
    cvtColor(image, hsv, COLOR_BGR2HSV);
    for(int y=0; y < hsv.rows; y++) {
        for(int x=0; x < hsv.cols; x++) {
            Vec3b color = hsv.at<Vec3b>(Point(x,y));
            
            if(color[0] < 2 && color[1] > 250 && color[2] > 250) {
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
                
            } else {
                color.val[0] = 0;
                color.val[1] = 0;
                color.val[2] = 0;
            }
            
            image.at<Vec3b>(Point(x,y)) = color;
        }
    }
    
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    Canny(gray, gray, 100, 100 * 2, 3);
    findContours(gray, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    vector<Moments> mu(contours.size());
    for( int i = 0; i < contours.size(); i++ ) {
        mu[i] = moments( contours[i], false );
    }
    vector<Point2f> mc(contours.size());
    for( int i = 0; i < contours.size(); i++) {
        mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00 );
    }
    return mc;
}

int main(int ac, char** av) {
    string img = "/Users/s/IdeaProjects/visual-chess/src/main/resources/images/example2.jpg";
    vector<Point2f> points = findDiagonale(img);
    Mat image = imread(img);
    Point2f a = points.at(0);
    Point2f b = points.at(2);
    double res = cv::norm(a - b);
    float angle = angleBetween(a, b);
    double sideLength = getSideLength(res);
    Point2f endPoint = getEndPoint(a, angle, sideLength);
    Mat drawing = Mat::zeros(image.size(), CV_8UC3);
    RNG rng(12345);
    Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255));
    for( int i = 0; i < points.size(); i++ ) {
        circle(image, points[i], 1, color, -1, 1, 0);
    }
    circle(image, endPoint, 4, color, -1, 1, 0);
    
    cv::Point2f source_points[4];
    cv::Point2f dest_points[4];
    source_points[0] = points.at(0);
    source_points[1] = points.at(2);
    source_points[2] = points.at(4);
    source_points[3] = points.at(6);
    
    dest_points[0] = points.at(0);
    dest_points[1] = points.at(2);
    dest_points[2] = points.at(4);
    dest_points[3] = points.at(6);
    
    Mat transform_matrix = getPerspectiveTransform(source_points, dest_points);
    cv::warpPerspective(image, image, transform_matrix, cv::Size(1698, 1200));
    
    imshow("image", image);
    waitKey(0);
    return 0;
}