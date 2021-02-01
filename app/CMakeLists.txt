cmake_minimum_required(VERSION 3.14)
project(app_pocket_munnin)

set (pm_src
    main.cpp
    )

set (CMAKE_AUTORCC ON)
find_package(Qt6 COMPONENTS Qml Quick)

add_executable(app_pocket_munnin ${pm_src} pocket_munnin.qrc)

set_target_properties(app_pocket_munnin PROPERTIES OUTPUT_NAME "pocket_munnin")
target_link_libraries(app_pocket_munnin
    rc_af_base
    lib_baseAF lib_quickAF lib_currencyAF gui_trinn
    Qt6::Quick Qt6::Qml)

target_compile_features(app_pocket_munnin PUBLIC cxx_std_17)
target_include_directories(app_pocket_munnin PUBLIC include
    PUBLIC $<TARGET_PROPERTY:lib_baseAF,INTERFACE_INCLUDE_DIRECTORIES>
    PUBLIC $<TARGET_PROPERTY:lib_quickAF,INTERFACE_INCLUDE_DIRECTORIES>
    PUBLIC $<TARGET_PROPERTY:lib_currencyAF,INTERFACE_INCLUDE_DIRECTORIES>
    PUBLIC $<TARGET_PROPERTY:gui_trinn,INTERFACE_INCLUDE_DIRECTORIES>
    PUBLIC $<TARGET_PROPERTY:lib_trinn,INTERFACE_INCLUDE_DIRECTORIES>
)
