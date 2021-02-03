cmake_minimum_required(VERSION 3.14)
project(app_battle_for_rokugan)

set (bfr_src
    main.cpp
    )

set (CMAKE_AUTORCC ON)
find_package(Qt6 COMPONENTS Qml Quick LinguistTools)

add_executable(app_battle_for_rokugan ${bfr_src} battle_for_rokugan.qrc ${TS_FILES})
#qt6_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
#qt6_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} bfr_en.ts bfrhelloworld_de.ts)

set_target_properties(app_battle_for_rokugan PROPERTIES OUTPUT_NAME "battle_for_rokugan")
target_link_libraries(app_battle_for_rokugan
    rc_af_base
    lib_baseAF lib_quickAF
#    lib_currencyAF gui_bfr
    lib_bfr
    Qt6::Quick Qt6::Qml)

target_compile_features(app_battle_for_rokugan PUBLIC cxx_std_17)
target_include_directories(app_battle_for_rokugan PUBLIC include
    PUBLIC $<TARGET_PROPERTY:lib_baseAF,INTERFACE_INCLUDE_DIRECTORIES>
    PUBLIC $<TARGET_PROPERTY:lib_quickAF,INTERFACE_INCLUDE_DIRECTORIES>
    PUBLIC $<TARGET_PROPERTY:lib_currencyAF,INTERFACE_INCLUDE_DIRECTORIES>
    PUBLIC $<TARGET_PROPERTY:gui_trinn,INTERFACE_INCLUDE_DIRECTORIES>
    PUBLIC $<TARGET_PROPERTY:lib_trinn,INTERFACE_INCLUDE_DIRECTORIES>
)
