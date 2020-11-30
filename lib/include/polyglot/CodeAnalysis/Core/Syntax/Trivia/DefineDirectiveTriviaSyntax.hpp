#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_DEFINEDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_DEFINEDIRECTIVETRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DefineDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit DefineDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                         SharedPtr<SyntaxToken> startToken,
                                         SharedPtr<SyntaxToken> defineKeyword,
                                         SharedPtr<SyntaxToken> name,
                                         SharedPtr<SyntaxToken> endOfDirectiveToken,
                                         bool isActive) noexcept;

    virtual ~DefineDirectiveTriviaSyntax() noexcept = default;
    inline virtual const SharedPtr<SyntaxToken>& startToken() const noexcept override { return _ptrStartToken; }
    inline virtual const SharedPtr<SyntaxToken>& defineKeyword() const noexcept { return _ptrDefineKeyword; }
    inline virtual const SharedPtr<SyntaxToken>& name() const noexcept { return _ptrName; }
    inline virtual const SharedPtr<SyntaxToken>& endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static SharedPtr<DefineDirectiveTriviaSyntax> create(SharedPtr<SyntaxToken> startToken,
                                                         SharedPtr<SyntaxToken> defineKeyword,
                                                         SharedPtr<SyntaxToken> name,
                                                         SharedPtr<SyntaxToken> endOfDirectiveToken,
                                                         bool isActive) noexcept;

private:
    SharedPtr<SyntaxToken> _ptrStartToken;
    SharedPtr<SyntaxToken> _ptrDefineKeyword;
    SharedPtr<SyntaxToken> _ptrName;
    SharedPtr<SyntaxToken> _ptrEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_DEFINEDIRECTIVETRIVIASYNTAX_H
