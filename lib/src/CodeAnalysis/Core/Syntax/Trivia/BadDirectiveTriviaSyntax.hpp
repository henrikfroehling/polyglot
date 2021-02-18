#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_BADDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_BADDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxNode;
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

    virtual ~BadDirectiveTriviaSyntax() noexcept = default;
    inline virtual ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual ISyntaxToken* identifier() const noexcept { return _pIdentifier; }
    inline virtual ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline pg_size childCount() const noexcept override { return 3; }
    ISyntaxNode* child(pg_size index) const override;

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

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_BADDIRECTIVETRIVIASYNTAX_H
