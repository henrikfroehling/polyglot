#ifndef POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIPREDEFINEDTYPESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIPREDEFINEDTYPESYNTAX_H

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

class DelphiPredefinedTypeSyntax : public DelphiTypeSyntax
{
public:
    explicit DelphiPredefinedTypeSyntax(Core::Syntax::ISyntaxToken* keyword) noexcept;
    virtual ~DelphiPredefinedTypeSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* keyword() const noexcept { return _pKeyword; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pKeyword); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiPredefinedTypeSyntax"; }

    static DelphiPredefinedTypeSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                              Core::Syntax::ISyntaxToken* keyword) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pKeyword;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIPREDEFINEDTYPESYNTAX_H
