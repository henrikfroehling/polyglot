#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_SWITCHDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_SWITCHDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxNode;
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

    virtual ~SwitchDirectiveTriviaSyntax() noexcept = default;
    inline virtual ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual ISyntaxToken* identifier() const noexcept { return _pIdentifier; }
    inline virtual ISyntaxToken* onOffToken() const noexcept { return _pOnOffToken; }
    inline virtual ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return false; }
    inline pg_size childCount() const noexcept override { return 4; }
    ISyntaxNode* child(pg_size index) const override;

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

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_SWITCHDIRECTIVETRIVIASYNTAX_H
