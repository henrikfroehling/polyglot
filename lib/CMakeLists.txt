set(POLYGLOT_VERSION_MAJOR 0)
set(POLYGLOT_VERSION_MINOR 1)
set(POLYGLOT_VERSION_PATCH 0)
set(POLYGLOT_VERSION_SUFFIX " pre alpha 1")
set(POLYGLOT_VERSION "${POLYGLOT_VERSION_MAJOR}.${POLYGLOT_VERSION_MINOR}.${POLYGLOT_VERSION_PATCH}")
set(POLYGLOT_VERSION_WITH_SUFFIX "${POLYGLOT_VERSION}${POLYGLOT_VERSION_SUFFIX}")

project(polyglot VERSION ${POLYGLOT_VERSION} LANGUAGES CXX)
message(STATUS "Project: ${PROJECT_NAME} ${POLYGLOT_VERSION_WITH_SUFFIX}")

# Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)

if(EXISTS ${LOC_PATH})
  message(FATAL_ERROR "You cannot build in a source directory.")
endif()

configure_file(
  ${PROJECT_SOURCE_DIR}/include/polyglot/Version.hpp.in
  ${PROJECT_BINARY_DIR}/include/polyglot/Version.hpp
)

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

set(SOURCES
  ${SOURCE_DIR}/Polyglot.cpp
  ${SOURCE_DIR}/Version.cpp
)

set(SOURCES_CORE
  ${SOURCE_DIR}/Core/Hashing.cpp
  ${SOURCE_DIR}/Core/Types.cpp
)

set(SOURCES_CODEANALYSIS_CORE
  ${SOURCE_DIR}/CodeAnalysis/CodeAnalysis.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/CharFlags.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Lexer.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/LexerCache.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Parser.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/QuickScanState.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/TextKeyedCache.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/TokenInfo.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/SyntaxKinds.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/SyntaxNode.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/SyntaxToken.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/SyntaxTree.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/SyntaxTrivia.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Text/LinePosition.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Text/LinePositionSpan.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Text/SlidingTextWindow.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Text/SourceText.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Text/TextLine.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Text/TextLineCollection.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Text/TextSpan.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Text/TextUtilities.cpp
)

set(SOURCES_CODEANALYSIS_DELPHI_CORE
  ${SOURCE_DIR}/CodeAnalysis/Delphi/DelphiLexer.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/DelphiLexerFlags.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/DelphiLexerStates.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/DelphiParser.cpp
)

set(SOURCES_CODEANALYSIS_DELPHI_SYNTAX
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiCompilationUnitSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiExpressionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiIdentifierNameSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiNameSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiPackageContainsClauseSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiPackageHeadingSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiPackageModuleSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiPackageRequiresClauseSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiProgramHeadingSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiProgramModuleSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiQualifiedNameSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiSimpleNameSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiSyntaxFacts.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiSyntaxTree.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiTypeSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiUnitModuleSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiUnitFinalizationSectionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiUnitHeadingSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiUnitImplementationSectionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiUnitInitializationSectionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiUnitInterfaceSectionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiUnitReferenceDeclarationSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiUsesClauseSyntax.cpp
)

set(SOURCES_CODEANALYSIS_DELPHI
  ${SOURCES_CODEANALYSIS_DELPHI_CORE}
  ${SOURCES_CODEANALYSIS_DELPHI_SYNTAX}
)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(${PROJECT_NAME} SHARED)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
  ${SOURCES}
  ${SOURCES_CORE}
  ${SOURCES_CODEANALYSIS_CORE}
  ${SOURCES_CODEANALYSIS_DELPHI}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_compile_options(${PROJECT_NAME}
  PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wno-switch -Wno-shift-count-overflow>
    $<$<CXX_COMPILER_ID:MSVC>:/w44265 /wd4251 /wd4293>
)

target_compile_definitions(${PROJECT_NAME}
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:polyglot_EXPORTS>
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/polyglot>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${PROJECT_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/polyglot
    ${PROJECT_SOURCE_DIR}/src
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${POLYGLOT_VERSION}
  SOVERSION ${POLYGLOT_VERSION}
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN 1
  ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}
  LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}
  RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
)

include(GenerateExportHeader)

generate_export_header(${PROJECT_NAME}
  EXPORT_MACRO_NAME POLYGLOT_API
  EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/polyglot/polyglot_global.hpp
)
