#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIRAISESTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIRAISESTATEMENTSYNTAX_H

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

class DelphiRaiseStatementSyntax : public DelphiStatementSyntax
{
public:
    explicit DelphiRaiseStatementSyntax(Core::Syntax::ISyntaxToken* raiseKeyword,
                                        DelphiExpressionSyntax* expression,
                                        Core::Syntax::ISyntaxToken* semiColonToken) noexcept;

    virtual ~DelphiRaiseStatementSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* raiseKeyword() const noexcept { return _pRaiseKeyword; }
    inline DelphiExpressionSyntax* expression() const noexcept { return _pExpression; }
    inline Core::Syntax::ISyntaxToken* semiColonToken() const noexcept { return _pSemiColonToken; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pRaiseKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pSemiColonToken); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiRaiseStatementSyntax"; }

    inline bool isRaiseStatement() const noexcept override final { return true; }

    static DelphiRaiseStatementSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                              Core::Syntax::ISyntaxToken* raiseKeyword,
                                              DelphiExpressionSyntax* expression,
                                              Core::Syntax::ISyntaxToken* semiColonToken) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pRaiseKeyword;
    DelphiExpressionSyntax* _pExpression;
    Core::Syntax::ISyntaxToken* _pSemiColonToken;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIRAISESTATEMENTSYNTAX_H
