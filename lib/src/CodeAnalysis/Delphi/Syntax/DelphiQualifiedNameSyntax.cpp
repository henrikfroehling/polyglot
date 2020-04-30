#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiQualifiedNameSyntax.hpp"

namespace polyglot::CodeAnalysis
{

DelphiQualifiedNameSyntax::DelphiQualifiedNameSyntax(SyntaxKind syntaxKind,
                                                     DelphiNameSyntax* left,
                                                     SyntaxToken dotToken,
                                                     DelphiSimpleNameSyntax* right) noexcept
    : DelphiNameSyntax{syntaxKind},
     _left{left},
     _dotToken{dotToken},
     _right{right}
{}

} // end namespace polyglot::CodeAnalysis
