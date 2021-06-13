#ifndef POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIEXCEPTIONHANDLERSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIEXCEPTIONHANDLERSTATEMENTSYNTAX_H

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

class DelphiExpressionSyntax;

class DelphiExceptionHandlerStatementSyntax : public DelphiStatementSyntax
{
public:
    explicit DelphiExceptionHandlerStatementSyntax(Core::Syntax::ISyntaxToken* onKeyword,
                                                   DelphiExpressionSyntax* expression,
                                                   Core::Syntax::ISyntaxToken* doKeyword,
                                                   DelphiStatementSyntax* statement,
                                                   Core::Syntax::ISyntaxToken* semiColonToken) noexcept;

    virtual ~DelphiExceptionHandlerStatementSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* onKeyword() const noexcept { return _pOnKeyword; }
    inline DelphiExpressionSyntax* expression() const noexcept { return _pExpression; }
    inline Core::Syntax::ISyntaxToken* doKeyword() const noexcept { return _pDoKeyword; }
    inline DelphiStatementSyntax* statement() const noexcept { return _pStatement; }
    inline Core::Syntax::ISyntaxToken* semiColonToken() const noexcept { return _pSemiColonToken; }

    inline pg_size childCount() const noexcept override final { return 5; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pOnKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pSemiColonToken); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiExceptionHandlerStatementSyntax"; }

    static DelphiExceptionHandlerStatementSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                         Core::Syntax::ISyntaxToken* onKeyword,
                                                         DelphiExpressionSyntax* expression,
                                                         Core::Syntax::ISyntaxToken* doKeyword,
                                                         DelphiStatementSyntax* statement,
                                                         Core::Syntax::ISyntaxToken* semiColonToken) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pOnKeyword;
    DelphiExpressionSyntax* _pExpression;
    Core::Syntax::ISyntaxToken* _pDoKeyword;
    DelphiStatementSyntax* _pStatement;
    Core::Syntax::ISyntaxToken* _pSemiColonToken;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIEXCEPTIONHANDLERSTATEMENTSYNTAX_H
