#include "CodeAnalysis/Delphi/Syntax/DelphiUnitReferenceDeclarationSyntax.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxToken.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.hpp"
#include <cassert>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

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
    _pUnitName->setChildNumber(0);

    pg_size childNr{1};

    if (_pInKeyword != nullptr)
    {
        adjustWidthAndFlags(_pInKeyword);
        _pInKeyword->setChildNumber(childNr++);
    }

    if (_pSourceFile != nullptr)
    {
        assert(_pInKeyword != nullptr);
        adjustWidthAndFlags(_pSourceFile);
        _pSourceFile->setChildNumber(childNr);
    }
}

ISyntaxNode* DelphiUnitReferenceDeclarationSyntax::child(pg_size index) const
{
    switch (childCount())
    {
        case 1:
        {
            if (index == 0)
                return _pUnitName;
        }
        case 3:
        {
            switch (index)
            {
                case 0: return _pUnitName;
                case 1: return _pInKeyword;
                case 2: return _pSourceFile;
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
    return dynamic_cast<DelphiUnitReferenceDeclarationSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrUnitReferenceDeclarationSyntax)));
}

} // end namespace polyglot::CodeAnalysis
