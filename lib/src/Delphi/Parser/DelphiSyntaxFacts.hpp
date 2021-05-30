#ifndef POLYGLOT_DELPHI_PARSER_DELPHISYNTAXFACTS_H
#define POLYGLOT_DELPHI_PARSER_DELPHISYNTAXFACTS_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"
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
    static bool isStatementStart(Core::Syntax::SyntaxKind syntaxKind) noexcept;
    static bool isPredefinedType(Core::Syntax::SyntaxKind syntaxKind) noexcept;

    static Core::Syntax::SyntaxKind keywordKind(pg_string_view text,
                                                Core::Parser::LexerMode mode = Core::Parser::LexerMode::Syntax) noexcept;
};

} // end namespace polyglot::Delphi::Parser

#endif // POLYGLOT_DELPHI_PARSER_DELPHISYNTAXFACTS_H
