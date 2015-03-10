################################################################################
#
# Cross compiler for Qt programs that use OpenCV.
# creator: Miguel Almeida
# date: 2014/09
#
################################################################################

################################# System info ##################################
OPENCV_DIR=$(shell pwd)
ifeq (${TRAVIS}, 1)
	CPUS=1
else
	CPUS=$(shell nproc)
endif

############################### Third party libs ###############################
# Qt
SRC_FLD=src
SRC_GIT=https://github.com/Itseez/opencv.git
PLACEHOLDER=PLACEHOLDER

## Windows stuff
WIN_BUILD_FLD=windows-build
WIN_INSTALL_FLD=windows-install
WIN_VERSION=2.4.11
WIN_SRC_FLD=src-$(WIN_VERSION)

## Linux stuff
LIN_BUILD_FLD=linux-build
LIN_INSTALL_FLD=linux-install
LIN_VERSION=2.4.11
LIN_SRC_FLD=src-$(LIN_VERSION)

################################################################################

all: windows linux

########################## Source Cloning Rules ################################

src: linux-src windows-src
linux-src:
	test -d $(LIN_SRC_FLD) || git clone --branch $(LIN_VERSION) --depth 1 $(SRC_GIT) $(LIN_SRC_FLD)
	cd $(LIN_SRC_FLD); \
	git pull
windows-src:
	test -d $(WIN_SRC_FLD) || git clone --branch $(WIN_VERSION) --depth 1 $(SRC_GIT) $(WIN_SRC_FLD)
	cd $(WIN_SRC_FLD); \
	git pull

############################ Full Build Rules ##################################

linux: linux-src
	export PKG_CONFIG_PATH=$(PWD)/third-party/linux-install/lib/pkgconfig; \
	mkdir -p $(LIN_BUILD_FLD); \
	cd $(LIN_BUILD_FLD); \
	cmake -D CMAKE_BUILD_TYPE=RELEASE \
      -D CMAKE_INSTALL_PREFIX=../../$(LIN_INSTALL_FLD) \
      -D WITH_CUDA=OFF \
      -D ENABLE_FAST_MATH=ON \
      -D BUILD_SHARED_LIBS=OFF \
      -D BUILD_opencv_java=OFF \
      -D BUILD_opencv_python=OFF \
      -D BUILD_opencv_legacy=OFF \
      -D BUILD_opencv_apps=OFF \
      -D BUILD_DOCS=OFF \
      -D BUILD_TESTS=OFF \
      -D BUILD_PERF_TESTS=OFF \
      -D BUILD_FAT_JAVA_LIB=OFF \
      -D BUILD_TBB=ON \
      -D BUILD_PNG=ON \
      -D BUILD_JPEG=ON \
      -D BUILD_TIFF=ON \
      -D BUILD_JASPER=ON \
      -D BUILD_ZLIB=ON \
      -D WITH_TBB=ON \
      -D WITH_GSTREAMER=OFF \
      -D WITH_V4L=OFF \
      -D WITH_FFMPEG=ON \
      -D WITH_LIBV4L=OFF \
      ../$(LIN_SRC_FLD)/
	$(MAKE) -C $(LIN_BUILD_FLD) -j$(CPUS) install

windows: windows-src
	mkdir -p $(WIN_BUILD_FLD); \
	cd $(WIN_BUILD_FLD); \
	cmake -D CMAKE_BUILD_TYPE=RELEASE \
      -D CMAKE_INSTALL_PREFIX=../../$(WIN_INSTALL_FLD) \
      -D CMAKE_TOOLCHAIN_FILE=../../Toolchain-cross-mingw32-linux.cmake \
      -D WITH_CUDA=OFF \
      -D ENABLE_FAST_MATH=ON \
      -D BUILD_SHARED_LIBS=OFF \
      -D BUILD_opencv_java=OFF \
      -D BUILD_opencv_python=OFF \
      -D BUILD_opencv_legacy=OFF \
      -D BUILD_DOCS=OFF \
      -D BUILD_TESTS=OFF \
      -D BUILD_PERF_TESTS=OFF \
      -D BUILD_FAT_JAVA_LIB=OFF \
      -D BUILD_PNG=ON \
      -D BUILD_JPEG=ON \
      -D BUILD_TIFF=ON \
      -D BUILD_JASPER=ON \
      -D BUILD_ZLIB=ON \
      -D WITH_FFMPEG=ON \
      -D WITH_GSTREAMER=OFF \
      ../$(WIN_SRC_FLD)/
	$(MAKE) -C $(WIN_BUILD_FLD) -j$(CPUS) install
	cp $(WIN_SRC_FLD)/3rdparty/ffmpeg/opencv_ffmpeg.dll ../$(WIN_INSTALL_FLD)

############################## Clean Rules #####################################

clean-linux-build:
	rm -rf $(LIN_BUILD_FLD)
clean-linux-install:
	rm -rf $(LIN_INSTALL_FLD)
clean-linux: clean-linux-build clean-linux-install

clean-windows-build:
	rm -rf $(WIN_BUILD_FLD)
clean-windows-install:
	rm -rf $(WIN_INSTALL_FLD)
clean-windows: clean-windows-build clean-windows-install

clean-src: clean-linux-src clean-windows-src
clean-windows-src:
	rm -rf $(WIN_SRC_FLD)
clean-linux-src:
	rm -rf $(LIN_SRC_FLD)

clean: clean-windows clean-linux clean-src
