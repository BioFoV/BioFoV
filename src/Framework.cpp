#include "Framework.hpp"

int main(){
	Video* vid = new Video("/home/miguel/Tese/Code/Cpp/cam1.avi");
	
	cv::namedWindow("Frame", WIN_FLAGS);
	cv::Mat frame;
	vid->bgSubInit(2000, 50, false);
	while(vid->get_frame(frame)){
		cv::imshow("Frame",vid->bg->Contours(frame));
		cv::waitKey(5);
	}
	
	
	return 0;
}
