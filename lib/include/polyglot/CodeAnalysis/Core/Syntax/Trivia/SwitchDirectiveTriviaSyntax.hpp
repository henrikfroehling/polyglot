#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_SWITCHDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_SWITCHDIRECTIVETRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class POLYGLOT_API SwitchDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit SwitchDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                         SyntaxToken* startToken,
                                         SyntaxToken* identifier,
                                         SyntaxToken* onOffToken,
                                         SyntaxToken* endOfDirectiveToken) noexcept;

    virtual ~SwitchDirectiveTriviaSyntax() noexcept = default;
    inline virtual SyntaxToken* startToken() const noexcept override { return _ptrStartToken; }
    inline virtual SyntaxToken* identifier() const noexcept { return _ptrIdentifier; }
    inline virtual SyntaxToken* onOffToken() const noexcept { return _ptrOnOffToken; }
    inline virtual SyntaxToken* endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return false; }

    static SwitchDirectiveTriviaSyntax* create(SyntaxToken* startToken,
                                               SyntaxToken* identifier,
                                               SyntaxToken* onOffToken,
                                               SyntaxToken* endOfDirectiveToken) noexcept;

private:
    SyntaxToken* _ptrStartToken;
    SyntaxToken* _ptrIdentifier;
    SyntaxToken* _ptrOnOffToken;
    SyntaxToken* _ptrEndOfDirectiveToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_SWITCHDIRECTIVETRIVIASYNTAX_H
