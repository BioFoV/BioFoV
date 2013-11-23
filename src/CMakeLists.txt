cmake_minimum_required(VERSION 2.8)
project( Framework )
find_package( OpenCV REQUIRED )
find_package(Qt5 REQUIRED)
find_package(Qt5Widgets)
include(${QT_USE_FILE})

#install(TARGETS hello_cmake DESTINATION /usr/bin)

# All files in src will be used, so be careful what you put there...
SET(SRCS
	Framework.cpp
	Video/Video.cpp
	Feature/Feature.cpp
	Frame/Frame.cpp
	Event/Event.cpp
	Individual/Individual.cpp
	Snapshot/Snapshot.cpp
	Video/Video.cpp
	Video/BackgroundSubtraction.cpp)
File(GLOB_RECURSE HEADERS *.hpp)
File(GLOB_RECURSE FORMS *.ui)
File(GLOB_RECURSE RESOURCES *.qrc)

QT4_WRAP_CPP(HEADERS_MOC GUI/mainwindow.h )
QT4_WRAP_UI(FORMS_HEADERS ${FORMS} )
QT4_ADD_RESOURCES(RESOURCES_RCC ${RESOURCES} )

add_executable( Framework ${SRCS} ${HEADERS_MOC} ${FORMS_HEADERS} 
${RESOURCES_RCC})
target_link_libraries( Framework ${OpenCV_LIBS} )
target_link_libraries( Framework ${QT_LIBRARIES} )
add_definitions(${Qt5Widgets_DEFINITIONS})

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # Linux specific code
    MESSAGE("Building for Linux")
    SET(OperatingSystem "Linux")
    SET(CMAKE_CXX_FLAGS ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} )
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # Windows specific code
    MESSAGE("Building for Windows")
    SET(OperatingSystem "Windows")
    SET(CMAKE_CXX_FLAGS "-Wall -static-libgcc -static -lstdc++")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

add_definitions(${CMAKE_CXX_FLAGS})
