#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIEXITSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIEXITSTATEMENTSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/Expressions/ParenthesizedExpressionSyntax.hpp"
#include "Delphi/Syntax/DelphiSimpleStatementSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiExitStatementSyntax : public DelphiSimpleStatementSyntax
{
public:
    explicit DelphiExitStatementSyntax(Core::Syntax::ISyntaxToken* exitKeyword,
                                       Core::Syntax::ParenthesizedExpressionSyntax* expression = nullptr) noexcept;

    virtual ~DelphiExitStatementSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* exitKeyword() const noexcept { return _pExitKeyword; }
    inline Core::Syntax::ParenthesizedExpressionSyntax* expression() const noexcept { return _pExpression; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pExitKeyword); }

    inline Core::Syntax::SyntaxVariant last() const noexcept override final
    {
        if (_pExpression != nullptr)
            return Core::Syntax::SyntaxVariant::asNode(_pExpression);

        return Core::Syntax::SyntaxVariant::asToken(_pExitKeyword);
    }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiExitStatementSyntax"; }

    inline bool isExitStatement() const noexcept override final { return true; }

    static DelphiExitStatementSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                             Core::Syntax::ISyntaxToken* exitKeyword,
                                             Core::Syntax::ParenthesizedExpressionSyntax* expression = nullptr) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pExitKeyword;
    Core::Syntax::ParenthesizedExpressionSyntax* _pExpression; // optional
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIEXITSTATEMENTSYNTAX_H
