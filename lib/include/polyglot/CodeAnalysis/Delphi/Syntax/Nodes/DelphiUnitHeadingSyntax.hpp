#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITHEADINGSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITHEADINGSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiUnitHeadingSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitHeadingSyntax(Ptr<SyntaxToken> unitKeyword,
                                     Ptr<NameExpressionSyntax> name,
                                     Ptr<SyntaxToken> semiColonToken) noexcept;

    virtual ~DelphiUnitHeadingSyntax() noexcept = default;
    const Ptr<SyntaxToken> unitKeyword() const noexcept { return _ptrUnitKeyword; }
    const Ptr<NameExpressionSyntax> name() const noexcept { return _ptrName; }
    const Ptr<SyntaxToken> semiColonToken() const noexcept { return _ptrSemiColonToken; }

private:
    Ptr<SyntaxToken> _ptrUnitKeyword;
    Ptr<NameExpressionSyntax> _ptrName;
    Ptr<SyntaxToken> _ptrSemiColonToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITHEADINGSYNTAX_H
