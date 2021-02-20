#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_UNDEFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_UNDEFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxNode;
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

    virtual ~UndefDirectiveTriviaSyntax() noexcept = default;
    inline virtual ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual ISyntaxToken* undefKeyword() const noexcept { return _pUndefKeyword; }
    inline virtual ISyntaxToken* name() const noexcept { return _pName; }
    inline virtual ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline pg_size childCount() const noexcept override { return 4; }
    ISyntaxNode* child(pg_size index) const override;

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

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_UNDEFDIRECTIVETRIVIASYNTAX_H
