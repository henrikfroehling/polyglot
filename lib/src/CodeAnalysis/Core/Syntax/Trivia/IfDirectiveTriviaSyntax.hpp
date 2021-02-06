#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/ConditionalDirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class ExpressionSyntax;
class LanguageSyntaxToken;
class SyntaxFactory;

class IfDirectiveTriviaSyntax : public ConditionalDirectiveTriviaSyntax
{
public:
    explicit IfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                     LanguageSyntaxToken* startToken,
                                     LanguageSyntaxToken* ifKeyword,
                                     ExpressionSyntax* condition,
                                     LanguageSyntaxToken* endOfDirectiveToken,
                                     bool isActive,
                                     bool isBranchTaken,
                                     bool conditionValue) noexcept;

    virtual ~IfDirectiveTriviaSyntax() noexcept = default;
    inline virtual LanguageSyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual LanguageSyntaxToken* ifKeywword() const noexcept { return _pIfKeyword; }
    inline virtual ExpressionSyntax* condition() const noexcept override { return _pCondition; }
    inline virtual LanguageSyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }
    inline virtual bool conditionValue() const noexcept override { return _conditionValue; }

    static IfDirectiveTriviaSyntax* create(SyntaxFactory& syntaxFactory,
                                           LanguageSyntaxToken* startToken,
                                           LanguageSyntaxToken* ifKeyword,
                                           ExpressionSyntax* condition,
                                           LanguageSyntaxToken* endOfDirectiveToken,
                                           bool isActive,
                                           bool isBranchTaken,
                                           bool conditionValue) noexcept;

private:
    LanguageSyntaxToken* _pStartToken;
    LanguageSyntaxToken* _pIfKeyword;
    ExpressionSyntax* _pCondition;
    LanguageSyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
    bool _conditionValue;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFDIRECTIVETRIVIASYNTAX_H
