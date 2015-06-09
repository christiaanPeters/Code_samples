#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;

#define Threshold 75

class RoadWatcher
{
public:
	RoadWatcher();
	Mat Calculate_And_Draw_RoadLines(Mat frame);
	Mat Detect_And_Draw_Traffic_Signs(Mat frame);

private:
	int previousleftLaneEdge;
	Scalar lowestThreshold;
	Scalar highestThreshold;
	SimpleBlobDetector detector;
	Mat bitwise_And(Mat hueg, Mat probablisticHueg);
	Mat Draw_RoadLines_On_Matrix(Mat originalFrame, Mat linesMatrix, int frameLocation);
	Mat Draw_HoughLines(Mat source, vector<Vec2f> lines);
	Mat Draw_Probablistic_HoughLines(Mat source, vector<Vec4i> lines);

};