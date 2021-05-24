#ifndef POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHISWITCHDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHISWITCHDIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiSwitchDirectiveTriviaSyntax : public Core::Syntax::DirectiveTriviaSyntax
{
public:
    explicit DelphiSwitchDirectiveTriviaSyntax(Core::Syntax::SyntaxKind syntaxKind,
                                               Core::Syntax::ISyntaxToken* startToken,
                                               Core::Syntax::ISyntaxToken* identifier,
                                               Core::Syntax::ISyntaxToken* onOffToken,
                                               Core::Syntax::ISyntaxToken* endOfDirectiveToken) noexcept;

    virtual ~DelphiSwitchDirectiveTriviaSyntax() noexcept {}
    inline virtual Core::Syntax::ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual Core::Syntax::ISyntaxToken* identifier() const noexcept { return _pIdentifier; }
    inline virtual Core::Syntax::ISyntaxToken* onOffToken() const noexcept { return _pOnOffToken; }
    inline virtual Core::Syntax::ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return false; }
    inline pg_size childCount() const noexcept override final { return 4; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline virtual pg_string typeName() const noexcept override { return L"DelphiSwitchDirectiveTriviaSyntax"; }

    static DelphiSwitchDirectiveTriviaSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                     Core::Syntax::ISyntaxToken* startToken,
                                                     Core::Syntax::ISyntaxToken* identifier,
                                                     Core::Syntax::ISyntaxToken* onOffToken,
                                                     Core::Syntax::ISyntaxToken* endOfDirectiveToken) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pStartToken;
    Core::Syntax::ISyntaxToken* _pIdentifier;
    Core::Syntax::ISyntaxToken* _pOnOffToken;
    Core::Syntax::ISyntaxToken* _pEndOfDirectiveToken;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHISWITCHDIRECTIVETRIVIASYNTAX_H
