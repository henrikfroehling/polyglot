#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_DEFINEDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_DEFINEDIRECTIVETRIVIASYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class DefineDirectiveTriviaSyntax;
using DefineDirectiveTriviaSyntaxPtr = std::shared_ptr<DefineDirectiveTriviaSyntax>;

class POLYGLOT_API DefineDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit DefineDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                         SyntaxTokenPtr startToken,
                                         SyntaxTokenPtr defineKeyword,
                                         SyntaxTokenPtr name,
                                         SyntaxTokenPtr endOfDirectiveToken,
                                         bool isActive) noexcept;

    virtual ~DefineDirectiveTriviaSyntax() noexcept = default;
    inline virtual const SyntaxTokenPtr& startToken() const noexcept override { return _ptrStartToken; }
    inline virtual const SyntaxTokenPtr& defineKeyword() const noexcept { return _ptrDefineKeyword; }
    inline virtual const SyntaxTokenPtr& name() const noexcept { return _ptrName; }
    inline virtual const SyntaxTokenPtr& endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static DefineDirectiveTriviaSyntaxPtr Create(SyntaxTokenPtr startToken,
                                                 SyntaxTokenPtr defineKeyword,
                                                 SyntaxTokenPtr name,
                                                 SyntaxTokenPtr endOfDirectiveToken,
                                                 bool isActive) noexcept;

private:
    SyntaxTokenPtr _ptrStartToken;
    SyntaxTokenPtr _ptrDefineKeyword;
    SyntaxTokenPtr _ptrName;
    SyntaxTokenPtr _ptrEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_DEFINEDIRECTIVETRIVIASYNTAX_H
