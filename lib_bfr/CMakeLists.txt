cmake_minimum_required(VERSION 3.14)
project(lib_bfr VERSION 0.0.1)

set (lib_bfr_h
    include/lib_bfr/border.h
    include/lib_bfr/card.h
    include/lib_bfr/game.h
    include/lib_bfr/map.h
    include/lib_bfr/mission.h
    include/lib_bfr/player.h
    include/lib_bfr/province.h
    include/lib_bfr/provinceToken.h
    include/lib_bfr/region.h
    include/lib_bfr/turnToken.h
    include/lib_bfr/turnManager.h
    include/lib_bfr/clan.h
    include/lib_bfr/clanStats.h
    include/lib_bfr/battle.h
    include/bfrLib.h
    include/bfrLib_pre.h
    include/bfrEnum.h
)

set (lib_bfr_cpp
    border.cpp
    card.cpp
    clan.cpp
    game.cpp
    map.cpp
    mission.cpp
    player.cpp
    province.cpp
    provinceToken.cpp
    region.cpp
    turnToken.cpp
    turnTokenPlace.h
    turnTokenPlace.cpp
    turnManager.cpp
    battle.cpp
    clanStats.cpp
)

set (bfr_initialize_header
    include/BFR/Border
    include/BFR/Card
    include/BFR/Game
    include/BFR/Map
    include/BFR/Mission
    include/BFR/Player
    include/BFR/Province
    include/BFR/ProvinceToken
    include/BFR/Region
    include/BFR/TurnToken
    include/BFR/TurnManager
    include/BFR/Clan
    include/BFR/Battle
    include/BFR/ClanStats
    include/BFRlib
)

set (CMAKE_AUTOMOC, true)
set (CMAKE_AUTORCC ON)
set (CMAKE_CXX_STANDARD 20)
find_package(Qt6 COMPONENTS Core LinguistTools)
qt6_create_translation(QM_FILES ${lib_bfr_h} ${lib_bfr_cpp}
    tr/bfr_ua.ts
    tr/bfr_ru.ts
    tr/bfr_sp.ts
    tr/bfr_fr.ts
    tr/bfr_de.ts
    tr/bfr_pl.ts
    tr/bfr_jp.ts
)

add_library(lib_bfr ${lib_bfr_h} ${lib_bfr_cpp}
    rc_lib_bfr_tr.qrc ${bfr_initialize_header} ${QM_FILES})

set_target_properties(lib_bfr PROPERTIES OUTPUT_NAME "lib_bfr")
target_link_libraries(lib_bfr lib_baseAF lib_currencyAF Qt6::Core)
target_include_directories(lib_bfr
    PUBLIC  include
    PUBLIC  include/Trinn
    PRIVATE include/lib_trinn
    PUBLIC $<TARGET_PROPERTY:lib_currencyAF,INTERFACE_INCLUDE_DIRECTORIES>
    PUBLIC $<TARGET_PROPERTY:lib_baseAF,INTERFACE_INCLUDE_DIRECTORIES>
)

add_custom_command(TARGET lib_bfr PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/translate
                                               ${CMAKE_CURRENT_SOURCE_DIR}/tr)

add_custom_command(TARGET lib_bfr POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/tr
                                               ${CMAKE_CURRENT_SOURCE_DIR}/translate)
