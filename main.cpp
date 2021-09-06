#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "Detector.hpp"
using namespace std;
using namespace cv;

int main()
{
    Detector dector;
    string path="E:\\C++Projects\\openCV\\detectCenters\\images\\task.png"; //图片路径
    Mat img=imread(path);
    dector.set_img(img);
    dector.detect();
    dector.print();
    waitKey(0);
}
