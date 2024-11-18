#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int MINIMUM_CONTOUR_AREA = 3000;
int FRAME_DELAY = 20; 
int H_MIN = 0, H_MAX = 179;
int S_MIN = 140, S_MAX = 255;
int V_MIN = 0, V_MAX = 200;

double FRAME_DILATION_SCALE = 0.5;

void showContours(Mat input, Mat output){
    vector<vector<Point>>contours;
    findContours(input, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    int minX, minY, maxX, maxY;
    minX = minY = INT32_MAX;
    maxX = maxY = 0;

    for(vector<Point>contour : contours){
        
        int area = contourArea(contour);

        if(area >= MINIMUM_CONTOUR_AREA){
            minX = minY = INT32_MAX;
            maxX = maxY = 0;
            for(Point p : contour){
                maxX = max(maxX, p.x);
                minX = min(minX, p.x);
                maxY = max(maxY, p.y);
                minY = min(minY, p.y);
            }

            int offset = 5;
            putText(output, "Object", Point(minX-offset-3, minY-offset-3), FONT_HERSHEY_PLAIN, 2, Scalar(255,0,255), 3);
            rectangle(output, Point(minX-offset, minY-offset), Point(maxX+offset, maxY+offset), Scalar(255, 0, 255), 2);
        }
    }
}


int main(int argc, char* argv[]){
    
    string path;

    if(argc > 1)path = argv[1];
    else path = "shape.mp4";

    VideoCapture cap(path);

    bool showMask = 0;
    if(argc > 2 && string(argv[2])=="--mask")showMask = 1;

    Mat frame, frameHsv, mask;

    while(true){
        try{
            cap.read(frame);
            
            resize(frame, frame, Size(0,0), FRAME_DILATION_SCALE, FRAME_DILATION_SCALE);
            cvtColor(frame, frameHsv, COLOR_BGR2HSV);

            Scalar lowerBound(H_MIN, S_MIN, V_MIN), upperBound(H_MAX, S_MAX, V_MAX);
            inRange(frameHsv, lowerBound, upperBound, mask);
            
            int fps = (int)cap.get(CAP_PROP_FPS);
            putText(frame, "FPS: "+to_string(fps), Point(0,40), FONT_HERSHEY_PLAIN, 2, Scalar(0,0,0), 3);
            
            showContours(mask, frame);

            if(showMask)imshow("Frame mask", mask);
            imshow(path, frame);

            waitKey(FRAME_DELAY);
        }
        catch(const exception &e){
            cap = VideoCapture(path);
        }
    }
}
