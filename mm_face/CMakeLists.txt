cmake_minimum_required(VERSION 2.8)
project( mm_facedetect )
find_package( OpenCV REQUIRED )
add_executable( mm_facedetect mm_facedetect.cpp ) 
target_link_libraries( mm_facedetect ${OpenCV_LIBS} )
