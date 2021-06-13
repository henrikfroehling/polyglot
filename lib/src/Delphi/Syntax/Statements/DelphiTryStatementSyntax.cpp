#include "Delphi/Syntax/Statements/DelphiTryStatementSyntax.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiTryStatementSyntax::DelphiTryStatementSyntax(Core::Syntax::SyntaxKind syntaxKind,
                                                   Core::Syntax::ISyntaxToken* tryKeyword,
                                                   DelphiStatementListSyntax* statements,
                                                   Core::Syntax::ISyntaxToken* endKeyword,
                                                   Core::Syntax::ISyntaxToken* semiColonToken) noexcept
    : DelphiStatementSyntax{syntaxKind},
      _pTryKeyword{tryKeyword},
      _pStatements{statements},
      _pEndKeyword{endKeyword},
      _pSemiColonToken{semiColonToken}
{}

} // end namespace polyglot::Delphi::Syntax
