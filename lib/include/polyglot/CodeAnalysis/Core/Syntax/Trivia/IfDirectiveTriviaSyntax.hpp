#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/ConditionalDirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class ExpressionSyntax;
class SyntaxToken;

class POLYGLOT_API IfDirectiveTriviaSyntax : public ConditionalDirectiveTriviaSyntax
{
public:
    explicit IfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                     SyntaxToken* startToken,
                                     SyntaxToken* ifKeyword,
                                     ExpressionSyntax* condition,
                                     SyntaxToken* endOfDirectiveToken,
                                     bool isActive,
                                     bool isBranchTaken,
                                     bool conditionValue) noexcept;

    virtual ~IfDirectiveTriviaSyntax() noexcept = default;
    inline virtual SyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual SyntaxToken* ifKeywword() const noexcept { return _pIfKeyword; }
    inline virtual ExpressionSyntax* condition() const noexcept override { return _pCondition; }
    inline virtual SyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }
    inline virtual bool conditionValue() const noexcept override { return _conditionValue; }

    static IfDirectiveTriviaSyntax* create(SyntaxToken* startToken,
                                           SyntaxToken* ifKeyword,
                                           ExpressionSyntax* condition,
                                           SyntaxToken* endOfDirectiveToken,
                                           bool isActive,
                                           bool isBranchTaken,
                                           bool conditionValue) noexcept;

private:
    SyntaxToken* _pStartToken;
    SyntaxToken* _pIfKeyword;
    ExpressionSyntax* _pCondition;
    SyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
    bool _conditionValue;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFDIRECTIVETRIVIASYNTAX_H
