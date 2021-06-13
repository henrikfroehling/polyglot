#include "Delphi/Syntax/Statements/DelphiForStatementSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiForStatementSyntax::DelphiForStatementSyntax(Core::Syntax::SyntaxKind syntaxKind,
                                                   Core::Syntax::ISyntaxToken* forKeyword,
                                                   Core::Syntax::ISyntaxToken* doKeyword,
                                                   DelphiStatementSyntax* statement) noexcept
    : DelphiStatementSyntax{syntaxKind},
      _pForKeyword{forKeyword},
      _pDoKeyword{doKeyword},
      _pStatement{statement}
{}

} // end namespace polyglot::Delphi::Syntax
