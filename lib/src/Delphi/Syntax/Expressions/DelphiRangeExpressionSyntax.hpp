#ifndef POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIRANGEEXPRESSIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIRANGEEXPRESSIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Expressions/DelphiExpressionSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiRangeExpressionSyntax : public DelphiExpressionSyntax
{
public:
    explicit DelphiRangeExpressionSyntax(DelphiExpressionSyntax* leftExpression,
                                         Core::Syntax::ISyntaxToken* dotDotToken,
                                         DelphiExpressionSyntax* rightExpression) noexcept;

    virtual ~DelphiRangeExpressionSyntax() noexcept {}

    inline virtual DelphiExpressionSyntax* leftExpression() const noexcept { return _pLeftExpression; }
    inline virtual Core::Syntax::ISyntaxToken* dotDotToken() const noexcept { return _pDotDotToken; }
    inline virtual DelphiExpressionSyntax* rightExpression() const noexcept { return _pRightExpression; }

    inline pg_size childCount() const noexcept override final { return 3; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline virtual Core::Syntax::SyntaxVariant first() const noexcept override { return Core::Syntax::SyntaxVariant::asNode(_pLeftExpression); }
    inline virtual Core::Syntax::SyntaxVariant last() const noexcept override { return Core::Syntax::SyntaxVariant::asNode(_pRightExpression); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiRangeExpressionSyntax"; }

    static DelphiRangeExpressionSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                               DelphiExpressionSyntax* leftExpression,
                                               Core::Syntax::ISyntaxToken* dotDotToken,
                                               DelphiExpressionSyntax* rightExpression) noexcept;

private:
    DelphiExpressionSyntax* _pLeftExpression;
    Core::Syntax::ISyntaxToken* _pDotDotToken;
    DelphiExpressionSyntax* _pRightExpression;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIRANGEEXPRESSIONSYNTAX_H
