#ifndef POLYGLOT_CORE_SYNTAX_TRIVIA_SWITCHDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CORE_SYNTAX_TRIVIA_SWITCHDIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxNodeOrToken.hpp"
#include "polyglot/Core/Types.hpp"
#include "DirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

class SwitchDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit SwitchDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                         ISyntaxToken* startToken,
                                         ISyntaxToken* identifier,
                                         ISyntaxToken* onOffToken,
                                         ISyntaxToken* endOfDirectiveToken) noexcept;

    virtual ~SwitchDirectiveTriviaSyntax() noexcept {}
    inline virtual ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual ISyntaxToken* identifier() const noexcept { return _pIdentifier; }
    inline virtual ISyntaxToken* onOffToken() const noexcept { return _pOnOffToken; }
    inline virtual ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return false; }
    inline pg_size childCount() const noexcept override final { return 4; }
    SyntaxNodeOrToken child(pg_size index) const override final;

    static SwitchDirectiveTriviaSyntax* create(SyntaxFactory& syntaxFactory,
                                               ISyntaxToken* startToken,
                                               ISyntaxToken* identifier,
                                               ISyntaxToken* onOffToken,
                                               ISyntaxToken* endOfDirectiveToken) noexcept;

private:
    ISyntaxToken* _pStartToken;
    ISyntaxToken* _pIdentifier;
    ISyntaxToken* _pOnOffToken;
    ISyntaxToken* _pEndOfDirectiveToken;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_TRIVIA_SWITCHDIRECTIVETRIVIASYNTAX_H
