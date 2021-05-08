#ifndef POLYGLOT_CORE_SYNTAX_TRIVIA_DEFINEDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CORE_SYNTAX_TRIVIA_DEFINEDIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "DirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;
class ISyntaxToken;
class SyntaxFactory;

class DefineDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit DefineDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                         ISyntaxToken* startToken,
                                         ISyntaxToken* defineKeyword,
                                         ISyntaxToken* name,
                                         ISyntaxToken* endOfDirectiveToken,
                                         bool isActive) noexcept;

    virtual ~DefineDirectiveTriviaSyntax() noexcept = default;
    inline virtual ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual ISyntaxToken* defineKeyword() const noexcept { return _pDefineKeyword; }
    inline virtual ISyntaxToken* name() const noexcept { return _pName; }
    inline virtual ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline pg_size childCount() const noexcept override { return 4; }
    ISyntaxNode* child(pg_size index) const override;

    static DefineDirectiveTriviaSyntax* create(SyntaxFactory& syntaxFactory,
                                               ISyntaxToken* startToken,
                                               ISyntaxToken* defineKeyword,
                                               ISyntaxToken* name,
                                               ISyntaxToken* endOfDirectiveToken,
                                               bool isActive) noexcept;

private:
    ISyntaxToken* _pStartToken;
    ISyntaxToken* _pDefineKeyword;
    ISyntaxToken* _pName;
    ISyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_TRIVIA_DEFINEDIRECTIVETRIVIASYNTAX_H
