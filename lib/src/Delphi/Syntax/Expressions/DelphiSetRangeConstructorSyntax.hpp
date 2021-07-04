#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHISETRANGECONSTRUCTORSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHISETRANGECONSTRUCTORSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Expressions/DelphiSetConstructorSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiRangeExpressionSyntax;

class DelphiSetRangeConstructorSyntax : public DelphiSetConstructorSyntax
{
public:
    explicit DelphiSetRangeConstructorSyntax(Core::Syntax::ISyntaxToken* openBracketToken,
                                             DelphiRangeExpressionSyntax* setRange,
                                             Core::Syntax::ISyntaxToken* closeBracketToken) noexcept;

    virtual ~DelphiSetRangeConstructorSyntax() noexcept {}

    inline DelphiRangeExpressionSyntax* setRange() const noexcept { return _pSetRange; }

    inline pg_size childCount() const noexcept override final { return 3; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline virtual pg_string typeName() const noexcept override { return L"DelphiSetRangeConstructorSyntax"; }

    static DelphiSetRangeConstructorSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                   Core::Syntax::ISyntaxToken* openBracketToken,
                                                   DelphiRangeExpressionSyntax* setRange,
                                                   Core::Syntax::ISyntaxToken* closeBracketToken) noexcept;

protected:
    DelphiRangeExpressionSyntax* _pSetRange;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHISETRANGECONSTRUCTORSYNTAX_H
