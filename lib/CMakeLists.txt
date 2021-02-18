set(POLYGLOT_VERSION_MAJOR 0)
set(POLYGLOT_VERSION_MINOR 1)
set(POLYGLOT_VERSION_PATCH 0)
set(POLYGLOT_VERSION_SUFFIX " pre alpha 1")
set(POLYGLOT_VERSION "${POLYGLOT_VERSION_MAJOR}.${POLYGLOT_VERSION_MINOR}.${POLYGLOT_VERSION_PATCH}")
set(POLYGLOT_VERSION_WITH_SUFFIX "${POLYGLOT_VERSION}${POLYGLOT_VERSION_SUFFIX}")

project(polyglot VERSION ${POLYGLOT_VERSION}
                 DESCRIPTION "A multi language static analysis library."
                 LANGUAGES CXX
)

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

configure_file(
  ${PROJECT_SOURCE_DIR}/VersionInformation.rc.in
  ${PROJECT_BINARY_DIR}/VersionInformation.rc
)

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

set(SOURCES
  ${SOURCE_DIR}/Polyglot.cpp
  ${SOURCE_DIR}/Version.cpp
  ${PROJECT_BINARY_DIR}/VersionInformation.rc
)

set(SOURCES_CORE
  ${SOURCE_DIR}/Core/Hashing.cpp
  ${SOURCE_DIR}/Core/Types.cpp
)

set(SOURCES_CODEANALYSIS_CORE
  ${SOURCE_DIR}/CodeAnalysis/CodeAnalysis.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/ISyntaxTree.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/LanguageKind.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/SyntaxFactory.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/SyntaxPool.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/SyntaxKinds.cpp
)

set(SOURCES_CODEANALYSIS_CORE_PARSER
  ${SOURCE_DIR}/CodeAnalysis/Core/Parser/CharFlags.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Parser/Directive.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Parser/DirectiveList.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Parser/DirectiveParser.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Parser/DirectiveStack.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Parser/Lexer.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Parser/LexerCache.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Parser/LexerMode.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Parser/Parser.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Parser/QuickScanState.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Parser/TextKeyedCache.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Parser/TokenInfo.cpp
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
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/ISyntaxList.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/ISyntaxNode.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/ISyntaxToken.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/ISyntaxTrivia.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/ISyntaxTriviaList.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/LanguageSyntaxList.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/LanguageSyntaxMissingToken.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/LanguageSyntaxNode.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/LanguageSyntaxToken.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/LanguageSyntaxTrivia.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/SyntaxList.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/SyntaxMissingToken.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/SyntaxNode.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/SyntaxNodeFlags.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/SyntaxToken.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/SyntaxTrivia.cpp
  ${SOURCE_DIR}/CodeAnalysis/Core/Syntax/SyntaxTriviaList.cpp
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
  ${SOURCE_DIR}/CodeAnalysis/Delphi/DelphiSyntaxTree.cpp
)

set(SOURCES_CODEANALYSIS_DELPHI_PARSER
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Parser/DelphiDirectiveParser.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Parser/DelphiLexer.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Parser/DelphiLexerFlags.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Parser/DelphiLexerStates.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Parser/DelphiParser.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Parser/DelphiSyntaxFacts.cpp
)

set(SOURCES_CODEANALYSIS_DELPHI_SYNTAX
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiCompilationUnitSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiEndOfModuleSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiPackageContainsClauseSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiPackageHeadSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiPackageModuleSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiPackageRequiresClauseSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiProgramHeadSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiProgramModuleSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiUsesClauseSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiUnitFinalizationSectionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiUnitHeadSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiUnitImplementationSectionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiUnitInitializationSectionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiUnitInterfaceSectionSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiUnitModuleSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiUnitReferenceDeclarationSyntax.cpp
  ${SOURCE_DIR}/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.cpp
)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(${PROJECT_NAME} SHARED)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
  ${SOURCES}
  ${SOURCES_CORE}
  ${SOURCES_CODEANALYSIS_CORE}
  ${SOURCES_CODEANALYSIS_CORE_PARSER}
  ${SOURCES_CODEANALYSIS_CORE_SYNTAX}
  ${SOURCES_CODEANALYSIS_CORE_TEXT}
  ${SOURCES_CODEANALYSIS_DELPHI_CORE}
  ${SOURCES_CODEANALYSIS_DELPHI_PARSER}
  ${SOURCES_CODEANALYSIS_DELPHI_SYNTAX}
)

target_compile_features(${PROJECT_NAME} PRIVATE ${CPP_STANDARD})

target_compile_options(${PROJECT_NAME}
  PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wno-switch -Wno-shift-count-overflow>
    $<$<CXX_COMPILER_ID:MSVC>:/w44265 /wd4251 /wd4293 /wd4297>
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
