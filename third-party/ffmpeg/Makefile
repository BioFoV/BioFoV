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

## Linux stuff
LIN_BUILD_FLD=linux-build
LIN_INSTALL_FLD=linux-install
LIN_VERSION=release/2.3
LIN_SRC_FLD=linux-src

################################################################################

all: linux

########################## Source Cloning Rules ################################

src: linux-src
linux-src:
	test -d $(LIN_SRC_FLD) || git clone --branch $(LIN_VERSION) --depth 1 $(SRC_GIT) $(LIN_SRC_FLD)
	cd $(LIN_SRC_FLD); \
	git pull

############################ Full Build Rules ##################################

linux: linux-src
	cd $(LIN_SRC_FLD); \
	./configure --enable-pic \
				--prefix=$(PWD)/third-party/$(LIN_INSTALL_FLD) \
				--disable-debug \
				--disable-ffplay \
				--disable-ffserver \
				--disable-doc
	$(MAKE) -C $(LIN_SRC_FLD) -j$(CPUS) install

############################## Clean Rules #####################################

clean-linux-build:
	rm -rf $(LIN_BUILD_FLD)
clean-linux-install:
	rm -rf $(LIN_INSTALL_FLD)
clean-linux: clean-linux-build clean-linux-install

clean-src: clean-linux-src
clean-linux-src:
	rm -rf $(LIN_SRC_FLD)

clean: clean-linux clean-src
