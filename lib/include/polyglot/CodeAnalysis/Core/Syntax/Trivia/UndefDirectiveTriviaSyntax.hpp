#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_UNDEFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_UNDEFDIRECTIVETRIVIASYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class UndefDirectiveTriviaSyntax;
using UndefDirectiveTriviaSyntaxPtr = std::shared_ptr<UndefDirectiveTriviaSyntax>;

class POLYGLOT_API UndefDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit UndefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                        SyntaxTokenPtr startToken,
                                        SyntaxTokenPtr undefKeyword,
                                        SyntaxTokenPtr name,
                                        SyntaxTokenPtr endOfDirectiveToken,
                                        bool isActive) noexcept;

    virtual ~UndefDirectiveTriviaSyntax() noexcept = default;
    inline virtual const SyntaxTokenPtr& startToken() const noexcept override { return _ptrStartToken; }
    inline virtual const SyntaxTokenPtr& undefKeyword() const noexcept { return _ptrUndefKeyword; }
    inline virtual const SyntaxTokenPtr& name() const noexcept { return _ptrName; }
    inline virtual const SyntaxTokenPtr& endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static UndefDirectiveTriviaSyntaxPtr Create(SyntaxTokenPtr startToken,
                                                SyntaxTokenPtr undefKeyword,
                                                SyntaxTokenPtr name,
                                                SyntaxTokenPtr endOfDirectiveToken,
                                                bool isActive) noexcept;

private:
    SyntaxTokenPtr _ptrStartToken;
    SyntaxTokenPtr _ptrUndefKeyword;
    SyntaxTokenPtr _ptrName;
    SyntaxTokenPtr _ptrEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_UNDEFDIRECTIVETRIVIASYNTAX_H
