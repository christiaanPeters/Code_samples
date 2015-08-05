//made by Christiaan Peters

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <stdlib.h>
#include <stdio.h>
#include "RoadWatcher.hpp"

/** @function main */
int main( int argc, char** argv )
{
  Mat frame;
  RoadWatcher watcher;

  VideoCapture cap(0); // open the default camera
  cap.open("../lanetrack.avi");
  if(!cap.isOpened())  // check if we succeeded
  {
    printf("error while trying to open the capture device!\n");
    return -1;
  }

  watcher = RoadWatcher();

  while(true)
  {
    cap >> frame; // get a new frame from camera
    Mat frameWithLines = watcher.Calculate_And_Draw_RoadLines(frame);
    Mat totalFrame = watcher.Detect_And_Draw_Traffic_Signs(frameWithLines);

    imshow("result", totalFrame);
    if(waitKey(30) >= 0) break;
  }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}