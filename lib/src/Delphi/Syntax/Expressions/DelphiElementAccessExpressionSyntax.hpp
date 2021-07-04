#ifndef POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIELEMENTACCESSEXPRESSIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIELEMENTACCESSEXPRESSIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Expressions/DelphiExpressionSyntax.hpp"
#include "Delphi/Syntax/DelphiBracketArgumentListSyntax.hpp"

namespace polyglot::Core::Syntax
{

class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiElementAccessExpressionSyntax : public DelphiExpressionSyntax
{
public:
    explicit DelphiElementAccessExpressionSyntax(DelphiExpressionSyntax* element,
                                                 DelphiBracketArgumentListSyntax* arguments) noexcept;

    virtual ~DelphiElementAccessExpressionSyntax() noexcept {}

    inline DelphiExpressionSyntax* element() const noexcept { return _pElement; }
    inline DelphiBracketArgumentListSyntax* arguments() const noexcept { return _pArguments; }

    inline pg_size childCount() const noexcept override final { return 2; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asNode(_pElement); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asNode(_pArguments); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiElementAccessExpressionSyntax"; }

    static DelphiElementAccessExpressionSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                       DelphiExpressionSyntax* elementExpression,
                                                       DelphiBracketArgumentListSyntax* arguments) noexcept;

private:
    DelphiExpressionSyntax* _pElement;
    DelphiBracketArgumentListSyntax* _pArguments;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIELEMENTACCESSEXPRESSIONSYNTAX_H
