################################################################################
#
# Cross compiler for Qt programs that use OpenCV.
# creator: Miguel Almeida
# date: 2014/09
#
################################################################################

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
QMAKE_LIN=$(THIRD_PARTY_FLD)/qt/linux-install/bin/qmake
QT_BUILD_WIN=build-qt-win
QT_BUILD_LIN=build-qt-lin

## Windows stuff
WIN_BUILD_FLD=windows
WIN_BUILD_TYPE=release
WIN_FFMPEG_WRONG=$(THIRD_PARTY_FLD)/opencv/src-2.4.8/3rdparty/ffmpeg/opencv_ffmpeg.dll
WIN_FFMPEG_RIGHT=opencv_ffmpeg248.dll
WIN_ZIP=$(PRO_NAME).zip

## Linux stuff
LIN_BUILD_FLD=linux
LIN_BUILD_TYPE=release

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

qt-linux:
	cd $(THIRD_PARTY_FLD); \
	./$(QT_BUILD_LIN); \
	cd ..;

opencv-linux:
	cd $(THIRD_PARTY_FLD); \
	./$(OPENCV_BUILD_LIN); \
	cd ..;

build-only-linux:
	cd $(LIN_BUILD_FLD); \
	../$(QMAKE_LIN) ../$(PRO_FILE); \
	$(MAKE) -j$(CPUS) $(LIN_BUILD_TYPE); \
	cd ..;

build-linux: qt-linux opencv-linux build-only-linux

linux: build-linux

################################################################################

all: windows linux

################################################################################

clean-qt-linux:
	rm -rf $(THIRD_PARTY_FLD)/qt/linux*
clean-opencv-linux:
	rm -rf $(THIRD_PARTY_FLD)/opencv/linux*
clean-build-linux:
	rm -rf linux/*
clean-linux: clean-qt-linux clean-opencv-linux clean-build-linux

clean-qt-windows:
	rm -rf $(THIRD_PARTY_FLD)/qt/windows*
clean-opencv-windows:
	rm -rf $(THIRD_PARTY_FLD)/opencv/windows*
clean-build-windows:
	rm -rf windows/*
clean-windows: clean-qt-windows clean-opencv-windows clean-build-windows

clean-qt-src:
	rm -rf $(THIRD_PARTY_FLD)/qt/src*
clean-opencv-src:
	rm -rf $(THIRD_PARTY_FLD)/opencv/src*
clean-src: clean-qt-src clean-opencv-src

clean: clean-windows clean-linux clean-src

