#ifndef POLYGLOT_CORE_SYNTAX_TRIVIA_IFNDEFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CORE_SYNTAX_TRIVIA_IFNDEFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "DirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

class IfNDefDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit IfNDefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                         ISyntaxToken* startToken,
                                         ISyntaxToken* ifNDefKeyword,
                                         ISyntaxToken* name,
                                         ISyntaxToken* endOfDirectiveToken,
                                         bool isActive) noexcept;

    virtual ~IfNDefDirectiveTriviaSyntax() noexcept {}
    inline virtual ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual ISyntaxToken* ifNDefKeyword() const noexcept { return _pIfNDefKeyword; }
    inline virtual ISyntaxToken* name() const noexcept { return _pName; }
    inline virtual ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline pg_size childCount() const noexcept override final { return 4; }
    SyntaxVariant child(pg_size index) const override final;

    static IfNDefDirectiveTriviaSyntax* create(SyntaxFactory& syntaxFactory,
                                               ISyntaxToken* startToken,
                                               ISyntaxToken* ifNDefKeyword,
                                               ISyntaxToken* name,
                                               ISyntaxToken* endOfDirectiveToken,
                                               bool isActive) noexcept;

private:
    ISyntaxToken* _pStartToken;
    ISyntaxToken* _pIfNDefKeyword;
    ISyntaxToken* _pName;
    ISyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_TRIVIA_IFNDEFDIRECTIVETRIVIASYNTAX_H
