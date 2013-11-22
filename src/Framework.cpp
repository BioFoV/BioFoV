#include "Framework.hpp"

int main(int argc, char ** argv){
	
	std::string filename;
	
	if (argc > 1){
		filename = argv[1];
	}
	Video* vid = new Video(filename);
	
	if (!vid->check_cap())
		return 0;
	
	cv::namedWindow("Frame", WIN_FLAGS);
	cv::Mat frame;
	vid->bgSubInit(2000, 50, false);
	while(vid->get_frame(frame)){
		cv::imshow("Frame",vid->bg->Contours(frame));
		cv::waitKey(5);
	}
	
	return 0;
}
