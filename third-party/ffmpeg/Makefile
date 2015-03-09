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
# libav
SRC_FLD=src
SRC_GIT=git://source.ffmpeg.org/ffmpeg.git

## Windows stuff
WIN_BUILD_FLD=windows-build
WIN_INSTALL_FLD=windows-install
WIN_VERSION=release/11
WIN_SRC_FLD=src-$(WIN_VERSION)
WIN_TBZ=ffmpeg-windows.tbz
OPENCV_WIN_TBZ_URL=https://www.dropbox.com/s/z2ausk9ium7wepg/$(WIN_TBZ)

## Linux stuff
LIN_BUILD_FLD=linux-build
LIN_INSTALL_FLD=linux-install
LIN_VERSION=release/2.3
LIN_SRC_FLD=linux-src
LIN_TBZ=ffmpeg-linux.tbz
#OPENCV_LIN_TBZ_URL=

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
	cd $(LIN_SRC_FLD); \
	./configure --enable-pic \
				--prefix=/home/miguel/Documents/IST/Tese/BioFoV/third-party/$(LIN_INSTALL_FLD) \
				--disable-debug \
				--disable-ffplay \
				--disable-ffserver \
				--disable-doc
	$(MAKE) -C $(LIN_SRC_FLD) -j$(CPUS) install

windows: windows-src
	mkdir -p $(WIN_BUILD_FLD); \
	cd $(WIN_BUILD_FLD); \
	cmake -D CMAKE_BUILD_TYPE=RELEASE \
      -D CMAKE_INSTALL_PREFIX=../$(WIN_INSTALL_FLD) \
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
	cp $(WIN_SRC_FLD)/3rdparty/ffmpeg/opencv_ffmpeg.dll $(WIN_INSTALL_FLD)

############################ Lazy Deploy Rules #################################

linux-create-tbz: linux
	tar -cjf $(LIN_TBZ) $(LIN_INSTALL_FLD)

windows-create-tbz: windows
	tar -cjf $(WIN_TBZ) $(WIN_INSTALL_FLD)

linux-deploy-tbz:
	rm -rf $(LIN_INSTALL_FLD)
	wget --quiet $(OPENCV_LIN_TBZ_URL)
	tar -xjf $(LIN_TBZ)

windows-deploy-tbz:
	rm -rf $(WIN_INSTALL_FLD)
	wget --quiet $(OPENCV_WIN_TBZ_URL)
	tar -xjf $(WIN_TBZ)

############################## Clean Rules #####################################

clean-linux-build:
	rm -rf $(LIN_BUILD_FLD)
clean-linux-install:
	rm -rf $(LIN_INSTALL_FLD)
clean-linux-tbz:
	rm -f $(LIN_TBZ)
clean-linux: clean-linux-build clean-linux-install clean-linux-tbz

clean-windows-build:
	rm -rf $(WIN_BUILD_FLD)
clean-windows-install:
	rm -rf $(WIN_INSTALL_FLD)
clean-windows-tbz:
	rm -f $(WIN_TBZ)
clean-windows: clean-windows-build clean-windows-install clean-windows-tbz

clean-src: clean-linux-src clean-windows-src
clean-windows-src:
	rm -rf $(WIN_SRC_FLD)
clean-linux-src:
	rm -rf $(LIN_SRC_FLD)

clean: clean-windows clean-linux clean-src
