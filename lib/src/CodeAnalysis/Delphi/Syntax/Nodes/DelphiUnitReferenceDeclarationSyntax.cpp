#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitReferenceDeclarationSyntax.hpp"
#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxPool.hpp"
#include "CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

DelphiUnitReferenceDeclarationSyntax::DelphiUnitReferenceDeclarationSyntax(NameExpressionSyntax* unitName,
                                                                           LanguageSyntaxToken* inKeyword,
                                                                           LanguageSyntaxToken* sourceFile,
                                                                           LanguageSyntaxToken* commaToken) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitReference},
      _pUnitName{unitName},
      _pInKeyword{inKeyword},
      _pSourceFile{sourceFile},
      _pCommaToken{commaToken}
{
    adjustWidthAndFlags(_pUnitName);

    if (_pInKeyword != nullptr)
        adjustWidthAndFlags(_pInKeyword);

    if (_pSourceFile != nullptr)
        adjustWidthAndFlags(_pSourceFile);

    if (_pCommaToken != nullptr)
        adjustWidthAndFlags(_pCommaToken);
}

DelphiUnitReferenceDeclarationSyntax* DelphiUnitReferenceDeclarationSyntax::create(NameExpressionSyntax* unitName,
                                                                                   LanguageSyntaxToken* inKeyword,
                                                                                   LanguageSyntaxToken* sourceFile,
                                                                                   LanguageSyntaxToken* commaToken) noexcept
{
    assert(unitName != nullptr);

    if (inKeyword != nullptr)
        assert(inKeyword->syntaxKind() == SyntaxKind::InKeyword);

    if (sourceFile != nullptr)
        assert(sourceFile->syntaxKind() == SyntaxKind::SingleQuotationStringLiteralToken);

    if (commaToken != nullptr)
        assert(commaToken->syntaxKind() == SyntaxKind::CommaToken);

    auto ptrUnitReferenceDeclarationSyntax = std::make_unique<DelphiUnitReferenceDeclarationSyntax>(unitName, inKeyword, sourceFile, commaToken);
    return static_cast<DelphiUnitReferenceDeclarationSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrUnitReferenceDeclarationSyntax)));
}

} // end namespace polyglot::CodeAnalysis
