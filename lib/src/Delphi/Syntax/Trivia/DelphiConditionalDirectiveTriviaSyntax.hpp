#ifndef POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHICONDITIONALDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHICONDITIONALDIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/Trivia/BranchingDirectiveTriviaSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiExpressionSyntax;

class DelphiConditionalDirectiveTriviaSyntax : public Core::Syntax::BranchingDirectiveTriviaSyntax
{
public:
    explicit DelphiConditionalDirectiveTriviaSyntax(Core::Syntax::SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiConditionalDirectiveTriviaSyntax() noexcept {}
    virtual DelphiExpressionSyntax* condition() const noexcept = 0;
    virtual bool conditionValue() const noexcept = 0;

    inline virtual pg_string typeName() const noexcept override { return L"DelphiConditionalDirectiveTriviaSyntax"; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHICONDITIONALDIRECTIVETRIVIASYNTAX_H
