#ifndef POLYGLOT_CODEANALYSIS_DELPHI_PARSER_DELPHISYNTAXFACTS_H
#define POLYGLOT_CODEANALYSIS_DELPHI_PARSER_DELPHISYNTAXFACTS_H

#include <string_view>
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Parser/LexerMode.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiSyntaxFacts
{
public:
    static bool isPunctuation(SyntaxKind syntaxKind) noexcept;
    static bool isCompoundPunctuation(SyntaxKind syntaxKind) noexcept;
    static SyntaxKind binaryExpressionKind(SyntaxKind syntaxKind) noexcept;
    static SyntaxKind literalExpressionKind(SyntaxKind syntaxKind) noexcept;
    static bool isComparisonSyntaxKind(SyntaxKind syntaxKind) noexcept;
    static bool isKeyword(SyntaxKind syntaxKind) noexcept;
    static bool isModuleStart(SyntaxKind syntaxKind) noexcept;

    static SyntaxKind keywordKind(std::string_view text,
                                  LexerMode mode = LexerMode::Syntax) noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_PARSER_DELPHISYNTAXFACTS_H
