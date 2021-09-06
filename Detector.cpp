#include "Detector.hpp"

Detector::Detector()
{

}
void Detector::set_img(Mat& img){
    img.copyTo(_img);
}
vector<Point> Detector::detect(){
    /*
     * 预处理图片，检测出边缘
    */
    Mat imgGray,imgBlur,imgCanny,imgDil;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    cvtColor(_img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
    Canny(imgBlur, imgCanny, 25, 75);
    dilate(imgCanny, imgDil, kernel);


    /*
     * 提取轮廓和顶点，根据顶点计算中心坐标
    */
    vector<vector<Point>> contours; //轮廓
    vector<Vec4i> hierarchy;
    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    vector<vector<Point>> conPoly(contours.size()); //顶点
    float peri; //轮廓的周长
    _points.resize(3); //3个中心坐标
    for (int i = 0; i < contours.size(); i++)
    {
        peri = arcLength(contours[i], true);
        approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true); //找出图形的顶点
        Point p(0,0); //中心点
        for(Point& pt:conPoly[i]){
            p.x+=pt.x;
            p.y+=pt.y;
        }
        p.x/=conPoly[i].size();
        p.y/=conPoly[i].size();
        if(conPoly[i].size()>4){ //圆形
            _points[0]=p;
        }else if(conPoly[i].size()==4){ //矩形
            _points[1]=p;
        }else if(conPoly[i].size()==3){ //三角形
            _points[2]=p;
        }
        circle(_img,p,6,Scalar(128,0,128),FILLED); //显示出每个中心点
    }
    imshow("image with centers of the objects",_img);
    return _points;
}
void Detector::print(){ //在控制台输出中心点
    string shapes[]={"circle","rectangle","triangle"};
    for (int i=0;i<3;i++) {
        cout<<"The center of "+shapes[i]+" is: ("<<_points[i].x<<","<<_points[i].y<<")\n";
    }
}
