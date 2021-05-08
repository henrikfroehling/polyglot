#ifndef POLYGLOT_DELPHI_PARSER_DELPHISYNTAXFACTS_H
#define POLYGLOT_DELPHI_PARSER_DELPHISYNTAXFACTS_H

#include <string_view>
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Parser/LexerMode.hpp"

namespace polyglot::Delphi::Parser
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

} // end namespace polyglot::Delphi::Parser

#endif // POLYGLOT_DELPHI_PARSER_DELPHISYNTAXFACTS_H
