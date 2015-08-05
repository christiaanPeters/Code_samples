#include "RoadWatcher.hpp"
#include <stdio.h>

//the settings to define the color of the traffic signs, currently set to blue
#define ILOWH 100
#define IHIGHH 140
#define ILOWS 150
#define IHIGHS 255
#define ILOWV 50
#define IHIGHV 255

RoadWatcher::RoadWatcher()
{
  lowestThreshold = Scalar(ILOWH, ILOWS, ILOWV);
  highestThreshold = Scalar(IHIGHH, IHIGHS, IHIGHV);

  SimpleBlobDetector::Params params;

    //setting parameters for the blobdetection.
  params.minDistBetweenBlobs = 1.0f; //minimum distance between blobs to decide wether it's 1 blob or multiple
  params.filterByInertia = false;
  params.filterByConvexity = false;
  params.filterByColor = false;
  params.filterByCircularity = false;
  params.filterByArea = true;
  params.minArea = 50.0f; //minimum area to define it's a blob.

  detector = SimpleBlobDetector(params);
}

Mat RoadWatcher::bitwise_And(Mat hueg, Mat probablisticHueg)
{
	Mat BitwiseBlack;
	BitwiseBlack = hueg.clone();
	BitwiseBlack.setTo(Scalar(0,255,255));
	cv::bitwise_and(probablisticHueg, hueg, BitwiseBlack);
	return BitwiseBlack;
}

Mat RoadWatcher::Draw_RoadLines_On_Matrix(Mat originalFrame, Mat linesMatrix, int frameLocation)
{
  vector<Vec4i> linesVector;
  Mat cimg;
  Canny(linesMatrix, cimg, 50, 200, 3);
  HoughLinesP(cimg, linesVector, 1, CV_PI/180, Threshold, 50, 10);
  for (size_t j = 0; j < linesVector.size(); j++)
  {
    Vec4i l = linesVector[j];
    l[1] += frameLocation;
    l[3] += frameLocation;
    line(originalFrame, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
  }
  return originalFrame;
}

Mat RoadWatcher::Draw_HoughLines(Mat source, vector<Vec2f> lines)
{
	// draw the hough lines
    for( size_t i = 0; i < lines.size(); i++ )
    {
      float rho = lines[i][0];
      float theta = lines[i][1];
      //check wether the lines are in a certain degree before drawing them, this check doesn't work entirely according to plan.
      //In here, only the normal houglines are drawn
      if(theta > CV_PI/6 && theta < (5*CV_PI)/6)
      {
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line(source, pt1, pt2, Scalar(255,255,255), 3, CV_AA);
      }
    }
    return source;
}

Mat RoadWatcher::Draw_Probablistic_HoughLines(Mat source, vector<Vec4i> lines)
{
  //draw the probablistic houglines.
    for (size_t j = 0; j < lines.size(); j++)
    {
      Vec4i l = lines[j];
      line(source, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,255,255), 3, CV_AA);
    }
    return source;
}

Mat RoadWatcher::Calculate_And_Draw_RoadLines(Mat frame)
{
	Mat half_frame, dst, cdst, editedFrame, blackHueg, blackProb;
	int lowerFrameloc;

	editedFrame = frame.clone();
  half_frame = frame( Range( frame.rows/2 +50, frame.rows - 1 ), Range( 0, frame.cols - 1 ) );

  //copy the half frame into these 2 frames, afterwards make them completely black. So that we can use these frames to bitwise and.
  blackHueg = half_frame.clone();
  blackProb = half_frame.clone();
  blackHueg.setTo(Scalar(0,0,0));
  blackProb.setTo(Scalar(0,0,0));

  //define where the lanes should be located on the main frame.
  lowerFrameloc = frame.rows/2 +50;

    //convert the color + canny to prepare for (probablistic) houghlines
  cvtColor(dst, cdst, CV_GRAY2BGR);
  Canny(half_frame, dst, 50, 200, 3);

  threshold(dst,cdst,128,255,THRESH_BINARY_INV);
      
  vector<Vec2f> houghlines;
  vector<Vec4i> probLines;

  // detect lines
  HoughLines(dst, houghlines, 1, CV_PI/180, Threshold, 0, 0 );
  HoughLinesP(dst, probLines, 1, CV_PI/180, Threshold, 50, 10 );

  blackHueg = Draw_HoughLines(blackHueg, houghlines);
  blackProb = Draw_Probablistic_HoughLines(blackProb, probLines);
  Mat linesToDraw = bitwise_And(blackHueg, blackProb);
	Mat returner = Draw_RoadLines_On_Matrix(editedFrame, linesToDraw, lowerFrameloc);
	return returner;
}

Mat RoadWatcher::Detect_And_Draw_Traffic_Signs(Mat frame)
{
	Mat returnerFrame, imgHSV, imgThresholded; 
	returnerFrame = frame.clone();
	cvtColor(returnerFrame, imgHSV, COLOR_BGR2HSV);

	inRange(imgHSV, lowestThreshold, highestThreshold, imgThresholded); //Threshold the image

	//morphological opening (remove small objects from the foreground)
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
	dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

	//morphological closing (fill small holes in the foreground)
	dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

	//detect!
	vector<cv::KeyPoint> keypoints;
	detector.detect(imgThresholded, keypoints);
	Mat temp;
	drawKeypoints(imgThresholded, keypoints, temp, Scalar(0,0,255), 0);
	imshow("blobs", temp);

	for (int i=0; i<keypoints.size(); i++)
  	{
    	float X = keypoints[i].pt.x; 
	    float Y = keypoints[i].pt.y;
    	circle(returnerFrame, Point(X, Y), 10, Scalar(0,255,0), -1, CV_AA, 0);
  	}
  	return returnerFrame;
}