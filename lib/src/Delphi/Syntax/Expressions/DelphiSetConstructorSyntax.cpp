#include "Delphi/Syntax/Expressions/DelphiSetConstructorSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiSetConstructorSyntax::DelphiSetConstructorSyntax(Core::Syntax::SyntaxKind syntaxKind,
                                                       Core::Syntax::ISyntaxToken* openBracketToken,
                                                       Core::Syntax::ISyntaxToken* closeBracketToken) noexcept
    : DelphiExpressionSyntax{syntaxKind},
      _pOpenBracketToken{openBracketToken},
      _pCloseBracketToken{closeBracketToken}
{}

} // end namespace polyglot::Delphi::Syntax
