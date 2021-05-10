#ifndef POLYGLOT_CORE_SYNTAX_TRIVIA_ELSEIFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CORE_SYNTAX_TRIVIA_ELSEIFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "ConditionalDirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ExpressionSyntax;
class ISyntaxToken;
class SyntaxFactory;

class ElseIfDirectiveTriviaSyntax : public ConditionalDirectiveTriviaSyntax
{
public:
    explicit ElseIfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                         ISyntaxToken* startToken,
                                         ISyntaxToken* elseIfKeyword,
                                         ExpressionSyntax* condition,
                                         ISyntaxToken* endOfDirectiveToken,
                                         bool isActive,
                                         bool isBranchTaken,
                                         bool conditionValue) noexcept;

    virtual ~ElseIfDirectiveTriviaSyntax() noexcept {}
    inline virtual ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual ISyntaxToken* elseIfKeywword() const noexcept { return _pElseIfKeyword; }
    inline virtual ExpressionSyntax* condition() const noexcept override { return _pCondition; }
    inline virtual ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }
    inline virtual bool conditionValue() const noexcept override { return _conditionValue; }
    inline pg_size childCount() const noexcept override final { return 4; }
    SyntaxVariant child(pg_size index) const override final;

    static ElseIfDirectiveTriviaSyntax* create(SyntaxFactory& syntaxFactory,
                                               ISyntaxToken* startToken,
                                               ISyntaxToken* elseIfKeyword,
                                               ExpressionSyntax* condition,
                                               ISyntaxToken* endOfDirectiveToken,
                                               bool isActive,
                                               bool isBranchTaken,
                                               bool conditionValue) noexcept;

private:
    ISyntaxToken* _pStartToken;
    ISyntaxToken* _pElseIfKeyword;
    ExpressionSyntax* _pCondition;
    ISyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
    bool _conditionValue;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_TRIVIA_ELSEIFDIRECTIVETRIVIASYNTAX_H
