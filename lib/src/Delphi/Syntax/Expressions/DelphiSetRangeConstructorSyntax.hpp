#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHISETRANGECONSTRUCTORSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHISETRANGECONSTRUCTORSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Expressions/DelphiExpressionSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiSetConstructorSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiSetRangeConstructorSyntax : public DelphiSetConstructorSyntax
{
public:
    explicit DelphiSetRangeConstructorSyntax(Core::Syntax::ISyntaxToken* openBracketToken,
                                             DelphiExpressionSyntax* firstElement,
                                             Core::Syntax::ISyntaxToken* dotDotToken,
                                             DelphiExpressionSyntax* lastElement,
                                             Core::Syntax::ISyntaxToken* closeBracketToken) noexcept;

    virtual ~DelphiSetRangeConstructorSyntax() noexcept {}

    inline DelphiExpressionSyntax* firstElement() const noexcept { return _pFirstElement; }
    inline Core::Syntax::ISyntaxToken* dotDotToken() const noexcept { return _pDotDotToken; }
    inline DelphiExpressionSyntax* lastElement() const noexcept { return _pLastElement; }

    inline pg_size childCount() const noexcept override final { return 5; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline virtual pg_string typeName() const noexcept override { return L"DelphiSetRangeConstructorSyntax"; }

    static DelphiSetRangeConstructorSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                   Core::Syntax::ISyntaxToken* openBracketToken,
                                                   DelphiExpressionSyntax* firstElement,
                                                   Core::Syntax::ISyntaxToken* dotDotToken,
                                                   DelphiExpressionSyntax* lastElement,
                                                   Core::Syntax::ISyntaxToken* closeBracketToken) noexcept;

protected:
    DelphiExpressionSyntax* _pFirstElement;
    Core::Syntax::ISyntaxToken* _pDotDotToken;
    DelphiExpressionSyntax* _pLastElement;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHISETRANGECONSTRUCTORSYNTAX_H
