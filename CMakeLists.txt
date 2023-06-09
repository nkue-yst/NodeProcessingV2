cmake_minimum_required(VERSION 3.20)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if(NOT DEFINED CMAKE_SUPPRESS_DEVELOPER_WARNINGS)
    set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings.")
endif()

project(NodeProcessingV2 CXX)

### cmake module ###
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/thirdparty/cmake/sdl2)

### imgui ###
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/thirdparty/imgui)
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends)
set(IMGUI_SOURCES
	${IMGUI_DIR}/imgui.cpp
	${IMGUI_DIR}/imgui_demo.cpp
	${IMGUI_DIR}/imgui_draw.cpp
	${IMGUI_DIR}/imgui_tables.cpp
	${IMGUI_DIR}/imgui_widgets.cpp
	${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
	${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

### imnodes ###
set(IMNODES_DIR ${CMAKE_SOURCE_DIR}/thirdparty/imnodes)
include_directories(${IMNODES_DIR})
set(IMNODES_SOURCES ${IMNODES_DIR}/imnodes.cpp)

### ImGuiFileDialog ###
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/ImGuiFileDialog)
set(IMGUI_FILE_DIALOG_SOURCES ${CMAKE_SOURCE_DIR}/thirdparty/ImGuiFileDialog/ImGuiFileDialog.cpp)

### OpenGL ###
find_package(OpenGL REQUIRED)

### OpenCV ###
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

### SDL2 ###
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

### stb ###
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/stb)

### NodeProcessingV2 ###
set(MAIN_SRC_DIR ${CMAKE_SOURCE_DIR}/src/)
include_directories(${MAIN_SRC_DIR})
include_directories((${MAIN_SRC_DIR}/node))
set(NP_SOURCES
	${MAIN_SRC_DIR}/Image.cpp
	${MAIN_SRC_DIR}/main.cpp
	${MAIN_SRC_DIR}/MenuBar.cpp
	${MAIN_SRC_DIR}/MenuItem_Audio.cpp
	${MAIN_SRC_DIR}/MenuItem_File.cpp
	${MAIN_SRC_DIR}/MenuItem_ImageVideo.cpp
	${MAIN_SRC_DIR}/NodeGui.cpp
	${MAIN_SRC_DIR}/NodeManager.cpp
	${MAIN_SRC_DIR}/Pin.cpp
	${MAIN_SRC_DIR}/PinManager.cpp

	${MAIN_SRC_DIR}/node/ImageNode.cpp
	${MAIN_SRC_DIR}/node/Node.cpp
)
add_executable(${PROJECT_NAME} ${NP_SOURCES} ${IMGUI_SOURCES} ${IMNODES_SOURCES} ${IMGUI_FILE_DIALOG_SOURCES})
target_link_libraries(${PROJECT_NAME} OpenGL::GL ${OpenCV_LIBRARIES} SDL2::Core SDL2::Main)

if(WIN32)
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
	set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif(WIN32)
