#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHISETCONSTRUCTORSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHISETCONSTRUCTORSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Expressions/DelphiExpressionSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiSetConstructorSyntax : public DelphiExpressionSyntax
{
public:
    explicit DelphiSetConstructorSyntax(Core::Syntax::SyntaxKind syntaxKind,
                                        Core::Syntax::ISyntaxToken* openBracketToken,
                                        Core::Syntax::ISyntaxToken* closeBracketToken) noexcept;

    virtual ~DelphiSetConstructorSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* openBracketToken() const noexcept { return _pOpenBracketToken; }
    inline Core::Syntax::ISyntaxToken* closeBracketToken() const noexcept { return _pCloseBracketToken; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pOpenBracketToken); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pCloseBracketToken); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiSetConstructorSyntax"; }

protected:
    Core::Syntax::ISyntaxToken* _pOpenBracketToken;
    Core::Syntax::ISyntaxToken* _pCloseBracketToken;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHISETCONSTRUCTORSYNTAX_H
