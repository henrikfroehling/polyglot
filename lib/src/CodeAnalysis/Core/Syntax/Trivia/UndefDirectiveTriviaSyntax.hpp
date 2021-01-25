#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_UNDEFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_UNDEFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class UndefDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit UndefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                        SyntaxToken* startToken,
                                        SyntaxToken* undefKeyword,
                                        SyntaxToken* name,
                                        SyntaxToken* endOfDirectiveToken,
                                        bool isActive) noexcept;

    virtual ~UndefDirectiveTriviaSyntax() noexcept = default;
    inline virtual SyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual SyntaxToken* undefKeyword() const noexcept { return _pUndefKeyword; }
    inline virtual SyntaxToken* name() const noexcept { return _pName; }
    inline virtual SyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static UndefDirectiveTriviaSyntax* create(SyntaxToken* startToken,
                                              SyntaxToken* undefKeyword,
                                              SyntaxToken* name,
                                              SyntaxToken* endOfDirectiveToken,
                                              bool isActive) noexcept;

private:
    SyntaxToken* _pStartToken;
    SyntaxToken* _pUndefKeyword;
    SyntaxToken* _pName;
    SyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_UNDEFDIRECTIVETRIVIASYNTAX_H
