cmake_minimum_required(VERSION 3.20)
project(RawImageEditor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(SOURCES
    src/main.cpp
    src/app/Application.cpp
    src/app/MainWindow.cpp
    src/ui/LeftPanel.cpp
    src/ui/RightPanel.cpp
    src/ui/Toolbar.cpp
    src/ui/ImageView.cpp
    src/ui/AdjustmentWidgets/WhiteBalanceWidget.cpp
    src/ui/AdjustmentWidgets/ExposureWidget.cpp
    src/ui/AdjustmentWidgets/ContrastWidget.cpp
    src/ui/AdjustmentWidgets/BrightnessWidget.cpp
    src/ui/AdjustmentWidgets/SaturationWidget.cpp
    src/ui/AdjustmentWidgets/HDRWidget.cpp
    src/ui/AdjustmentWidgets/LevelsWidget.cpp
    src/ui/AdjustmentWidgets/CurveWidget.cpp
    src/ui/AdjustmentWidgets/ColorEditorWidget.cpp
    src/ui/AdjustmentWidgets/ColorBalanceWidget.cpp
    src/ui/AdjustmentWidgets/BlackAndWhiteWidget.cpp
    src/ui/AdjustmentWidgets/DehazeWidget.cpp
    src/ui/AdjustmentWidgets/ClarityWidget.cpp
    src/ui/AdjustmentWidgets/VignetteWidget.cpp
)

set(HEADERS
    src/app/Application.h
    src/app/MainWindow.h
    src/ui/LeftPanel.h
    src/ui/RightPanel.h
    src/ui/Toolbar.h
    src/ui/ImageView.h
    src/ui/AdjustmentWidgets/WhiteBalanceWidget.h
    src/ui/AdjustmentWidgets/ExposureWidget.h
    src/ui/AdjustmentWidgets/ContrastWidget.h
    src/ui/AdjustmentWidgets/BrightnessWidget.h
    src/ui/AdjustmentWidgets/SaturationWidget.h
    src/ui/AdjustmentWidgets/HDRWidget.h
    src/ui/AdjustmentWidgets/LevelsWidget.h
    src/ui/AdjustmentWidgets/CurveWidget.h
    src/ui/AdjustmentWidgets/ColorEditorWidget.h
    src/ui/AdjustmentWidgets/ColorBalanceWidget.h
    src/ui/AdjustmentWidgets/BlackAndWhiteWidget.h
    src/ui/AdjustmentWidgets/DehazeWidget.h
    src/ui/AdjustmentWidgets/ClarityWidget.h
    src/ui/AdjustmentWidgets/VignetteWidget.h
)

qt_add_resources(RESOURCES resources/resources.qrc)   # if we add one

add_executable(RawImageEditor ${SOURCES} ${HEADERS})
target_include_directories(RawImageEditor PRIVATE src)   # so #include "ui/..." works
target_link_libraries(RawImageEditor PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)