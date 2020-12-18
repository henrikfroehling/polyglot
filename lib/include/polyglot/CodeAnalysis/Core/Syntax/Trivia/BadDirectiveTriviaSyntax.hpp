#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_BADDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_BADDIRECTIVETRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class POLYGLOT_API BadDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit BadDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                      SyntaxToken* startToken,
                                      SyntaxToken* identifier,
                                      SyntaxToken* endOfDirectiveToken,
                                      bool isActive) noexcept;

    virtual ~BadDirectiveTriviaSyntax() noexcept = default;
    inline virtual SyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual SyntaxToken* identifier() const noexcept { return _pIdentifier; }
    inline virtual SyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static BadDirectiveTriviaSyntax* create(SyntaxToken* startToken,
                                            SyntaxToken* identifier,
                                            SyntaxToken* endOfDirectiveToken,
                                            bool isActive) noexcept;

private:
    SyntaxToken* _pStartToken;
    SyntaxToken* _pIdentifier;
    SyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_BADDIRECTIVETRIVIASYNTAX_H
