#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHICONTINUESTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHICONTINUESTATEMENTSYNTAX_H

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

class DelphiContinueStatementSyntax : public DelphiSimpleStatementSyntax
{
public:
    explicit DelphiContinueStatementSyntax(Core::Syntax::ISyntaxToken* continueKeyword) noexcept;
    virtual ~DelphiContinueStatementSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* continueKeyword() const noexcept { return _pContinueKeyword; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pContinueKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pContinueKeyword); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiContinueStatementSyntax"; }

    inline bool isContinueStatement() const noexcept override final { return true; }

    static DelphiContinueStatementSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                 Core::Syntax::ISyntaxToken* continueKeyword) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pContinueKeyword;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHICONTINUESTATEMENTSYNTAX_H
