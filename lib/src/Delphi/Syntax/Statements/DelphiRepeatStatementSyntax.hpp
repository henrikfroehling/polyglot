#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIREPEATSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIREPEATSTATEMENTSYNTAX_H

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

class DelphiRepeatStatementSyntax : public DelphiStatementSyntax
{
public:
    explicit DelphiRepeatStatementSyntax(Core::Syntax::ISyntaxToken* repeatKeyword,
                                         DelphiStatementSyntax* statement,
                                         Core::Syntax::ISyntaxToken* untilKeyword,
                                         DelphiExpressionSyntax* expression,
                                         Core::Syntax::ISyntaxToken* semiColonToken) noexcept;

    virtual ~DelphiRepeatStatementSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* repeatKeyword() const noexcept { return _pRepeatKeyword; }
    inline DelphiStatementSyntax* statement() const noexcept { return _pStatement; }
    inline Core::Syntax::ISyntaxToken* untilKeyword() const noexcept { return _pUntilKeyword; }
    inline DelphiExpressionSyntax* expression() const noexcept { return _pExpression; }
    inline Core::Syntax::ISyntaxToken* semiColonToken() const noexcept { return _pSemiColonToken; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pRepeatKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pSemiColonToken); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiRepeatStatementSyntax"; }

    inline bool isRepeatStatement() const noexcept override final { return true; }

    static DelphiRepeatStatementSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                               Core::Syntax::ISyntaxToken* repeatKeyword,
                                               DelphiStatementSyntax* statement,
                                               Core::Syntax::ISyntaxToken* untilKeyword,
                                               DelphiExpressionSyntax* expression,
                                               Core::Syntax::ISyntaxToken* semiColonToken) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pRepeatKeyword;
    DelphiStatementSyntax* _pStatement;
    Core::Syntax::ISyntaxToken* _pUntilKeyword;
    DelphiExpressionSyntax* _pExpression;
    Core::Syntax::ISyntaxToken* _pSemiColonToken;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIREPEATSTATEMENTSYNTAX_H
