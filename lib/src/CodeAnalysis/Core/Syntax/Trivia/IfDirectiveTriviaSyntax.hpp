#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/ConditionalDirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class ExpressionSyntax;
class ISyntaxNode;
class ISyntaxToken;
class SyntaxFactory;

class IfDirectiveTriviaSyntax : public ConditionalDirectiveTriviaSyntax
{
public:
    explicit IfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                     ISyntaxToken* startToken,
                                     ISyntaxToken* ifKeyword,
                                     ExpressionSyntax* condition,
                                     ISyntaxToken* endOfDirectiveToken,
                                     bool isActive,
                                     bool isBranchTaken,
                                     bool conditionValue) noexcept;

    virtual ~IfDirectiveTriviaSyntax() noexcept = default;
    inline virtual ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual ISyntaxToken* ifKeywword() const noexcept { return _pIfKeyword; }
    inline virtual ExpressionSyntax* condition() const noexcept override { return _pCondition; }
    inline virtual ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }
    inline virtual bool conditionValue() const noexcept override { return _conditionValue; }
    inline pg_size childCount() const noexcept override { return 4; }
    ISyntaxNode* child(pg_size index) const override;

    static IfDirectiveTriviaSyntax* create(SyntaxFactory& syntaxFactory,
                                           ISyntaxToken* startToken,
                                           ISyntaxToken* ifKeyword,
                                           ExpressionSyntax* condition,
                                           ISyntaxToken* endOfDirectiveToken,
                                           bool isActive,
                                           bool isBranchTaken,
                                           bool conditionValue) noexcept;

private:
    ISyntaxToken* _pStartToken;
    ISyntaxToken* _pIfKeyword;
    ExpressionSyntax* _pCondition;
    ISyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
    bool _conditionValue;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFDIRECTIVETRIVIASYNTAX_H
