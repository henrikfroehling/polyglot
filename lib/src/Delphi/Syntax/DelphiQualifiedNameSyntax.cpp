#include "Delphi/Syntax/DelphiQualifiedNameSyntax.hpp"
#include <cassert>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/DelphiSimpleNameSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiQualifiedNameSyntax::DelphiQualifiedNameSyntax(DelphiNameSyntax* left,
                                                     ISyntaxToken* dotToken,
                                                     DelphiSimpleNameSyntax* right) noexcept
    : DelphiNameSyntax{SyntaxKind::QualifiedNameExpression},
      _pLeft{left},
      _pDotToken{dotToken},
      _pRight{right}
{
    _position = _pLeft->position();
    adjustWidthAndFlags(_pLeft);
    adjustWidthAndFlags(_pDotToken);
    adjustWidthAndFlags(_pRight);
}

SyntaxVariant DelphiQualifiedNameSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asNode(_pLeft);
        case 1: return SyntaxVariant::asToken(_pDotToken);
        case 2: return SyntaxVariant::asNode(_pRight);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiQualifiedNameSyntax* DelphiQualifiedNameSyntax::create(SyntaxFactory& syntaxFactory,
                                                             DelphiNameSyntax* left,
                                                             ISyntaxToken* dotToken,
                                                             DelphiSimpleNameSyntax* right) noexcept
{
    assert(left != nullptr);
    assert(dotToken != nullptr);
    assert(dotToken->syntaxKind() == SyntaxKind::DotToken);
    assert(right != nullptr);

    auto ptrQualifiedNameSyntax = std::make_unique<DelphiQualifiedNameSyntax>(left, dotToken, right);
    return static_cast<DelphiQualifiedNameSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrQualifiedNameSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
