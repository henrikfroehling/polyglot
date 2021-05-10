#ifndef POLYGLOT_CORE_SYNTAX_TRIVIA_UNDEFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CORE_SYNTAX_TRIVIA_UNDEFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "DirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

class UndefDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit UndefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                        ISyntaxToken* startToken,
                                        ISyntaxToken* undefKeyword,
                                        ISyntaxToken* name,
                                        ISyntaxToken* endOfDirectiveToken,
                                        bool isActive) noexcept;

    virtual ~UndefDirectiveTriviaSyntax() noexcept {}
    inline virtual ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual ISyntaxToken* undefKeyword() const noexcept { return _pUndefKeyword; }
    inline virtual ISyntaxToken* name() const noexcept { return _pName; }
    inline virtual ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline pg_size childCount() const noexcept override final { return 4; }
    SyntaxVariant child(pg_size index) const override final;

    static UndefDirectiveTriviaSyntax* create(SyntaxFactory& syntaxFactory,
                                              ISyntaxToken* startToken,
                                              ISyntaxToken* undefKeyword,
                                              ISyntaxToken* name,
                                              ISyntaxToken* endOfDirectiveToken,
                                              bool isActive) noexcept;

private:
    ISyntaxToken* _pStartToken;
    ISyntaxToken* _pUndefKeyword;
    ISyntaxToken* _pName;
    ISyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_TRIVIA_UNDEFDIRECTIVETRIVIASYNTAX_H
