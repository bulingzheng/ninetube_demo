#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 生成 bg.png
int main1()
{
	Mat bg(530, 910, CV_8UC1, Scalar(0));
	Mat white(110, 210, CV_8UC1, Scalar(255));

	Rect rects[9];

	rects[0] = Rect(70, 50, 210, 110);
	rects[1] = Rect(70 + 280, 50, 210, 110);
	rects[2] = Rect(70 + 560, 50, 210, 110);
	rects[3] = Rect(70, 50 + 160, 210, 110);
	rects[4] = Rect(70 + 280, 50 + 160, 210, 110);
	rects[5] = Rect(70 + 560, 50 + 160, 210, 110);
	rects[6] = Rect(70, 50 + 320, 210, 110);
	rects[7] = Rect(70 + 280, 50 + 320, 210, 110);
	rects[8] = Rect(70 + 560, 50 + 320, 210, 110);


	for (int i = 0; i < 9; i++)
	{
		white.copyTo(bg(rects[i]));
	}

	cv::imshow("bg", bg);
	imwrite("bg.png", bg);
	waitKey(0);

	return 0;
}

int main2()
{
	FileStorage fs("config.xml",FileStorage::WRITE);
	string filepath="D:\\vs2015engineer\\MINIST\\";
	fs << "filepath" << filepath;
	int maxNumber=892;
	fs << "maxNumber" << maxNumber;
	int delayTime=3000;
	fs << "delayTime" << delayTime;
	fs.release();
	return 0;
}

// 九宫格demo
int main()
{
	FileStorage fs("config.xml", FileStorage::READ);

	string filepath;

	fs["filepath"] >> filepath;

	int maxNumber;

	fs["maxNumber"] >> maxNumber;

	int delayTime;

	fs["delayTime"] >> delayTime;

	fs.release();

	Rect rects[9];

	rects[0] = Rect(70 + 0, 50, 210, 110);
	rects[1] = Rect(70 + 280 + 0, 50, 210, 110);
	rects[2] = Rect(70 + 560 + 0, 50, 210, 110);
	rects[3] = Rect(70 + 0, 50 + 160, 210, 110);
	rects[4] = Rect(70 + 280 + 0, 50 + 160, 210, 110);
	rects[5] = Rect(70 + 560 + 0, 50 + 160, 210, 110);
	rects[6] = Rect(70 + 0, 50 + 320, 210, 110);
	rects[7] = Rect(70 + 280 + 0, 50 + 320, 210, 110);
	rects[8] = Rect(70 + 560 + 0, 50 + 320, 210, 110);

	Mat bg = imread("bg.png");
	if (bg.empty()) {
		// 		cout << "当前路径下缺少 bg.png 文件！" << endl;
		// 		system("pause");
		return -1;
	}

	RNG rng;

	// 保存 1~9 这九个数字
	int aa[9];
	for (int i = 0; i < 9; i++)
		aa[i] = i + 1;

	int bb[9];

	string cc[9];

	while (true) {
		Mat bg_ = bg.clone();
		cv::imshow("九宫格demo", bg_);
		waitKey(100);

		for (int i = 0; i < 30; i++)
			swap(aa[rng.uniform(0, 9)], aa[rng.uniform(0, 9)]);

		for (int i = 0; i < 9; i++)
			bb[i] = rng.uniform(1, maxNumber);	// 编号最大的文件名

		for (int i = 0; i < 9; i++) {
			if (bb[i] < 10)
				cc[i] = "0000" + to_string(bb[i]) + ".png";
			else if (bb[i] >= 10 && bb[i] < 100)
				cc[i] = "000" + to_string(bb[i]) + ".png";
			else
				cc[i] = "00" + to_string(bb[i]) + ".png";
		}

		vector<Mat> number_mat(9);
		for (int i = 0; i < 9; i++) {
			string filename = filepath + to_string(aa[i]) + "_" + cc[i];
			Mat m = imread(filename);
			if (m.empty()) {
				// 				cout << "未找到图片文件！" << endl;
				// 				system("pause");
				return -1;
			}
			resize(m, m, Size(210, 110));
			threshold(m, m, 100, 255, THRESH_BINARY_INV);
			blur(m, m, Size(3, 3));
			number_mat[i] = m;
			// 			imshow("m", m);
			// 			waitKey(0);
		}

		for (int i = 0; i < 9; i++)
			number_mat[i].copyTo(bg_(rects[i]));

		cv::imshow("九宫格demo", bg_);
		int key = waitKey(delayTime);
		if (key == 27)
			break;
	}

	return 0;
}