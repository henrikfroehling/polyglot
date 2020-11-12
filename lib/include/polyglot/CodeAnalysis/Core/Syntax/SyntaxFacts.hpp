#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXFACTS_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXFACTS_H

#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API SyntaxFacts
{
public:
    virtual bool isPunctuation(SyntaxKind syntaxKind) const noexcept { return false; }
    virtual bool isCompoundPunctuation(SyntaxKind syntaxKind) const noexcept { return false; }
    virtual SyntaxKind binaryExpressionKind(SyntaxKind syntaxKind) const noexcept { return SyntaxKind::None; }
    virtual SyntaxKind literalExpressionKind(SyntaxKind syntaxKind) const noexcept { return SyntaxKind::None; }
    virtual bool isKeyword(SyntaxKind syntaxKind) const noexcept { return false; }
    virtual bool isModuleStart(SyntaxKind syntaxKind) const noexcept { return false; }
    virtual SyntaxKind keywordKind(std::string_view text) const noexcept { return SyntaxKind::None; }

protected:
    SyntaxFacts() noexcept = default;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXFACTS_H
