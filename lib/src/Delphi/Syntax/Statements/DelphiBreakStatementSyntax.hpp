#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIBREAKSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIBREAKSTATEMENTSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Statements/DelphiSimpleStatementSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiBreakStatementSyntax : public DelphiSimpleStatementSyntax
{
public:
    explicit DelphiBreakStatementSyntax(Core::Syntax::ISyntaxToken* breakKeyword) noexcept;
    virtual ~DelphiBreakStatementSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* breakKeyword() const noexcept { return _pBreakKeyword; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pBreakKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pBreakKeyword); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiBreakStatementSyntax"; }

    inline bool isBreakStatement() const noexcept override final { return true; }

    static DelphiBreakStatementSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                              Core::Syntax::ISyntaxToken* breakKeyword) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pBreakKeyword;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIBREAKSTATEMENTSYNTAX_H
