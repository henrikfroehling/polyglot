#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFNDEFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFNDEFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class POLYGLOT_API IfNDefDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit IfNDefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                         SyntaxToken* startToken,
                                         SyntaxToken* ifNDefKeyword,
                                         SyntaxToken* name,
                                         SyntaxToken* endOfDirectiveToken,
                                         bool isActive) noexcept;

    virtual ~IfNDefDirectiveTriviaSyntax() noexcept = default;
    inline virtual SyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual SyntaxToken* ifNDefKeyword() const noexcept { return _pIfNDefKeyword; }
    inline virtual SyntaxToken* name() const noexcept { return _pName; }
    inline virtual SyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static IfNDefDirectiveTriviaSyntax* create(SyntaxToken* startToken,
                                               SyntaxToken* ifNDefKeyword,
                                               SyntaxToken* name,
                                               SyntaxToken* endOfDirectiveToken,
                                               bool isActive) noexcept;

private:
    SyntaxToken* _pStartToken;
    SyntaxToken* _pIfNDefKeyword;
    SyntaxToken* _pName;
    SyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFNDEFDIRECTIVETRIVIASYNTAX_H
