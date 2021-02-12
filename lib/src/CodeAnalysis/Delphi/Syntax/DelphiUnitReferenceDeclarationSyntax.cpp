#include "CodeAnalysis/Delphi/Syntax/DelphiUnitReferenceDeclarationSyntax.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.hpp"
#include <cassert>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

DelphiUnitReferenceDeclarationSyntax::DelphiUnitReferenceDeclarationSyntax(NameExpressionSyntax* unitName,
                                                                           LanguageSyntaxToken* inKeyword,
                                                                           LanguageSyntaxToken* sourceFile) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitReference},
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

LanguageSyntaxNode* DelphiUnitReferenceDeclarationSyntax::child(pg_size index) const
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
                                                                                   LanguageSyntaxToken* inKeyword,
                                                                                   LanguageSyntaxToken* sourceFile) noexcept
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
    return static_cast<DelphiUnitReferenceDeclarationSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrUnitReferenceDeclarationSyntax)));
}

} // end namespace polyglot::CodeAnalysis
