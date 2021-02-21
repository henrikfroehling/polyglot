#include "CodeAnalysis/Delphi/Syntax/DelphiUnitHeadSyntax.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxToken.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.hpp"
#include <cassert>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

DelphiUnitHeadSyntax::DelphiUnitHeadSyntax(ISyntaxToken* unitKeyword,
                                           NameExpressionSyntax* name,
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
    _pUnitKeyword->setChildNumber(0);
    adjustWidthAndFlags(_pName);
    _pName->setChildNumber(1);

    pg_size childNr{2};

    if (_pInKeyword != nullptr)
    {
        adjustWidthAndFlags(_pInKeyword);
        _pInKeyword->setChildNumber(childNr++);
    }

    if (_pFilename != nullptr)
    {
        assert(_pInKeyword != nullptr);
        adjustWidthAndFlags(_pFilename);
        _pFilename->setChildNumber(childNr++);
    }

    adjustWidthAndFlags(_pSemiColonToken);
    _pSemiColonToken->setChildNumber(childNr);
}

ISyntaxNode* DelphiUnitHeadSyntax::child(pg_size index) const
{
    switch (childCount())
    {
        case 3:
        {
            switch (index)
            {
                case 0: return _pUnitKeyword;
                case 1: return _pName;
                case 2: return _pSemiColonToken;
            }
        }
        case 5:
        {
            switch (index)
            {
                case 0: return _pUnitKeyword;
                case 1: return _pName;
                case 2: return _pInKeyword;
                case 3: return _pFilename;
                case 4: return _pSemiColonToken;
            }
        }
    }

    throw std::out_of_range{"index out of range"};
}

DelphiUnitHeadSyntax* DelphiUnitHeadSyntax::create(SyntaxFactory& syntaxFactory,
                                                   ISyntaxToken* unitKeyword,
                                                   NameExpressionSyntax* name,
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
    return dynamic_cast<DelphiUnitHeadSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrUnitHeadingSyntax)));
}

} // end namespace polyglot::CodeAnalysis
