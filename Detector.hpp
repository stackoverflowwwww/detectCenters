#ifndef DETECTOR_HPP
#define DETECTOR_HPP
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

class Detector
{
    Mat _img;
    vector<Point> _points;
public:
    Detector();
    void set_img(Mat& img);
    vector<Point> detect();
    void print();
};

#endif // DETECTOR_HPP
