#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiQualifiedNameSyntax.hpp"

namespace polyglot::CodeAnalysis
{

DelphiQualifiedNameSyntax::DelphiQualifiedNameSyntax(SyntaxKind syntaxKind,
                                                     std::shared_ptr<DelphiNameSyntax> left,
                                                     std::shared_ptr<SyntaxToken> dotToken,
                                                     std::shared_ptr<DelphiSimpleNameSyntax> right) noexcept
    : DelphiNameSyntax{syntaxKind},
     _ptrLeft{std::move(left)},
     _ptrDotToken{std::move(dotToken)},
     _ptrRight{std::move(right)}
{}

} // end namespace polyglot::CodeAnalysis
