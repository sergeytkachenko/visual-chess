
#include "laplacian.hpp"

using namespace cv;
using namespace std;

int t(int ac, char** av) {
    Mat dst, dst2;
    Mat image = imread("/Users/s/IdeaProjects/visual-chess/src/main/resources/images/example.jpg");
    
    cvtColor(image, image, CV_RGB2GRAY);
    GaussianBlur(image, image, Size(3,3), 0);
    
    Laplacian(image, dst, CV_16S, 1, 20, 0, BORDER_DEFAULT);
    Laplacian(image, dst2, CV_16S, 3, 1, 0, BORDER_DEFAULT);
    convertScaleAbs(dst, dst);
    convertScaleAbs(dst2, dst2);
    
    imshow("imageOrigin", image);
    imshow("image", dst);
    imshow("image2", dst2);
    waitKey(0);
    return 0;
}