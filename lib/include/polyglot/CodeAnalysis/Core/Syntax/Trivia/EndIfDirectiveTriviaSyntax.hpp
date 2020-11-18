#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ENDIFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ENDIFDIRECTIVETRIVIASYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class EndIfDirectiveTriviaSyntax;
using EndIfDirectiveTriviaSyntaxPtr = std::shared_ptr<EndIfDirectiveTriviaSyntax>;

class POLYGLOT_API EndIfDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit EndIfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                        SyntaxTokenPtr startToken,
                                        SyntaxTokenPtr endIfKeyword,
                                        SyntaxTokenPtr endOfDirectiveToken,
                                        bool isActive) noexcept;

    virtual ~EndIfDirectiveTriviaSyntax() noexcept = default;
    inline virtual const SyntaxTokenPtr& startToken() const noexcept override { return _ptrStartToken; }
    inline virtual const SyntaxTokenPtr& endIfKeyword() const noexcept { return _ptrEndIfKeyword; }
    inline virtual const SyntaxTokenPtr& endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static EndIfDirectiveTriviaSyntaxPtr create(SyntaxTokenPtr startToken,
                                                SyntaxTokenPtr endIFKeyword,
                                                SyntaxTokenPtr endOfDirectiveToken,
                                                bool isActive) noexcept;

private:
    SyntaxTokenPtr _ptrStartToken;
    SyntaxTokenPtr _ptrEndIfKeyword;
    SyntaxTokenPtr _ptrEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ENDIFDIRECTIVETRIVIASYNTAX_H
