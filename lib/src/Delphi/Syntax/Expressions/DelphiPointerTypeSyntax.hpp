#ifndef POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIPOINTERTYPESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIPOINTERTYPESYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Expressions/DelphiTypeSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiPointerTypeSyntax : public DelphiTypeSyntax
{
public:
    explicit DelphiPointerTypeSyntax(Core::Syntax::ISyntaxToken* caretToken,
                                     DelphiTypeSyntax* type) noexcept;

    virtual ~DelphiPointerTypeSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* caretToken() const noexcept { return _pCaretToken; }
    inline DelphiTypeSyntax* type() const noexcept { return _pType; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pCaretToken); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asNode(_pType); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiPointerTypeSyntax"; }

    static DelphiPointerTypeSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                           Core::Syntax::ISyntaxToken* caretToken,
                                           DelphiTypeSyntax* type) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pCaretToken;
    DelphiTypeSyntax* _pType;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIPOINTERTYPESYNTAX_H
