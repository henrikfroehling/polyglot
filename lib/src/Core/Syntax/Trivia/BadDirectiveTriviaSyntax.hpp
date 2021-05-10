#ifndef POLYGLOT_CORE_SYNTAX_TRIVIA_BADDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CORE_SYNTAX_TRIVIA_BADDIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "DirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

class BadDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit BadDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                      ISyntaxToken* startToken,
                                      ISyntaxToken* identifier,
                                      ISyntaxToken* endOfDirectiveToken,
                                      bool isActive) noexcept;

    virtual ~BadDirectiveTriviaSyntax() noexcept {}
    inline virtual ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual ISyntaxToken* identifier() const noexcept { return _pIdentifier; }
    inline virtual ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline pg_size childCount() const noexcept override final { return 3; }
    SyntaxVariant child(pg_size index) const override final;

    static BadDirectiveTriviaSyntax* create(SyntaxFactory& syntaxFactory,
                                            ISyntaxToken* startToken,
                                            ISyntaxToken* identifier,
                                            ISyntaxToken* endOfDirectiveToken,
                                            bool isActive) noexcept;

private:
    ISyntaxToken* _pStartToken;
    ISyntaxToken* _pIdentifier;
    ISyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_TRIVIA_BADDIRECTIVETRIVIASYNTAX_H
