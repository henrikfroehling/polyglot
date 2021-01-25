#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFENDDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFENDDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class IfEndDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit IfEndDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                        SyntaxToken* startToken,
                                        SyntaxToken* ifEndKeyword,
                                        SyntaxToken* endOfDirectiveToken,
                                        bool isActive) noexcept;

    virtual ~IfEndDirectiveTriviaSyntax() noexcept = default;
    inline virtual SyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual SyntaxToken* ifEndKeyword() const noexcept { return _pIfEndKeyword; }
    inline virtual SyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static IfEndDirectiveTriviaSyntax* create(SyntaxToken* startToken,
                                              SyntaxToken* ifEndKeyword,
                                              SyntaxToken* endOfDirectiveToken,
                                              bool isActive) noexcept;

private:
    SyntaxToken* _pStartToken;
    SyntaxToken* _pIfEndKeyword;
    SyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFENDDIRECTIVETRIVIASYNTAX_H
