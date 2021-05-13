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
    static bool isPunctuation(Core::Syntax::SyntaxKind syntaxKind) noexcept;
    static bool isCompoundPunctuation(Core::Syntax::SyntaxKind syntaxKind) noexcept;
    static Core::Syntax::SyntaxKind binaryExpressionKind(Core::Syntax::SyntaxKind syntaxKind) noexcept;
    static Core::Syntax::SyntaxKind literalExpressionKind(Core::Syntax::SyntaxKind syntaxKind) noexcept;
    static bool isComparisonSyntaxKind(Core::Syntax::SyntaxKind syntaxKind) noexcept;
    static bool isKeyword(Core::Syntax::SyntaxKind syntaxKind) noexcept;
    static bool isModuleStart(Core::Syntax::SyntaxKind syntaxKind) noexcept;

    static Core::Syntax::SyntaxKind keywordKind(std::string_view text,
                                                Core::Parser::LexerMode mode = Core::Parser::LexerMode::Syntax) noexcept;
};

} // end namespace polyglot::Delphi::Parser

#endif // POLYGLOT_DELPHI_PARSER_DELPHISYNTAXFACTS_H
