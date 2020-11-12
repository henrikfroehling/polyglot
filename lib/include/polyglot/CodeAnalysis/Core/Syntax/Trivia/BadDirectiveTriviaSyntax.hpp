#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_BADDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_BADDIRECTIVETRIVIASYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class BadDirectiveTriviaSyntax;
using BadDirectiveTriviaSyntaxPtr = std::shared_ptr<BadDirectiveTriviaSyntax>;

class POLYGLOT_API BadDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit BadDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                      SyntaxTokenPtr startToken,
                                      SyntaxTokenPtr identifier,
                                      SyntaxTokenPtr endOfDirectiveToken,
                                      bool isActive) noexcept;

    virtual ~BadDirectiveTriviaSyntax() noexcept = default;
    inline virtual const SyntaxTokenPtr& startToken() const noexcept override { return _ptrStartToken; }
    inline virtual const SyntaxTokenPtr& identifier() const noexcept { return _ptrIdentifier; }
    inline virtual const SyntaxTokenPtr& endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static BadDirectiveTriviaSyntaxPtr Create(SyntaxTokenPtr startToken,
                                              SyntaxTokenPtr identifier,
                                              SyntaxTokenPtr endOfDirectiveToken,
                                              bool isActive) noexcept;

private:
    SyntaxTokenPtr _ptrStartToken;
    SyntaxTokenPtr _ptrIdentifier;
    SyntaxTokenPtr _ptrEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_BADDIRECTIVETRIVIASYNTAX_H
