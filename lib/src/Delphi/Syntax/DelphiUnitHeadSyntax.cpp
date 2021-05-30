#include "Delphi/Syntax/DelphiUnitHeadSyntax.hpp"
#include <cassert>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax//DelphiNameSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::ISyntaxToken;
using Core::Syntax::SyntaxFactory;
using Core::Syntax::SyntaxKind;
using Core::Syntax::SyntaxVariant;

DelphiUnitHeadSyntax::DelphiUnitHeadSyntax(ISyntaxToken* unitKeyword,
                                           DelphiNameSyntax* name,
                                           ISyntaxToken* semiColonToken,
                                           ISyntaxToken* inKeyword,
                                           ISyntaxToken* filename) noexcept
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

    if (_pInKeyword != nullptr)
        adjustWidthAndFlags(_pInKeyword);

    if (_pFilename != nullptr)
    {
        assert(_pInKeyword != nullptr);
        adjustWidthAndFlags(_pFilename);
    }

    adjustWidthAndFlags(_pSemiColonToken);
}

SyntaxVariant DelphiUnitHeadSyntax::child(pg_size index) const
{
    switch (childCount())
    {
        case 3:
        {
            switch (index)
            {
                case 0: return SyntaxVariant::asToken(_pUnitKeyword);
                case 1: return SyntaxVariant::asNode(_pName);
                case 2: return SyntaxVariant::asToken(_pSemiColonToken);
            }
        }
        case 5:
        {
            switch (index)
            {
                case 0: return SyntaxVariant::asToken(_pUnitKeyword);
                case 1: return SyntaxVariant::asNode(_pName);
                case 2: return SyntaxVariant::asToken(_pInKeyword);
                case 3: return SyntaxVariant::asToken(_pFilename);
                case 4: return SyntaxVariant::asToken(_pSemiColonToken);
            }
        }
    }

    throw std::out_of_range{"index out of range"};
}

DelphiUnitHeadSyntax* DelphiUnitHeadSyntax::create(SyntaxFactory& syntaxFactory,
                                                   ISyntaxToken* unitKeyword,
                                                   DelphiNameSyntax* name,
                                                   ISyntaxToken* semiColonToken,
                                                   ISyntaxToken* inKeyword,
                                                   ISyntaxToken* filename) noexcept
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

} // end namespace polyglot::Delphi::Syntax
