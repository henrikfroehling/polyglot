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
                                         Ptr<SyntaxToken> startToken,
                                         Ptr<SyntaxToken> elseIfKeyword,
                                         Ptr<ExpressionSyntax> condition,
                                         Ptr<SyntaxToken> endOfDirectiveToken,
                                         bool isActive,
                                         bool isBranchTaken,
                                         bool conditionValue) noexcept;

    virtual ~ElseIfDirectiveTriviaSyntax() noexcept = default;
    inline virtual const Ptr<SyntaxToken> startToken() const noexcept override { return _ptrStartToken; }
    inline virtual const Ptr<SyntaxToken> elseIfKeywword() const noexcept { return _ptrElseIfKeyword; }
    inline virtual const Ptr<SyntaxToken> endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }
    inline virtual const Ptr<ExpressionSyntax> condition() const noexcept override { return _ptrCondition; }
    inline virtual bool conditionValue() const noexcept override { return _conditionValue; }

    static Ptr<ElseIfDirectiveTriviaSyntax> create(Ptr<SyntaxToken> startToken,
                                                   Ptr<SyntaxToken> elseIfKeyword,
                                                   Ptr<ExpressionSyntax> condition,
                                                   Ptr<SyntaxToken> endOfDirectiveToken,
                                                   bool isActive,
                                                   bool isBranchTaken,
                                                   bool conditionValue) noexcept;

private:
    Ptr<SyntaxToken> _ptrStartToken;
    Ptr<SyntaxToken> _ptrElseIfKeyword;
    Ptr<ExpressionSyntax> _ptrCondition;
    Ptr<SyntaxToken> _ptrEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
    bool _conditionValue;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ELSEIFDIRECTIVETRIVIASYNTAX_H
