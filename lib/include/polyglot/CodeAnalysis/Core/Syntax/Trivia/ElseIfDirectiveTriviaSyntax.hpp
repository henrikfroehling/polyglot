#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ELSEIFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ELSEIFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/ConditionalDirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API ElseIfDirectiveTriviaSyntax : public ConditionalDirectiveTriviaSyntax
{
public:
    explicit ElseIfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                         SharedPtr<SyntaxToken> startToken,
                                         SharedPtr<SyntaxToken> elseIfKeyword,
                                         SharedPtr<ExpressionSyntax> condition,
                                         SharedPtr<SyntaxToken> endOfDirectiveToken,
                                         bool isActive,
                                         bool isBranchTaken,
                                         bool conditionValue) noexcept;

    virtual ~ElseIfDirectiveTriviaSyntax() noexcept = default;
    inline virtual const SharedPtr<SyntaxToken>& startToken() const noexcept override { return _ptrStartToken; }
    inline virtual const SharedPtr<SyntaxToken>& elseIfKeywword() const noexcept { return _ptrElseIfKeyword; }
    inline virtual const SharedPtr<SyntaxToken>& endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }
    inline virtual const SharedPtr<ExpressionSyntax>& condition() const noexcept override { return _ptrCondition; }
    inline virtual bool conditionValue() const noexcept override { return _conditionValue; }

    static SharedPtr<ElseIfDirectiveTriviaSyntax> create(SharedPtr<SyntaxToken> startToken,
                                                         SharedPtr<SyntaxToken> elseIfKeyword,
                                                         SharedPtr<ExpressionSyntax> condition,
                                                         SharedPtr<SyntaxToken> endOfDirectiveToken,
                                                         bool isActive,
                                                         bool isBranchTaken,
                                                         bool conditionValue) noexcept;

private:
    SharedPtr<SyntaxToken> _ptrStartToken;
    SharedPtr<SyntaxToken> _ptrElseIfKeyword;
    SharedPtr<ExpressionSyntax> _ptrCondition;
    SharedPtr<SyntaxToken> _ptrEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
    bool _conditionValue;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ELSEIFDIRECTIVETRIVIASYNTAX_H
