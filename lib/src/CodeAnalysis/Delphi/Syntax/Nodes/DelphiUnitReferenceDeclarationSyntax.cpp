#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitReferenceDeclarationSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitReferenceDeclarationSyntax::DelphiUnitReferenceDeclarationSyntax(NameExpressionSyntax* unitName) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitReference},
      _pUnitName{unitName},
      _pInKeyword{nullptr},
      _pSourceFile{nullptr},
      _pCommaToken{nullptr}
{
    adjustWidthAndFlags(_pUnitName);
}

void DelphiUnitReferenceDeclarationSyntax::setInKeyword(LanguageSyntaxToken* inKeyword) noexcept
{
    _pInKeyword = inKeyword;
    adjustWidthAndFlags(_pInKeyword);
}

void DelphiUnitReferenceDeclarationSyntax::setSourceFile(LanguageSyntaxToken* sourceFile) noexcept
{
    _pSourceFile = sourceFile;
    adjustWidthAndFlags(_pSourceFile);
}

void DelphiUnitReferenceDeclarationSyntax::setCommaToken(LanguageSyntaxToken* commaToken) noexcept
{
    _pCommaToken = commaToken;
    adjustWidthAndFlags(_pCommaToken);
}

} // end namespace polyglot::CodeAnalysis
