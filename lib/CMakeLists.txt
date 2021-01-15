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
  ${SOURCE_DIR}/CodeAnalysis/Core/Directive.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/DirectiveList.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/DirectiveParser.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/DirectiveStack.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Lexer.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/LexerCache.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/LexerMode.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Parser.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/QuickScanState.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/SyntaxFactory.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/SyntaxKinds.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/SyntaxNodeFlags.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/SyntaxPool.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/TextKeyedCache.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/TokenInfo.cpp
)

set(SOURCES_CODEANALYSIS_CORE_SYNTAX
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Expressions/BinaryExpressionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Expressions/CallExpressionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Expressions/IdentifierNameExpressionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Expressions/LiteralExpressionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Expressions/ParenthesizedExpressionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Expressions/PrefixUnaryExpressionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Expressions/QualifiedNameExpressionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Expressions/SimpleNameExpressionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Expressions/TypeExpressionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Trivia/BadDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Trivia/BranchingDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Trivia/ConditionalDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Trivia/DefineDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Trivia/ElseDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Trivia/ElseIfDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Trivia/EndIfDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Trivia/EndRegionDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Trivia/IfDefDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Trivia/IfDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Trivia/IfEndDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Trivia/IfNDefDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Trivia/MessageDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Trivia/RegionDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Trivia/SkippedTokensTriviaSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Trivia/StructuredTriviaSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Trivia/SwitchDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/Trivia/UndefDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/ExpressionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/SyntaxNode.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/SyntaxToken.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/SyntaxTree.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/SyntaxTrivia.cpp
)

set(SOURCES_CODEANALYSIS_CORE_TEXT
  ${SOURCE_DIR}/CodeAnalysis/Core/Text/LinePosition.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Text/LinePositionSpan.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Text/SourceText.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Text/TextSpan.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Text/TextUtilities.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Text/TextWindow.cpp
)

set(SOURCES_CODEANALYSIS_DELPHI_CORE
  ${SOURCE_DIR}/CodeAnalysis/Delphi/DelphiDirectiveParser.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/DelphiLexer.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/DelphiLexerFlags.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/DelphiLexerStates.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/DelphiParser.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/DelphiSyntaxFacts.cpp
)

set(SOURCES_CODEANALYSIS_DELPHI_SYNTAX
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/Nodes/DelphiCompilationUnitSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageContainsClauseSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageHeadingSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageModuleSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageRequiresClauseSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/Nodes/DelphiProgramHeadingSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/Nodes/DelphiProgramModuleSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitFinalizationSectionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitHeadingSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitImplementationSectionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInitializationSectionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInterfaceSectionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitModuleSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitReferenceDeclarationSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUsesClauseSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiSyntaxTree.cpp
)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(${PROJECT_NAME} SHARED)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
  ${SOURCES}
  ${SOURCES_CORE}
  ${SOURCES_CODEANALYSIS_CORE}
  ${SOURCES_CODEANALYSIS_CORE_SYNTAX}
  ${SOURCES_CODEANALYSIS_CORE_TEXT}
  ${SOURCES_CODEANALYSIS_DELPHI_CORE}
  ${SOURCES_CODEANALYSIS_DELPHI_SYNTAX}
)

target_compile_features(${PROJECT_NAME} PRIVATE ${CPP_STANDARD})

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

install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Config
  ARCHIVE DESTINATION ${INSTALL_LIB_DIR}
  LIBRARY DESTINATION ${INSTALL_LIB_DIR}
  RUNTIME DESTINATION ${INSTALL_BIN_DIR}
  INCLUDES DESTINATION ${INSTALL_INCLUDE_DIR}
)

install(EXPORT ${PROJECT_NAME}Config
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION "${INSTALL_LIB_DIR}/cmake/${PROJECT_NAME}"
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file("${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}ConfigVersion.cmake"
  VERSION ${POLYGLOT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(FILES "${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION "${INSTALL_LIB_DIR}/cmake/${PROJECT_NAME}"
)
