#ifndef POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIASSIGNMENTEXPRESSIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIASSIGNMENTEXPRESSIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
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

class DelphiAssignmentExpressionSyntax : public DelphiExpressionSyntax
{
public:
    explicit DelphiAssignmentExpressionSyntax(DelphiExpressionSyntax* leftExpression,
                                              Core::Syntax::ISyntaxToken* colonEqualToken,
                                              DelphiExpressionSyntax* rightExpression) noexcept;

    virtual ~DelphiAssignmentExpressionSyntax() noexcept {}

    inline DelphiExpressionSyntax* leftExpression() const noexcept { return _pLeftExpression; }
    inline Core::Syntax::ISyntaxToken* colonEqualToken() const noexcept { return _pColonEqualToken; }
    inline DelphiExpressionSyntax* rightExpression() const noexcept { return _pRightExpression; }

    inline pg_size childCount() const noexcept override final { return 3; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asNode(_pLeftExpression); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asNode(_pRightExpression); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiAssignmentExpressionSyntax"; }

    static DelphiAssignmentExpressionSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                    DelphiExpressionSyntax* leftExpression,
                                                    Core::Syntax::ISyntaxToken* colonEqualToken,
                                                    DelphiExpressionSyntax* rightExpression) noexcept;

private:
    DelphiExpressionSyntax* _pLeftExpression;
    Core::Syntax::ISyntaxToken* _pColonEqualToken;
    DelphiExpressionSyntax* _pRightExpression;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIASSIGNMENTEXPRESSIONSYNTAX_H
