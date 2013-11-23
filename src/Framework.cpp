#include "Framework.hpp"

/*******************************************************************************
 * Main program entry point
 ******************************************************************************/
int main(int argc, char ** argv){
	
	std::string filename = parseArguments(argc, argv);
	
	
	Video* vid = new Video(filename);
	
	if (!vid->check_cap()){
		return 0;
	}
	
	cv::namedWindow("Frame", WIN_FLAGS);
	cv::Mat frame;
	vid->bgSubInit(2000, 50, false);
	while(vid->get_frame(frame)){
		vid->bg->NewFrame(frame, true, true, true);
		cv::imshow("Frame",vid->bg->Contours());
		cv::waitKey(5);
	}
	
	return 0;
}

/*******************************************************************************
 * Command line argument parser
 ******************************************************************************/
std::string parseArguments(int argc, char ** argv){
	std::string filename;
	
	if (argc < 2){
		// FIXME: RUN IN GUI MODE STRAIGHT AHEAD
		return NULL;
	}
	for (int i=1; i < argc; i++){
		if (!strcmp(argv[i],"-h") || !strcmp(argv[i],"--help")){
			std::cout << "Arguments" << std::endl;
			std::cout << "-h\t--help" << std::endl;
			std::cout << "\t Show this help" << std::endl;
			std::cout << "-i <filename>" << std::endl;
			std::cout <<
				"\t Name of the video file to be read"
				<< std::endl;
			return 0;
		}
		else if (!strcmp(argv[i],"-i")){
			if (argc <= i+1){
				std::cout << "please specify an input file name" << std::endl;
				return 0;
			}
			else{
				filename = argv[i+1];
				i++;
			}
		}
	}
	return filename;
}
