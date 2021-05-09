#include "DelphiUnitReferenceDeclarationSyntax.hpp"
#include <cassert>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/Expressions/NameExpressionSyntax.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::ISyntaxToken;
using Core::Syntax::NameExpressionSyntax;
using Core::Syntax::SyntaxFactory;
using Core::Syntax::SyntaxKind;
using Core::Syntax::SyntaxNodeOrToken;

DelphiUnitReferenceDeclarationSyntax::DelphiUnitReferenceDeclarationSyntax(NameExpressionSyntax* unitName,
                                                                           ISyntaxToken* inKeyword,
                                                                           ISyntaxToken* sourceFile) noexcept
    : DelphiSyntaxList{SyntaxKind::UnitReference},
      _pUnitName{unitName},
      _pInKeyword{inKeyword},
      _pSourceFile{sourceFile}
{
    _position = _pUnitName->position();
    adjustWidthAndFlags(_pUnitName);

    if (_pInKeyword != nullptr)
        adjustWidthAndFlags(_pInKeyword);

    if (_pSourceFile != nullptr)
    {
        assert(_pInKeyword != nullptr);
        adjustWidthAndFlags(_pSourceFile);
    }
}

SyntaxNodeOrToken DelphiUnitReferenceDeclarationSyntax::child(pg_size index) const
{
    switch (childCount())
    {
        case 1:
        {
            if (index == 0)
                return SyntaxNodeOrToken::asNode(_pUnitName);
        }
        case 3:
        {
            switch (index)
            {
                case 0: return SyntaxNodeOrToken::asNode(_pUnitName);
                case 1: return SyntaxNodeOrToken::asToken(_pInKeyword);
                case 2: return SyntaxNodeOrToken::asToken(_pSourceFile);
            }
        }
    }

    throw std::out_of_range{"index out of range"};
}

DelphiUnitReferenceDeclarationSyntax* DelphiUnitReferenceDeclarationSyntax::create(SyntaxFactory& syntaxFactory,
                                                                                   NameExpressionSyntax* unitName,
                                                                                   ISyntaxToken* inKeyword,
                                                                                   ISyntaxToken* sourceFile) noexcept
{
    assert(unitName != nullptr);

    if (inKeyword != nullptr)
        assert(inKeyword->syntaxKind() == SyntaxKind::InKeyword);

    if (sourceFile != nullptr)
    {
        assert(inKeyword != nullptr);
        assert(sourceFile->syntaxKind() == SyntaxKind::SingleQuotationStringLiteralToken);
    }

    auto ptrUnitReferenceDeclarationSyntax = std::make_unique<DelphiUnitReferenceDeclarationSyntax>(unitName, inKeyword, sourceFile);
    return dynamic_cast<DelphiUnitReferenceDeclarationSyntax*>(syntaxFactory.addSyntaxList(std::move(ptrUnitReferenceDeclarationSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
