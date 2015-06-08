This project has been made on Linux by Christiaan Peters.
Furthermore, OpenCV is needed to make/run this application.

to build this application, go into the "build" folder and open a console in there.
then type the following commands:
cmake ..
make

to execute the actual application, run the following command while still in the "build" folder:
./TrackLanes

however, for this program to actually work, make sure that the video is in the "Minor VIS" folder.
Furthermore, make sure the name of the video is "lanetrack.avi". Else it won't work.

I placed comments in the code to make clear what functions are doing.

It currently shows 2 frames, one frame with the image from the video and tracking the lanes + showing orbs on the traffic signs.
The other frame shows the blobs that get detected whenever a sign is detected