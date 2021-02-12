#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_ELSEDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_ELSEDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/BranchingDirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxNode;
class LanguageSyntaxToken;
class SyntaxFactory;

class ElseDirectiveTriviaSyntax : public BranchingDirectiveTriviaSyntax
{
public:
    explicit ElseDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                       LanguageSyntaxToken* startToken,
                                       LanguageSyntaxToken* elseKeyword,
                                       LanguageSyntaxToken* endOfDirectiveToken,
                                       bool isActive,
                                       bool isBranchTaken) noexcept;

    virtual ~ElseDirectiveTriviaSyntax() noexcept = default;
    inline virtual LanguageSyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual LanguageSyntaxToken* elseKeyword() const noexcept { return _pElseKeyword; }
    inline virtual LanguageSyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }
    LanguageSyntaxNode* child(pg_size index) const override;
    inline pg_size childCount() const noexcept override { return 3; }

    static ElseDirectiveTriviaSyntax* create(SyntaxFactory& syntaxFactory,
                                             LanguageSyntaxToken* startToken,
                                             LanguageSyntaxToken* elseKeyword,
                                             LanguageSyntaxToken* endOfDirectiveToken,
                                             bool isActive,
                                             bool isBranchTaken) noexcept;
    
private:
    LanguageSyntaxToken* _pStartToken;
    LanguageSyntaxToken* _pElseKeyword;
    LanguageSyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_ELSEDIRECTIVETRIVIASYNTAX_H
