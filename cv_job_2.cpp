#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
    string way = "krugi.jpg";

    Mat img_show = imread(way, 1);

    if (img_show.empty()) {
        cout << "nothing!" << endl;
        return 0;
    }
    else {
        cout << "norm" << endl;
    }

    Mat gray;
    Mat new_img;
    Mat gauss;

    namedWindow("1", 1);

    cvtColor(img_show, gray, COLOR_BGR2GRAY, 0);
    GaussianBlur(gray, gauss, Size(5, 5), 0);
    Canny(gauss, new_img, 50, 200, 3);

    Mat img_copy = img_show.clone();

    vector<Vec4i> linesP;
    HoughLinesP(new_img, linesP, 1, CV_PI / 180, 50, 50, 10);
    for (size_t i = 0; i < linesP.size(); i++)
    {
        Vec4i l = linesP[i];
        line(img_copy, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
    }
    vector<Vec3f> circles;
    HoughCircles(new_img, circles, HOUGH_GRADIENT, 1, new_img.rows / 40, 100, 50, 10, 200);
    for (size_t i = 0; i < circles.size(); i++) {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        circle(img_copy, center, radius, Scalar(0, 255, 0), 2, 8, 0);
    }

    imshow("1", img_copy);
    imshow("2", gray);
    imshow("3", new_img);

    waitKey(0);

    return 0;
}
