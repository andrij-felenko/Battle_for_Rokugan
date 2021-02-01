cmake_minimum_required(VERSION 3.14)
project(gui_trinn VERSION 0.0.1)

set (trinn_h
    include/gui_trinn/trinn.h
)

set (trinn_cpp
     trinn.cpp
)

set (force_rc_business -Wl,--whole-archive rc_business -Wl,--no-whole-archive)

set (CMAKE_AUTORCC ON)
find_package(Qt6 COMPONENTS Core Qml Quick)

add_library(gui_trinn ${trinn_h} ${trinn_cpp} trinn_rc.qrc)

set_target_properties(gui_trinn PROPERTIES PREFIX "plug_" OUTPUT_NAME "trinn")
target_link_libraries(gui_trinn
    ${force_rc_business}
    lib_baseAF lib_quickAF lib_currencyAF lib_trinn
    Qt6::Core Qt6::Quick Qt6::Qml
)

target_include_directories(gui_trinn
    PUBLIC  include
    PRIVATE include/gui_trinn
    PUBLIC $<TARGET_PROPERTY:lib_baseAF,INTERFACE_INCLUDE_DIRECTORIES>
    PUBLIC $<TARGET_PROPERTY:lib_quickAF,INTERFACE_INCLUDE_DIRECTORIES>
    PUBLIC $<TARGET_PROPERTY:lib_currencyAF,INTERFACE_INCLUDE_DIRECTORIES>
    PUBLIC $<TARGET_PROPERTY:lib_trinn,INTERFACE_INCLUDE_DIRECTORIES>
)
