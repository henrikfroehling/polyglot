#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_DEFINEDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_DEFINEDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class DefineDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit DefineDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                         SyntaxToken* startToken,
                                         SyntaxToken* defineKeyword,
                                         SyntaxToken* name,
                                         SyntaxToken* endOfDirectiveToken,
                                         bool isActive) noexcept;

    virtual ~DefineDirectiveTriviaSyntax() noexcept = default;
    inline virtual SyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual SyntaxToken* defineKeyword() const noexcept { return _pDefineKeyword; }
    inline virtual SyntaxToken* name() const noexcept { return _pName; }
    inline virtual SyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static DefineDirectiveTriviaSyntax* create(SyntaxToken* startToken,
                                               SyntaxToken* defineKeyword,
                                               SyntaxToken* name,
                                               SyntaxToken* endOfDirectiveToken,
                                               bool isActive) noexcept;

private:
    SyntaxToken* _pStartToken;
    SyntaxToken* _pDefineKeyword;
    SyntaxToken* _pName;
    SyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_DEFINEDIRECTIVETRIVIASYNTAX_H
