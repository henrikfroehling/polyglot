#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXFACTS_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXFACTS_H

#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxFacts.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiSyntaxFacts : public SyntaxFacts
{
public:
    bool isPunctuation(SyntaxKind syntaxKind) const noexcept override;
    bool isCompoundPunctuation(SyntaxKind syntaxKind) const noexcept override;
    SyntaxKind binaryExpressionKind(SyntaxKind syntaxKind) const noexcept override;
    SyntaxKind literalExpressionKind(SyntaxKind syntaxKind) const noexcept override;
    bool isKeyword(SyntaxKind syntaxKind) const noexcept override;
    bool isModuleStart(SyntaxKind syntaxKind) const noexcept override;
    SyntaxKind keywordKind(std::string_view text) const noexcept override;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXFACTS_H
