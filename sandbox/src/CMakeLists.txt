# Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)

if(EXISTS ${LOC_PATH})
  message(FATAL_ERROR "You cannout build in a source directory.")
endif()

project(polyglot-sandbox LANGUAGES CXX)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/SyntaxPropertiesWidget.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/SyntaxTreeItem.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/SyntaxTreeModel.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/SyntaxTreeWidget.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/SyntaxVisualizationDockWidget.cpp
)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
  ${SOURCES}
)

target_compile_features(${PROJECT_NAME} PRIVATE ${CPP_STANDARD})
target_link_libraries(${PROJECT_NAME} PRIVATE polyglot Qt6::Widgets)

target_compile_definitions(${PROJECT_NAME}
  PRIVATE
    QT_NO_CAST_TO_ASCII QT_NO_CAST_FROM_ASCII QT_USE_FAST_OPERATOR_PLUS
    ${Qt6Widgets_DEFINITIONS}
)

target_compile_options(${PROJECT_NAME}
  PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:>
    $<$<CXX_COMPILER_ID:MSVC>:/w44265 /wd4251>
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${PROJECT_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
    ${Qt6Widgets_INCLUDE_DIRS}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}
  RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)
