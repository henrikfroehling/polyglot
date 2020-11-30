#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_IFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_IFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/ConditionalDirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API IfDirectiveTriviaSyntax : public ConditionalDirectiveTriviaSyntax
{
public:
    explicit IfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                     SharedPtr<SyntaxToken> startToken,
                                     SharedPtr<SyntaxToken> ifKeyword,
                                     SharedPtr<ExpressionSyntax> condition,
                                     SharedPtr<SyntaxToken> endOfDirectiveToken,
                                     bool isActive,
                                     bool isBranchTaken,
                                     bool conditionValue) noexcept;

    virtual ~IfDirectiveTriviaSyntax() noexcept = default;
    inline virtual const SharedPtr<SyntaxToken>& startToken() const noexcept override { return _ptrStartToken; }
    inline virtual const SharedPtr<SyntaxToken>& ifKeywword() const noexcept { return _ptrIfKeyword; }
    inline virtual const SharedPtr<SyntaxToken>& endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }
    inline virtual const SharedPtr<ExpressionSyntax>& condition() const noexcept override { return _ptrCondition; }
    inline virtual bool conditionValue() const noexcept override { return _conditionValue; }

    static SharedPtr<IfDirectiveTriviaSyntax> create(SharedPtr<SyntaxToken> startToken,
                                                     SharedPtr<SyntaxToken> ifKeyword,
                                                     SharedPtr<ExpressionSyntax> condition,
                                                     SharedPtr<SyntaxToken> endOfDirectiveToken,
                                                     bool isActive,
                                                     bool isBranchTaken,
                                                     bool conditionValue) noexcept;

private:
    SharedPtr<SyntaxToken> _ptrStartToken;
    SharedPtr<SyntaxToken> _ptrIfKeyword;
    SharedPtr<ExpressionSyntax> _ptrCondition;
    SharedPtr<SyntaxToken> _ptrEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
    bool _conditionValue;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_IFDIRECTIVETRIVIASYNTAX_H
