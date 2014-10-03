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
DATE=$(shell date "+%Y%m%d-%H%M")

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
WIN=windows
WIN_BUILD_FLD=windows
WIN_BUILD_TYPE=release
WIN_FFMPEG_WRONG=$(THIRD_PARTY_FLD)/opencv/src-2.4.8/3rdparty/ffmpeg/opencv_ffmpeg.dll
WIN_FFMPEG_RIGHT=opencv_ffmpeg248.dll
WIN_ZIP=$(PRO_NAME)-$(WIN)-$(DATE).zip

## Linux stuff
LIN=linux
LIN_BUILD_FLD=linux
LIN_BUILD_TYPE=
LIN_ZIP=$(PRO_NAME)-$(LIN)-$(DATE).zip

################################################################################

all: windows linux

################################################################################

qt-windows:
	$(MAKE) -C $(THIRD_PARTY_FLD) qt-windows

opencv-windows:
	$(MAKE) -C $(THIRD_PARTY_FLD) opencv-windows

build-only-windows:
	mkdir -p $(WIN_BUILD_FLD)
	cd $(WIN_BUILD_FLD); \
	../$(QMAKE_WIN) ../$(PRO_FILE)
	$(MAKE) -C $(WIN_BUILD_FLD) -j$(CPUS) $(WIN_BUILD_TYPE)

build-windows: qt-windows opencv-windows build-only-windows

zip-only-windows:
	cp $(WIN_FFMPEG_WRONG) $(WIN_BUILD_FLD)/$(WIN_FFMPEG_RIGHT)
	zip -j $(WIN_ZIP) $(WIN_BUILD_FLD)/$(WIN_BUILD_TYPE)/$(PRO_NAME).exe $(WIN_BUILD_FLD)/$(WIN_FFMPEG_RIGHT)

zip-windows: build-windows zip-only-windows

windows: zip-windows

################################################################################

qt-linux:
	$(MAKE) -C $(THIRD_PARTY_FLD) qt-linux

opencv-linux:
	$(MAKE) -C $(THIRD_PARTY_FLD) opencv-linux

build-only-linux:
	mkdir -p $(LIN_BUILD_FLD)
	cd $(LIN_BUILD_FLD); \
	../$(QMAKE_LIN) ../$(PRO_FILE)
	$(MAKE) -C $(LIN_BUILD_FLD) -j$(CPUS) $(LIN_BUILD_TYPE)

build-linux: qt-linux opencv-linux build-only-linux

zip-only-linux:
	cd $(LIN_BUILD_FLD); \
	zip -j ../$(LIN_ZIP) $(PRO_NAME)

zip-linux: build-linux zip-only-linux

linux: zip-linux

################################################################################

clean-qt-linux:
	$(MAKE) -C $(THIRD_PARTY_FLD) clean-qt-linux
clean-opencv-linux:
	$(MAKE) -C $(THIRD_PARTY_FLD) clean-opencv-linux
clean-build-linux:
	rm -rf linux/*
clean-linux: clean-qt-linux clean-opencv-linux clean-build-linux

clean-qt-windows:
	$(MAKE) -C $(THIRD_PARTY_FLD) clean-qt-windows
clean-opencv-windows:
	$(MAKE) -C $(THIRD_PARTY_FLD) clean-opencv-windows
clean-build-windows:
	rm -rf windows/*
clean-windows: clean-qt-windows clean-opencv-windows clean-build-windows

clean-qt-src:
	$(MAKE) -C $(THIRD_PARTY_FLD) clean-qt-src
clean-opencv-src:
	$(MAKE) -C $(THIRD_PARTY_FLD) clean-opencv-src
clean-src:
	$(MAKE) -C $(THIRD_PARTY_FLD) clean-src

clean: clean-windows clean-linux clean-src

