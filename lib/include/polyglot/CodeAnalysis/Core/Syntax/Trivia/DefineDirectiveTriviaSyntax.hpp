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
                                         Ptr<SyntaxToken> startToken,
                                         Ptr<SyntaxToken> defineKeyword,
                                         Ptr<SyntaxToken> name,
                                         Ptr<SyntaxToken> endOfDirectiveToken,
                                         bool isActive) noexcept;

    virtual ~DefineDirectiveTriviaSyntax() noexcept = default;
    inline virtual const Ptr<SyntaxToken> startToken() const noexcept override { return _ptrStartToken; }
    inline virtual const Ptr<SyntaxToken> defineKeyword() const noexcept { return _ptrDefineKeyword; }
    inline virtual const Ptr<SyntaxToken> name() const noexcept { return _ptrName; }
    inline virtual const Ptr<SyntaxToken> endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static Ptr<DefineDirectiveTriviaSyntax> create(Ptr<SyntaxToken> startToken,
                                                   Ptr<SyntaxToken> defineKeyword,
                                                   Ptr<SyntaxToken> name,
                                                   Ptr<SyntaxToken> endOfDirectiveToken,
                                                   bool isActive) noexcept;

private:
    Ptr<SyntaxToken> _ptrStartToken;
    Ptr<SyntaxToken> _ptrDefineKeyword;
    Ptr<SyntaxToken> _ptrName;
    Ptr<SyntaxToken> _ptrEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_DEFINEDIRECTIVETRIVIASYNTAX_H
