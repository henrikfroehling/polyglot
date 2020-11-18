#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_IFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_IFDIRECTIVETRIVIASYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/ConditionalDirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class IfDirectiveTriviaSyntax;
using IfDirectiveTriviaSyntaxPtr = std::shared_ptr<IfDirectiveTriviaSyntax>;

class POLYGLOT_API IfDirectiveTriviaSyntax : public ConditionalDirectiveTriviaSyntax
{
public:
    explicit IfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                     SyntaxTokenPtr startToken,
                                     SyntaxTokenPtr ifKeyword,
                                     ExpressionSyntaxPtr condition,
                                     SyntaxTokenPtr endOfDirectiveToken,
                                     bool isActive,
                                     bool isBranchTaken,
                                     bool conditionValue) noexcept;

    virtual ~IfDirectiveTriviaSyntax() noexcept = default;
    inline virtual const SyntaxTokenPtr& startToken() const noexcept override { return _ptrStartToken; }
    inline virtual const SyntaxTokenPtr& ifKeywword() const noexcept { return _ptrIfKeyword; }
    inline virtual const SyntaxTokenPtr& endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }
    inline virtual const ExpressionSyntaxPtr& condition() const noexcept override { return _ptrCondition; }
    inline virtual bool conditionValue() const noexcept override { return _conditionValue; }

    static IfDirectiveTriviaSyntaxPtr create(SyntaxTokenPtr startToken,
                                             SyntaxTokenPtr ifKeyword,
                                             ExpressionSyntaxPtr condition,
                                             SyntaxTokenPtr endOfDirectiveToken,
                                             bool isActive,
                                             bool isBranchTaken,
                                             bool conditionValue) noexcept;

private:
    SyntaxTokenPtr _ptrStartToken;
    SyntaxTokenPtr _ptrIfKeyword;
    ExpressionSyntaxPtr _ptrCondition;
    SyntaxTokenPtr _ptrEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
    bool _conditionValue;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_IFDIRECTIVETRIVIASYNTAX_H
