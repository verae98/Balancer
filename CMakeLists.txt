cmake_minimum_required(VERSION 2.8)
project( Balancer )
find_package( OpenCV REQUIRED )
link_directories(/usr/local/lib/)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)
QT5_WRAP_UI( UI_HEADERS QT/mrb_window.ui QT/coordinate_popup.ui )

add_executable( Balancer main.cpp sources/pidController.cpp headers/pidController.hpp QT/ui_mrb_window.cpp ${UI_HEADERS} QT/ui_CoordinatePopup.cpp QT/ui_CoordinatePopup.hpp)

target_link_libraries( Balancer ${OpenCV_LIBS})
target_link_libraries( Balancer serial)
target_link_libraries( Balancer Qt5::Widgets)