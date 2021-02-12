#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_ELSEIFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_ELSEIFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/ConditionalDirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxNode;
class ExpressionSyntax;
class LanguageSyntaxToken;
class SyntaxFactory;

class ElseIfDirectiveTriviaSyntax : public ConditionalDirectiveTriviaSyntax
{
public:
    explicit ElseIfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                         LanguageSyntaxToken* startToken,
                                         LanguageSyntaxToken* elseIfKeyword,
                                         ExpressionSyntax* condition,
                                         LanguageSyntaxToken* endOfDirectiveToken,
                                         bool isActive,
                                         bool isBranchTaken,
                                         bool conditionValue) noexcept;

    virtual ~ElseIfDirectiveTriviaSyntax() noexcept = default;
    inline virtual LanguageSyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual LanguageSyntaxToken* elseIfKeywword() const noexcept { return _pElseIfKeyword; }
    inline virtual ExpressionSyntax* condition() const noexcept override { return _pCondition; }
    inline virtual LanguageSyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }
    inline virtual bool conditionValue() const noexcept override { return _conditionValue; }
    LanguageSyntaxNode* child(pg_size index) const override;
    inline pg_size childCount() const noexcept override { return 4; }

    static ElseIfDirectiveTriviaSyntax* create(SyntaxFactory& syntaxFactory,
                                               LanguageSyntaxToken* startToken,
                                               LanguageSyntaxToken* elseIfKeyword,
                                               ExpressionSyntax* condition,
                                               LanguageSyntaxToken* endOfDirectiveToken,
                                               bool isActive,
                                               bool isBranchTaken,
                                               bool conditionValue) noexcept;

private:
    LanguageSyntaxToken* _pStartToken;
    LanguageSyntaxToken* _pElseIfKeyword;
    ExpressionSyntax* _pCondition;
    LanguageSyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
    bool _conditionValue;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_ELSEIFDIRECTIVETRIVIASYNTAX_H
