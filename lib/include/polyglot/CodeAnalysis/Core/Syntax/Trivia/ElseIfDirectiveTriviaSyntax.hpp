#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ELSEIFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ELSEIFDIRECTIVETRIVIASYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/ConditionalDirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class ElseIfDirectiveTriviaSyntax;
using ElseIfDirectiveTriviaSyntaxPtr = std::shared_ptr<ElseIfDirectiveTriviaSyntax>;

class POLYGLOT_API ElseIfDirectiveTriviaSyntax : public ConditionalDirectiveTriviaSyntax
{
public:
    explicit ElseIfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                         SyntaxTokenPtr startToken,
                                         SyntaxTokenPtr elseIfKeyword,
                                         ExpressionSyntaxPtr condition,
                                         SyntaxTokenPtr endOfDirectiveToken,
                                         bool isActive,
                                         bool isBranchTaken,
                                         bool conditionValue) noexcept;

    virtual ~ElseIfDirectiveTriviaSyntax() noexcept = default;
    inline virtual const SyntaxTokenPtr& startToken() const noexcept override { return _ptrStartToken; }
    inline virtual const SyntaxTokenPtr& elseIfKeywword() const noexcept { return _ptrElseIfKeyword; }
    inline virtual const SyntaxTokenPtr& endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }
    inline virtual const ExpressionSyntaxPtr& condition() const noexcept override { return _ptrCondition; }
    inline virtual bool conditionValue() const noexcept override { return _conditionValue; }

    static ElseIfDirectiveTriviaSyntaxPtr create(SyntaxTokenPtr startToken,
                                                 SyntaxTokenPtr elseIfKeyword,
                                                 ExpressionSyntaxPtr condition,
                                                 SyntaxTokenPtr endOfDirectiveToken,
                                                 bool isActive,
                                                 bool isBranchTaken,
                                                 bool conditionValue) noexcept;

private:
    SyntaxTokenPtr _ptrStartToken;
    SyntaxTokenPtr _ptrElseIfKeyword;
    ExpressionSyntaxPtr _ptrCondition;
    SyntaxTokenPtr _ptrEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
    bool _conditionValue;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ELSEIFDIRECTIVETRIVIASYNTAX_H
