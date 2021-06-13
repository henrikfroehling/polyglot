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
  ${SOURCE_DIR}/Core/LanguageKind.cpp
  ${SOURCE_DIR}/Core/Types.cpp
)

set(SOURCES_CORE_PARSER
  ${SOURCE_DIR}/Core/Parser/CharFlags.cpp
  ${SOURCE_DIR}/Core/Parser/Directive.cpp
  ${SOURCE_DIR}/Core/Parser/DirectiveList.cpp
  ${SOURCE_DIR}/Core/Parser/DirectiveParser.cpp
  ${SOURCE_DIR}/Core/Parser/DirectiveStack.cpp
  ${SOURCE_DIR}/Core/Parser/Lexer.cpp
  ${SOURCE_DIR}/Core/Parser/LexerCache.cpp
  ${SOURCE_DIR}/Core/Parser/LexerMode.cpp
  ${SOURCE_DIR}/Core/Parser/Parser.cpp
  ${SOURCE_DIR}/Core/Parser/QuickScanState.cpp
  ${SOURCE_DIR}/Core/Parser/TextKeyedCache.cpp
  ${SOURCE_DIR}/Core/Parser/TokenInfo.cpp
)

set(SOURCES_CORE_SYNTAX
  ${SOURCE_DIR}/Core/Syntax/ExpressionSyntax.cpp
  ${SOURCE_DIR}/Core/Syntax/ISyntaxList.cpp
  ${SOURCE_DIR}/Core/Syntax/ISyntaxNode.cpp
  ${SOURCE_DIR}/Core/Syntax/ISyntaxToken.cpp
  ${SOURCE_DIR}/Core/Syntax/ISyntaxTree.cpp
  ${SOURCE_DIR}/Core/Syntax/ISyntaxTrivia.cpp
  ${SOURCE_DIR}/Core/Syntax/ISyntaxTriviaList.cpp
  ${SOURCE_DIR}/Core/Syntax/SyntaxFactory.cpp
  ${SOURCE_DIR}/Core/Syntax/SyntaxFlags.cpp
  ${SOURCE_DIR}/Core/Syntax/SyntaxKinds.cpp
  ${SOURCE_DIR}/Core/Syntax/SyntaxList.cpp
  ${SOURCE_DIR}/Core/Syntax/SyntaxMissingToken.cpp
  ${SOURCE_DIR}/Core/Syntax/SyntaxNode.cpp
  ${SOURCE_DIR}/Core/Syntax/SyntaxPool.cpp
  ${SOURCE_DIR}/Core/Syntax/SyntaxToken.cpp
  ${SOURCE_DIR}/Core/Syntax/SyntaxTree.cpp
  ${SOURCE_DIR}/Core/Syntax/SyntaxTrivia.cpp
  ${SOURCE_DIR}/Core/Syntax/SyntaxTriviaList.cpp
  ${SOURCE_DIR}/Core/Syntax/SyntaxVariant.cpp
)

set(SOURCES_CORE_SYNTAX_TRIVIA
  ${SOURCE_DIR}/Core/Syntax/Trivia/BranchingDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/Core/Syntax/Trivia/DefineDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/Core/Syntax/Trivia/DirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/Core/Syntax/Trivia/SkippedTokensTriviaSyntax.cpp
  ${SOURCE_DIR}/Core/Syntax/Trivia/StructuredTriviaSyntax.cpp
  ${SOURCE_DIR}/Core/Syntax/Trivia/UndefDirectiveTriviaSyntax.cpp
)

set(SOURCES_CORE_TEXT
  ${SOURCE_DIR}/Core/Text/LinePosition.cpp
  ${SOURCE_DIR}/Core/Text/LinePositionSpan.cpp
  ${SOURCE_DIR}/Core/Text/SourceText.cpp
  ${SOURCE_DIR}/Core/Text/TextSpan.cpp
  ${SOURCE_DIR}/Core/Text/TextUtilities.cpp
  ${SOURCE_DIR}/Core/Text/TextWindow.cpp
)

set(SOURCES_DELPHI_PARSER
  ${SOURCE_DIR}/Delphi/Parser/DelphiDirectiveParser.cpp
  ${SOURCE_DIR}/Delphi/Parser/DelphiLexer.cpp
  ${SOURCE_DIR}/Delphi/Parser/DelphiLexerFlags.cpp
  ${SOURCE_DIR}/Delphi/Parser/DelphiLexerStates.cpp
  ${SOURCE_DIR}/Delphi/Parser/DelphiParser.cpp
)

