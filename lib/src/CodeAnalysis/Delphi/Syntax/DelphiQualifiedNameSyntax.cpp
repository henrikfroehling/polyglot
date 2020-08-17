#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiQualifiedNameSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiQualifiedNameSyntax::DelphiQualifiedNameSyntax(DelphiNameSyntaxPtr left,
                                                     SyntaxTokenPtr dotToken,
                                                     DelphiSimpleNameSyntaxPtr right) noexcept
    : DelphiNameSyntax{SyntaxKind::QualifiedName},
      _ptrLeft{std::move(left)},
      _ptrDotToken{std::move(dotToken)},
      _ptrRight{std::move(right)}
{}

} // end namespace polyglot::CodeAnalysis
