#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_UNDEFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_UNDEFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API UndefDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit UndefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                        SharedPtr<SyntaxToken> startToken,
                                        SharedPtr<SyntaxToken> undefKeyword,
                                        SharedPtr<SyntaxToken> name,
                                        SharedPtr<SyntaxToken> endOfDirectiveToken,
                                        bool isActive) noexcept;

    virtual ~UndefDirectiveTriviaSyntax() noexcept = default;
    inline virtual const SharedPtr<SyntaxToken>& startToken() const noexcept override { return _ptrStartToken; }
    inline virtual const SharedPtr<SyntaxToken>& undefKeyword() const noexcept { return _ptrUndefKeyword; }
    inline virtual const SharedPtr<SyntaxToken>& name() const noexcept { return _ptrName; }
    inline virtual const SharedPtr<SyntaxToken>& endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static SharedPtr<UndefDirectiveTriviaSyntax> create(SharedPtr<SyntaxToken> startToken,
                                                        SharedPtr<SyntaxToken> undefKeyword,
                                                        SharedPtr<SyntaxToken> name,
                                                        SharedPtr<SyntaxToken> endOfDirectiveToken,
                                                        bool isActive) noexcept;

private:
    SharedPtr<SyntaxToken> _ptrStartToken;
    SharedPtr<SyntaxToken> _ptrUndefKeyword;
    SharedPtr<SyntaxToken> _ptrName;
    SharedPtr<SyntaxToken> _ptrEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_UNDEFDIRECTIVETRIVIASYNTAX_H
