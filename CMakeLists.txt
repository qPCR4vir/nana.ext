cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(nana_ext VERSION      0.0.2
        DESCRIPTION "Some extentions for the nana C++ GUI library"
        HOMEPAGE_URL https://github.com/qPCR4vir/nana.ext
        LANGUAGES CXX         )


option(BUILD_SHARED_LIBS "Compile nana_ext as a shared library." OFF)

#######################     Main setting of Nana targets, sources and installs

add_library(nana_ext)
# target_compile_features   (nana_ext PUBLIC cxx_std_14)
target_include_directories(nana_ext PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

target_sources            (nana_ext PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/CompoWidget.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/EditableForm.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/number.cpp)


add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../../ProgParam ${CMAKE_CURRENT_LIST_DIR}/../../cmake-progparam-build-${CMAKE_BUILD_TYPE} )
target_link_libraries(nana_ext PUBLIC progparam )


add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../nana ${CMAKE_CURRENT_LIST_DIR}/../cmake-nana-build-${CMAKE_BUILD_TYPE} )
target_link_libraries(nana_ext PUBLIC nana )

if (NANA_CMAKE_VERBOSE_PREPROCESSOR)

    include(CMakePrintHelpers)
    cmake_print_properties(TARGETS nana_ext  PROPERTIES
            COMPILE_DEFINITIONS   COMPILE_OPTIONS    COMPILE_FLAGS  LINK_LIBRARIES
            INCLUDE_DIRECTORIES   INSTALL_NAME_DIR   LINK_FLAGS     VERSION)

endif()