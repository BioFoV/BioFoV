## Project Configuration
PRO_NAME=BioFoV
PRO_FILE=application/application.pro

## System info
PWD=$(shell pwd)
CPUS=$(shell nproc)

## Third party libs
THIRD_PARTY_FLD=third-party
# OpenCV
OPENCV_BUILD_WIN=build-opencv-win
OPENCV_BUILD_LIN=build-opencv-lin
# Qt
QMAKE_WIN=$(THIRD_PARTY_FLD)/qt/windows-install/bin/qmake
QT_BUILD_WIN=build-qt-win
QT_BUILD_LIN=build-qt-lin

## Windows stuff
WIN_BUILD_FLD=windows
WIN_BUILD_TYPE=release
WIN_FFMPEG_WRONG=$(THIRD_PARTY_FLD)/opencv/src-2.4.8/3rdparty/ffmpeg/opencv_ffmpeg.dll
WIN_FFMPEG_RIGHT=opencv_ffmpeg248.dll
WIN_ZIP=$(PRO_NAME).zip

################################################################################

qt-windows:
	cd $(THIRD_PARTY_FLD); \
	./$(QT_BUILD_WIN); \
	cd ..;

opencv-windows:
	cd $(THIRD_PARTY_FLD); \
	./$(OPENCV_BUILD_WIN); \
	cd ..;

build-only-windows:
	cd $(WIN_BUILD_FLD); \
	../$(QMAKE_WIN) ../$(PRO_FILE); \
	$(MAKE) -j$(CPUS) $(WIN_BUILD_TYPE); \
	cd ..;

build-windows: qt-windows opencv-windows build-only-windows

zip-only-windows:
	cd $(WIN_BUILD_FLD); \
	cp $(PWD)/$(WIN_FFMPEG_WRONG) $(WIN_FFMPEG_RIGHT); \
	zip -j ../$(WIN_ZIP) $(WIN_BUILD_TYPE)/$(PRO_NAME).exe $(WIN_FFMPEG_RIGHT);

zip-windows: build-windows zip-only-windows

windows: zip-windows

################################################################################

all: windows
