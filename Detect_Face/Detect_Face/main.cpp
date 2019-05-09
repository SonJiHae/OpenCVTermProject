#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Point2d calc_center(Rect obj) {
	Point2d c = (Point2d)obj.size() / 2.0;
	Point2d center = (Point2d)obj.tl() + s;
	return center;
}

int main() {
	CascadeClassifier face_cascade.eyes_cascade;
	load_cascade(face_cascade, "haarcascade_frontalface_alt2.xml");
	load_cascade(eye_cascade, "haarcascade_eye.xml");

	Mat image = imread("", IMREAD_COLOR);
	CV_Assert(image.data);
	Mat gray = preprocessing(image);

	vector<Rect> faces, eyes;
	vector<Point2d> eyes_center;
	face_cascade.detectMultiScale(gray, faces, 1.1, 2, 0, Size(100, 100));

	if (faces.size() > 0) {
		eyes_cascade.detectMultiScale(gray())
	}

	return(0);
}