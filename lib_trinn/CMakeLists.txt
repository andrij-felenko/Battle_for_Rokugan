cmake_minimum_required(VERSION 3.14)
project(lib_trinn VERSION 0.0.1)

set (lib_trinn_h
    include/trinnLib.h
    include/lib_trinn/model/management.h
    include/lib_trinn/model/subject.h
    include/lib_trinn/model/transaction.h
    include/lib_trinn/trinnEnum.h
    include/lib_trinn/trinnStorage.h
    include/lib_trinn/management/budgate.h
    include/lib_trinn/management/plan.h
    include/lib_trinn/subject/account.h
    include/lib_trinn/subject/category.h
    include/lib_trinn/subject/project.h
    include/lib_trinn/subject/store.h
    include/lib_trinn/transaction/income.h
    include/lib_trinn/transaction/magnet.h
    include/lib_trinn/transaction/purchase.h
    include/lib_trinn/transaction/transfer.h
)

set (lib_trinn_cpp
    trinnEnum.cpp
    trinnStorage.cpp
    model/management.cpp
    model/subject.cpp
    model/transaction.cpp
    management/budgate.cpp
    management/plan.cpp
    subject/account.cpp
    subject/category.cpp
    subject/project.cpp
    subject/store.cpp
    transaction/income.cpp
    transaction/magnet.cpp
    transaction/purchase.cpp
    transaction/transfer.cpp
)

set (initialize_header
    include/TrinnLib
    include/Trinn/Model/Management
    include/Trinn/Model/Subject
    include/Trinn/Model/Transaction
    include/Trinn/Enum
    include/Trinn/Storage
    include/Trinn/Management/Budgate
    include/Trinn/Management/Plan
    include/Trinn/Subject/Account
    include/Trinn/Subject/Category
    include/Trinn/Subject/Project
    include/Trinn/Subject/Store
    include/Trinn/Transaction/Income
    include/Trinn/Transaction/Magnet
    include/Trinn/Transaction/Purchase
    include/Trinn/Transaction/Transfer
)

set (CMAKE_AUTOMOC, true)
find_package(Qt6Core)

add_library(lib_trinn ${lib_trinn_h} ${lib_trinn_cpp} ${initialize_header})

set_target_properties(lib_trinn PROPERTIES OUTPUT_NAME "lib_trinn")
target_link_libraries(lib_trinn lib_baseAF lib_currencyAF Qt6::Core)
target_include_directories(lib_trinn
    PUBLIC  include
    PUBLIC  include/Trinn
    PRIVATE include/lib_trinn
    PUBLIC $<TARGET_PROPERTY:lib_currencyAF,INTERFACE_INCLUDE_DIRECTORIES>
    PUBLIC $<TARGET_PROPERTY:lib_baseAF,INTERFACE_INCLUDE_DIRECTORIES>
)
