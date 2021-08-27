cmake_minimum_required(VERSION 3.19)
project(elisRs128WinTest)

set(CMAKE_CXX_STANDARD 14)

if (CMAKE_HOST_APPLE)
    set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt@5/5.15.2/lib/cmake")
elseif (CMAKE_HOST_WIN32)
    set (CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.12.11\\5.12.11\\msvc2017_64\\")
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)


if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
find_package(Qt5SerialPort)

SET(serialport_SOURCES ${treebot_SOURCE_DIR}/serialport/serialport.cpp)
SET(serialport_HEADERS ${treebot_SOURCE_DIR}/serialport/serialport.h)
QT5_WRAP_CPP(serialport_HEADERS_MOC ${serialport_HEADERS})
qt5_wrap_ui(UI_HEADERS ${treebot_SOURCE_DIR}/serialport/serialport.ui)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})


#include_directories(/usr/local/Cellar/qt@5/5.15.2/lib/QtSerialPort.framework/)
add_executable(${PROJECT_NAME} example/main.cpp
        src/elisserial/serialport/SerialPort.cpp
        src/elisserial/serialport/SerialPort.h
        src/view/ElisMainWidget.cpp
        src/view/ElisMainWidget.h
        src/view/ElisMainWidget.ui
        src/view/ComboListContent.h
        src/elisserial/parsedata/PackagingAndUnpacking.cpp
        src/elisserial/parsedata/PackagingAndUnpacking.h src/utils/StringUtils.cpp src/utils/StringUtils.h src/view/ElisSensorTestWidget.cpp src/view/ElisSensorTestWidget.h src/view/ElisSensorTestWidget.ui src/view/CustomComboBox.cpp src/view/CustomComboBox.h src/elisserial/EnumResultCode.h)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${Qt5Core_LIBRARIES}  ${Qt5Widgets_LIBRARIES}  ${Qt5SerialPort_LIBRARIES})
