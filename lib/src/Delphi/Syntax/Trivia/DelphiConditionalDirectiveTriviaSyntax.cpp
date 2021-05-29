#include "Delphi/Syntax/Trivia/DelphiConditionalDirectiveTriviaSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiConditionalDirectiveTriviaSyntax::DelphiConditionalDirectiveTriviaSyntax(Core::Syntax::SyntaxKind syntaxKind) noexcept
    : Core::Syntax::BranchingDirectiveTriviaSyntax{syntaxKind}
{}

} // end namespace polyglot::Delphi::Syntax
