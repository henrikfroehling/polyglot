#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIBRACKETARGUMENTLISTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIBRACKETARGUMENTLISTSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiSyntaxList;

class DelphiBracketArgumentListSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiBracketArgumentListSyntax(Core::Syntax::ISyntaxToken* openBracket,
                                             DelphiSyntaxList* arguments,
                                             Core::Syntax::ISyntaxToken* closeBracket) noexcept;

    virtual ~DelphiBracketArgumentListSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* openBracket() const noexcept { return _pOpenBracketToken; }
    inline DelphiSyntaxList* arguments() const noexcept { return _pArguments; }
    inline Core::Syntax::ISyntaxToken* closeBracket() const noexcept { return _pCloseBracketToken; }

    inline pg_size childCount() const noexcept override final { return 3; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pOpenBracketToken); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pCloseBracketToken); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiBracketArgumentListSyntax"; }

    static DelphiBracketArgumentListSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                   Core::Syntax::ISyntaxToken* openBracket,
                                                   DelphiSyntaxList* arguments,
                                                   Core::Syntax::ISyntaxToken* closeBracket) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pOpenBracketToken;
    DelphiSyntaxList* _pArguments;
    Core::Syntax::ISyntaxToken* _pCloseBracketToken;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIBRACKETARGUMENTLISTSYNTAX_H
