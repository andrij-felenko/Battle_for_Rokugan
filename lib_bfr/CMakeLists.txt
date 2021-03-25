cmake_minimum_required(VERSION 3.14)
project(lib_bfr VERSION 0.0.1)

set (lib_bfr_h
    include/lib_bfr/handler/battle.h
    include/lib_bfr/handler/stats.h
    include/lib_bfr/handler/turn.h
    include/lib_bfr/karta/border.h
    include/lib_bfr/karta/map.h
    include/lib_bfr/karta/province.h
    include/lib_bfr/karta/territory.h
    include/lib_bfr/karta/tokenBasement.h
    include/lib_bfr/object/card.h
    include/lib_bfr/object/clan.h
    include/lib_bfr/object/player.h
    include/lib_bfr/object/secretObjective.h
    include/lib_bfr/token/combat.h
    include/lib_bfr/token/control.h
    include/lib_bfr/token/honor.h
    include/lib_bfr/token/province.h
    include/lib_bfr/game.h
    include/bfrEnum.h
    include/bfrLib_pre.h
    include/bfrLib.h
)

set (lib_bfr_cpp
    src/game.cpp
    src/handler/battle.cpp
    src/handler/stats.cpp
    src/handler/turn.cpp
    src/karta/border.cpp
    src/karta/map.cpp
    src/karta/province.cpp
    src/karta/territory.cpp
    src/karta/tokenBasement.cpp
    src/object/card.cpp
    src/object/clan.cpp
    src/object/player.cpp
    src/object/secretObjective.cpp
    src/token/combat.cpp
    src/token/control.cpp
    src/token/honor.cpp
    src/token/province.cpp
)

set (bfr_initialize_header
    include/BFR/Handler/Battle
    include/BFR/Handler/Stats
    include/BFR/Handler/Turn
    include/BFR/Karta/Border
    include/BFR/Karta/Map
    include/BFR/Karta/Province
    include/BFR/Karta/Territory
    include/BFR/Karta/TokenBasement
    include/BFR/Object/Card
    include/BFR/Object/Clan
    include/BFR/Object/Player
    include/BFR/Object/SecretObjective
    include/BFR/Token/Combat
    include/BFR/Token/Control
    include/BFR/Token/Honor
    include/BFR/Token/Province
    include/BFR/Game
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

set_target_properties(lib_bfr PROPERTIES OUTPUT_NAME "bfr")
target_link_libraries(lib_bfr lib_baseAF lib_currencyAF Qt6::Core)
target_include_directories(lib_bfr
    PUBLIC  include
    PUBLIC  include/Trinn
    PRIVATE include/lib_bfr
    PUBLIC $<TARGET_PROPERTY:lib_currencyAF,INTERFACE_INCLUDE_DIRECTORIES>
    PUBLIC $<TARGET_PROPERTY:lib_baseAF,INTERFACE_INCLUDE_DIRECTORIES>
)

add_custom_command(TARGET lib_bfr PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/translate
                                               ${CMAKE_CURRENT_SOURCE_DIR}/tr)

add_custom_command(TARGET lib_bfr POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/tr
                                               ${CMAKE_CURRENT_SOURCE_DIR}/translate)
