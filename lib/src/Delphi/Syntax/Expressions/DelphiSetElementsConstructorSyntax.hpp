#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHISETELEMENTSCONSTRUCTORSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHISETELEMENTSCONSTRUCTORSYNTAX_H

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

class DelphiSyntaxList;

class DelphiSetElementsConstructorSyntax : public DelphiSetConstructorSyntax
{
public:
    explicit DelphiSetElementsConstructorSyntax(Core::Syntax::ISyntaxToken* openBracketToken,
                                                DelphiSyntaxList* elements,
                                                Core::Syntax::ISyntaxToken* closeBracketToken) noexcept;

    virtual ~DelphiSetElementsConstructorSyntax() noexcept {}

    inline DelphiSyntaxList* elements() const noexcept { return _pElements; }

    inline pg_size childCount() const noexcept override final { return 3; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline virtual pg_string typeName() const noexcept override { return L"DelphiSetElementsConstructorSyntax"; }

    static DelphiSetElementsConstructorSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                      Core::Syntax::ISyntaxToken* openBracketToken,
                                                      DelphiSyntaxList* elements,
                                                      Core::Syntax::ISyntaxToken* closeBracketToken) noexcept;

private:
    DelphiSyntaxList* _pElements;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHISETELEMENTSCONSTRUCTORSYNTAX_H
