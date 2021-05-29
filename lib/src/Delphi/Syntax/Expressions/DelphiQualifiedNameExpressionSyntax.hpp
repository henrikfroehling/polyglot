#ifndef POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIQUALIFIEDNAMEEXPRESSIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIQUALIFIEDNAMEEXPRESSIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Expressions/DelphiNameExpressionSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiSimpleNameExpressionSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiQualifiedNameExpressionSyntax : public DelphiNameExpressionSyntax
{
public:
    explicit DelphiQualifiedNameExpressionSyntax(DelphiNameExpressionSyntax* leftExpression,
                                                 Core::Syntax::ISyntaxToken* dotToken,
                                                 DelphiSimpleNameExpressionSyntax* rightExpression) noexcept;

    virtual ~DelphiQualifiedNameExpressionSyntax() noexcept {}
    inline virtual DelphiNameExpressionSyntax* leftExpression() const noexcept { return _pLeftExpression; }
    inline virtual Core::Syntax::ISyntaxToken* dotToken() const noexcept { return _pDotToken; }
    inline virtual DelphiSimpleNameExpressionSyntax* rightExpression() const noexcept { return _pRightExpression; }
    inline pg_size childCount() const noexcept override final { return 3; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;
    inline virtual Core::Syntax::SyntaxVariant first() const noexcept override { return Core::Syntax::SyntaxVariant::asNode(_pLeftExpression); }
    inline virtual Core::Syntax::SyntaxVariant last() const noexcept override { return Core::Syntax::SyntaxVariant::asNode(_pRightExpression); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiQualifiedNameExpressionSyntax"; }

    static DelphiQualifiedNameExpressionSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                       DelphiNameExpressionSyntax* leftExpression,
                                                       Core::Syntax::ISyntaxToken* dotToken,
                                                       DelphiSimpleNameExpressionSyntax* rightExpression) noexcept;

private:
    DelphiNameExpressionSyntax* _pLeftExpression;
    Core::Syntax::ISyntaxToken* _pDotToken;
    DelphiSimpleNameExpressionSyntax* _pRightExpression;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIQUALIFIEDNAMEEXPRESSIONSYNTAX_H
