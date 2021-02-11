#include "CodeAnalysis/Delphi/Syntax/DelphiUnitHeadSyntax.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

DelphiUnitHeadSyntax::DelphiUnitHeadSyntax(LanguageSyntaxToken* unitKeyword,
                                           NameExpressionSyntax* name,
                                           LanguageSyntaxToken* semiColonToken,
                                           LanguageSyntaxToken* inKeyword,
                                           LanguageSyntaxToken* filename) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitHead},
      _pUnitKeyword{unitKeyword},
      _pName{name},
      _pSemiColonToken{semiColonToken},
      _pInKeyword{inKeyword},
      _pFilename{filename}
{
    _position = _pUnitKeyword->position();
    adjustWidthAndFlags(_pUnitKeyword);
    adjustWidthAndFlags(_pName);
    adjustWidthAndFlags(_pSemiColonToken);

    if (_pInKeyword != nullptr)
        adjustWidthAndFlags(_pInKeyword);

    if (_pFilename != nullptr)
        adjustWidthAndFlags(_pFilename);
}

DelphiUnitHeadSyntax* DelphiUnitHeadSyntax::create(SyntaxFactory& syntaxFactory,
                                                   LanguageSyntaxToken* unitKeyword,
                                                   NameExpressionSyntax* name,
                                                   LanguageSyntaxToken* semiColonToken,
                                                   LanguageSyntaxToken* inKeyword,
                                                   LanguageSyntaxToken* filename) noexcept
{
    assert(unitKeyword != nullptr);
    assert(unitKeyword->syntaxKind() == SyntaxKind::UnitKeyword);
    assert(name != nullptr);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    if (inKeyword != nullptr)
    {
        assert(inKeyword->syntaxKind() == SyntaxKind::InKeyword);
        assert(filename != nullptr);
        assert(filename->syntaxKind() == SyntaxKind::SingleQuotationStringLiteralToken);
    }

    auto ptrUnitHeadingSyntax = std::make_unique<DelphiUnitHeadSyntax>(unitKeyword, name, semiColonToken, inKeyword, filename);
    return static_cast<DelphiUnitHeadSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrUnitHeadingSyntax)));
}

} // end namespace polyglot::CodeAnalysis
