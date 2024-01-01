cmake_minimum_required (VERSION 3.26)
project ("SDL2_Game1")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /P")

add_definitions(-DSHOW_Rect)

add_subdirectory(src)
add_subdirectory(3rdparty/SDL)
add_subdirectory(3rdparty/SDL2_image)

target_link_libraries(SDL2_Game1 PUBLIC SDL2::SDL2-static SDL2::SDL2main SDL2_image)

if(MSVC)
    message("Using MSVC")
	# 指定C++ 异常处理程序try()catch的展开语义
	set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/EHsc")
	#set_target_properties(SDL2_Game1 PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