set(SOURCES_DELPHI_SYNTAX
  ${SOURCE_DIR}/Delphi/Syntax/DelphiCaseElseClauseSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiCaseItemListSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiCaseItemSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiCaseLabelListSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiCaseLabelSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiCompilationUnitSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiElseClauseSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiEndOfModuleDeclarationSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiExceptClauseSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiExceptionBlockSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiExceptionHandlerBlockSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiExceptionStatementBlockSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiFinallyClauseSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiPackageContainsClauseSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiPackageHeadSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiPackageModuleSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiPackageRequiresClauseSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiProgramHeadSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiProgramModuleSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiSyntaxFacts.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiSyntaxList.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiSyntaxNode.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiSyntaxTree.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiTryElseClauseSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiUnitFinalizationSectionSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiUnitHeadSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiUnitImplementationSectionSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiUnitInitializationSectionSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiUnitInterfaceSectionSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiUnitModuleSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiUnitReferenceDeclarationSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/DelphiUsesClauseSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/IDelphiSyntaxTree.cpp
)

set(SOURCES_DELPHI_SYNTAX_EXPRESSIONS
  ${SOURCE_DIR}/Delphi/Syntax/Expressions/DelphiAssignmentExpressionSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Expressions/DelphiBinaryExpressionSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Expressions/DelphiCallExpressionSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Expressions/DelphiExpressionSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Expressions/DelphiExtendedIdentifierNameSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Expressions/DelphiIdentifierNameSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Expressions/DelphiLiteralExpressionSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Expressions/DelphiNameSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Expressions/DelphiParenthesizedExpressionSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Expressions/DelphiPointerTypeSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Expressions/DelphiPredefinedTypeSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Expressions/DelphiPrefixUnaryExpressionSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Expressions/DelphiQualifiedNameSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Expressions/DelphiSimpleNameSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Expressions/DelphiTypeSyntax.cpp
)

set(SOURCES_DELPHI_SYNTAX_STATEMENTS
  ${SOURCE_DIR}/Delphi/Syntax/Statements/DelphiAssemblerStatementSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Statements/DelphiBlockStatementSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Statements/DelphiBreakStatementSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Statements/DelphiCaseStatementSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Statements/DelphiContinueStatementSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Statements/DelphiExceptionHandlerStatementSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Statements/DelphiExitStatementSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Statements/DelphiExpressionStatementSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Statements/DelphiForInStatementSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Statements/DelphiForStatementSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Statements/DelphiForToStatementSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Statements/DelphiGotoStatementSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Statements/DelphiIfStatementSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Statements/DelphiLabeledStatementSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Statements/DelphiRaiseStatementSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Statements/DelphiRepeatStatementSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Statements/DelphiStatementListSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Statements/DelphiStatementSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Statements/DelphiTryExceptStatementSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Statements/DelphiTryFinallyStatementSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Statements/DelphiTryStatementSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Statements/DelphiWhileStatementSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Statements/DelphiWithStatementSyntax.cpp
)

set(SOURCES_DELPHI_SYNTAX_TRIVIA
  ${SOURCE_DIR}/Delphi/Syntax/Trivia/DelphiBadDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Trivia/DelphiConditionalDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Trivia/DelphiDefineDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Trivia/DelphiElseDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Trivia/DelphiElseIfDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Trivia/DelphiEndIfDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Trivia/DelphiEndRegionDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Trivia/DelphiIfDefDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Trivia/DelphiIfDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Trivia/DelphiIfEndDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Trivia/DelphiIfNDefDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Trivia/DelphiMessageDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Trivia/DelphiRegionDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Trivia/DelphiSwitchDirectiveTriviaSyntax.cpp
  ${SOURCE_DIR}/Delphi/Syntax/Trivia/DelphiUndefDirectiveTriviaSyntax.cpp
)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(${PROJECT_NAME} SHARED)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
  ${SOURCES}
  ${SOURCES_CORE}
  ${SOURCES_CORE_PARSER}
  ${SOURCES_CORE_SYNTAX}
  ${SOURCES_CORE_SYNTAX_TRIVIA}
  ${SOURCES_CORE_TEXT}
  ${SOURCES_DELPHI_PARSER}
  ${SOURCES_DELPHI_SYNTAX}
  ${SOURCES_DELPHI_SYNTAX_EXPRESSIONS}
  ${SOURCES_DELPHI_SYNTAX_STATEMENTS}
  ${SOURCES_DELPHI_SYNTAX_TRIVIA}
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
