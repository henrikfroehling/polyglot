#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_ELSEDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_ELSEDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/BranchingDirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class ElseDirectiveTriviaSyntax : public BranchingDirectiveTriviaSyntax
{
public:
    explicit ElseDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                       SyntaxToken* startToken,
                                       SyntaxToken* elseKeyword,
                                       SyntaxToken* endOfDirectiveToken,
                                       bool isActive,
                                       bool isBranchTaken) noexcept;

    virtual ~ElseDirectiveTriviaSyntax() noexcept = default;
    inline virtual SyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual SyntaxToken* elseKeyword() const noexcept { return _pElseKeyword; }
    inline virtual SyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }

    static ElseDirectiveTriviaSyntax* create(SyntaxToken* startToken,
                                             SyntaxToken* elseKeyword,
                                             SyntaxToken* endOfDirectiveToken,
                                             bool isActive,
                                             bool isBranchTaken) noexcept;
    
private:
    SyntaxToken* _pStartToken;
    SyntaxToken* _pElseKeyword;
    SyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_ELSEDIRECTIVETRIVIASYNTAX_H
