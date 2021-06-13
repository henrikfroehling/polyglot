#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_FORINSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_FORINSTATEMENTSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Statements/DelphiForStatementSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiExpressionSyntax;
class DelphiStatementSyntax;

class DelphiForInStatementSyntax : public DelphiForStatementSyntax
{
public:
    explicit DelphiForInStatementSyntax(Core::Syntax::ISyntaxToken* forKeyword,
                                        DelphiExpressionSyntax* elementExpression,
                                        Core::Syntax::ISyntaxToken* inKeyword,
                                        DelphiExpressionSyntax* collectionExpression,
                                        Core::Syntax::ISyntaxToken* doKeyword,
                                        DelphiStatementSyntax* statement) noexcept;

    virtual ~DelphiForInStatementSyntax() noexcept {}

    inline DelphiExpressionSyntax* elementExpression() const noexcept { return _pElementExpression; }
    inline Core::Syntax::ISyntaxToken* inKeyword() const noexcept { return _pInKeyword; }
    inline DelphiExpressionSyntax* collectionExpression() const noexcept { return _pCollectionExpression; }

    inline pg_size childCount() const noexcept override final { return 6; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline virtual pg_string typeName() const noexcept override { return L"DelphiForInStatementSyntax"; }
    inline bool isForInStatement() const noexcept override final { return true; }

    static DelphiForInStatementSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                              Core::Syntax::ISyntaxToken* forKeyword,
                                              DelphiExpressionSyntax* elementExpression,
                                              Core::Syntax::ISyntaxToken* inKeyword,
                                              DelphiExpressionSyntax* collectionExpression,
                                              Core::Syntax::ISyntaxToken* doKeyword,
                                              DelphiStatementSyntax* statement) noexcept;

private:
    DelphiExpressionSyntax* _pElementExpression;
    Core::Syntax::ISyntaxToken* _pInKeyword;
    DelphiExpressionSyntax* _pCollectionExpression;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_FORINSTATEMENTSYNTAX_H
