#include <iostream>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <direct.h>

int countFiles = 1;
std::string directory = "files_video";

void CreateDirectory() {
	_mkdir((char*)&directory);
}

void WriteImage(cv::Mat frame) {
	
	std::string nameFile = "frame.jpg";
	std::string fileTemp = directory + "/" + std::to_string(countFiles) + nameFile;
	cv::imwrite(fileTemp, frame);
	countFiles++;
}

void RunVideo(std::string fileName) {
	int fps_camera;
	cv::Mat _frame;
    cv::VideoCapture capture;
    capture.open(fileName);
    if (!capture.isOpened()) {
        std::cout << "Unable to open video file: " << fileName << std::endl;
        return;
    }

	fps_camera = (int)(capture.get(cv::CAP_PROP_FPS));

	while (true) {
		if (!capture.read(_frame)) {
			std::cout << "Unable to read next frame." << std::endl;
			std::cout << "Exiting..." << std::endl;
			break;
		}
		else {
			cv::imshow(fileName, _frame);
			WriteImage(_frame);
			if (cv::waitKey(1000 / fps_camera) >= 0) {
				break;
			}
		}
	}
	capture.release();
}

int main(int argc, char** argv)
{
    char* fileVideo = argv[1];

    if (argc != 2)
    {
        printf(" Set file video, please \n ");
        return -1;
    }
	CreateDirectory();
	RunVideo(fileVideo);

    return 0;
    
}

