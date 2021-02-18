#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_ELSEDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_ELSEDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/BranchingDirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxNode;
class ISyntaxToken;
class SyntaxFactory;

class ElseDirectiveTriviaSyntax : public BranchingDirectiveTriviaSyntax
{
public:
    explicit ElseDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                       ISyntaxToken* startToken,
                                       ISyntaxToken* elseKeyword,
                                       ISyntaxToken* endOfDirectiveToken,
                                       bool isActive,
                                       bool isBranchTaken) noexcept;

    virtual ~ElseDirectiveTriviaSyntax() noexcept = default;
    inline virtual ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual ISyntaxToken* elseKeyword() const noexcept { return _pElseKeyword; }
    inline virtual ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }
    inline pg_size childCount() const noexcept override { return 3; }
    ISyntaxNode* child(pg_size index) const override;

    static ElseDirectiveTriviaSyntax* create(SyntaxFactory& syntaxFactory,
                                             ISyntaxToken* startToken,
                                             ISyntaxToken* elseKeyword,
                                             ISyntaxToken* endOfDirectiveToken,
                                             bool isActive,
                                             bool isBranchTaken) noexcept;
    
private:
    ISyntaxToken* _pStartToken;
    ISyntaxToken* _pElseKeyword;
    ISyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_ELSEDIRECTIVETRIVIASYNTAX_H
