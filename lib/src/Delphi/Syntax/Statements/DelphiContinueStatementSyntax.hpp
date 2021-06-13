#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHICONTINUESTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHICONTINUESTATEMENTSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiContinueStatementSyntax : public DelphiStatementSyntax
{
public:
    explicit DelphiContinueStatementSyntax(Core::Syntax::ISyntaxToken* continueKeyword,
                                           Core::Syntax::ISyntaxToken* semiColonToken) noexcept;

    virtual ~DelphiContinueStatementSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* continueKeyword() const noexcept { return _pContinueKeyword; }
    inline Core::Syntax::ISyntaxToken* semiColonToken() const noexcept { return _pSemiColonToken; }

    inline pg_size childCount() const noexcept override final { return 2; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pContinueKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pSemiColonToken); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiContinueStatementSyntax"; }

    inline bool isContinueStatement() const noexcept override final { return true; }

    static DelphiContinueStatementSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                 Core::Syntax::ISyntaxToken* continueKeyword,
                                                 Core::Syntax::ISyntaxToken* semiColonToken) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pContinueKeyword;
    Core::Syntax::ISyntaxToken* _pSemiColonToken;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHICONTINUESTATEMENTSYNTAX_H
