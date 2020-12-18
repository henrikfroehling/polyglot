#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_ENDIFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_ENDIFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class POLYGLOT_API EndIfDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit EndIfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                        SyntaxToken* startToken,
                                        SyntaxToken* endIfKeyword,
                                        SyntaxToken* endOfDirectiveToken,
                                        bool isActive) noexcept;

    virtual ~EndIfDirectiveTriviaSyntax() noexcept = default;
    inline virtual SyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual SyntaxToken* endIfKeyword() const noexcept { return _pEndIfKeyword; }
    inline virtual SyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static EndIfDirectiveTriviaSyntax* create(SyntaxToken* startToken,
                                              SyntaxToken* endIFKeyword,
                                              SyntaxToken* endOfDirectiveToken,
                                              bool isActive) noexcept;

private:
    SyntaxToken* _pStartToken;
    SyntaxToken* _pEndIfKeyword;
    SyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_ENDIFDIRECTIVETRIVIASYNTAX_H