#include "Framework.hpp"

int main(){
	Video* vid = new Video("/home/miguel/Tese/Code/Cpp/cam1.avi");
	
	cv::namedWindow("Frame", WIN_FLAGS);
	cv::Mat frame;
	while(vid->get_frame(frame)){
		cv::imshow("Frame",frame);
		cv::waitKey(5);
	}
	
	
	return 0;
}
