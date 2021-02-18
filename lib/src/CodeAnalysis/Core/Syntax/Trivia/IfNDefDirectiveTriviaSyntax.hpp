#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFNDEFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFNDEFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxNode;
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

    virtual ~IfNDefDirectiveTriviaSyntax() noexcept = default;
    inline virtual ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual ISyntaxToken* ifNDefKeyword() const noexcept { return _pIfNDefKeyword; }
    inline virtual ISyntaxToken* name() const noexcept { return _pName; }
    inline virtual ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline pg_size childCount() const noexcept override { return 4; }
    ISyntaxNode* child(pg_size index) const override;

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

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFNDEFDIRECTIVETRIVIASYNTAX_H
