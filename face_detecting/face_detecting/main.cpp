#include <iostream>
#include <opencv2/opencv.hpp>

#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace cv;


/* @ function main */
int main(int argc, char *argv[])
{
	// open the default camera
	VideoCapture cap(0);	//Webcam으로 Frame Capture를 한다.

	// check if we succeeded
	if (!cap.isOpened()) {
		cerr << "Could not open camera" << endl;
		return -1;
	}

	// create a window
	namedWindow("webcam", 1);

	// face detection configuration
	CascadeClassifier face_classifier;

	face_classifier.load("{YOUR_OPENCV_PATH}/data/haarcascades/haarcascade_frontalface_default.xml");

	Mat frame;

	for (; ; ) {
		bool frame_valid = true;

		try {

			// get a new frame from webcam
			cap >> frame;

		}
		catch (cv::Exception& e) {

			cerr << "Exception occurred. Ignoring frame... " << e.err << endl;
			frame_valid = false;

		}

		if (frame_valid) {
			try {
				// convert captured frame to gray scale & equalize
				Mat grayframe;
				cvtColor(frame, grayframe, COLOR_BGR2GRAY);
				equalizeHist(grayframe, grayframe);

				// -------------------------------------------------------------
				// face detection routine

				// a vector array to store the face found
				vector<Rect> faces;

				face_classifier.detectMultiScale(grayframe, faces,
					1.1, // increase search scale by 10% each pass
					3,   // merge groups of three detections
					//CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE,
					CASCADE_FIND_BIGGEST_OBJECT | CASCADE_SCALE_IMAGE,
					Size(30, 30)
				);
				// -------------------------------------------------------------
				// draw the results
				for (int i = 0; i < faces.size(); i++) {
					Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
					Point tr(faces[i].x, faces[i].y);

					rectangle(frame, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
				}
				// print the output
				imshow("webcam", frame);
			}
			catch (Exception& e) {
				cerr << "Exception occurred. Ignoring frame... " << e.err << endl;
			}
		}
		if (waitKey(30) >= 0) break;
	}
	// VideoCapture automatically deallocate camera object
	return 0;
}