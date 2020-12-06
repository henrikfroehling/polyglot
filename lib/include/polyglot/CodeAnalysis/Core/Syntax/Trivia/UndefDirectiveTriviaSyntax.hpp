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
                                        Ptr<SyntaxToken> startToken,
                                        Ptr<SyntaxToken> undefKeyword,
                                        Ptr<SyntaxToken> name,
                                        Ptr<SyntaxToken> endOfDirectiveToken,
                                        bool isActive) noexcept;

    virtual ~UndefDirectiveTriviaSyntax() noexcept = default;
    inline virtual const Ptr<SyntaxToken> startToken() const noexcept override { return _ptrStartToken; }
    inline virtual const Ptr<SyntaxToken> undefKeyword() const noexcept { return _ptrUndefKeyword; }
    inline virtual const Ptr<SyntaxToken> name() const noexcept { return _ptrName; }
    inline virtual const Ptr<SyntaxToken> endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static Ptr<UndefDirectiveTriviaSyntax> create(Ptr<SyntaxToken> startToken,
                                                  Ptr<SyntaxToken> undefKeyword,
                                                  Ptr<SyntaxToken> name,
                                                  Ptr<SyntaxToken> endOfDirectiveToken,
                                                  bool isActive) noexcept;

private:
    Ptr<SyntaxToken> _ptrStartToken;
    Ptr<SyntaxToken> _ptrUndefKeyword;
    Ptr<SyntaxToken> _ptrName;
    Ptr<SyntaxToken> _ptrEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_UNDEFDIRECTIVETRIVIASYNTAX_H
