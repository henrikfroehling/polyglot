#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXFACTS_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXFACTS_H

#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiSyntaxFacts
{
public:
    static bool isPunctuation(SyntaxKind syntaxKind) noexcept;
    static bool isCompoundPunctuation(SyntaxKind syntaxKind) noexcept;
    static SyntaxKind binaryExpressionKind(SyntaxKind syntaxKind) noexcept;
    static SyntaxKind literalExpressionKind(SyntaxKind syntaxKind) noexcept;
    static bool isKeyword(SyntaxKind syntaxKind) noexcept;
    static bool isModuleStart(SyntaxKind syntaxKind) noexcept;
    static SyntaxKind keywordKind(std::string_view text) noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXFACTS_H
