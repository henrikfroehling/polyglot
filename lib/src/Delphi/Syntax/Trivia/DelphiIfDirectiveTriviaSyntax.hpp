#ifndef POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIIFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIIFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/Trivia/ConditionalDirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ExpressionSyntax;
class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiIfDirectiveTriviaSyntax : public Core::Syntax::ConditionalDirectiveTriviaSyntax
{
public:
    explicit DelphiIfDirectiveTriviaSyntax(Core::Syntax::SyntaxKind syntaxKind,
                                           Core::Syntax::ISyntaxToken* startToken,
                                           Core::Syntax::ISyntaxToken* ifKeyword,
                                           Core::Syntax::ExpressionSyntax* condition,
                                           Core::Syntax::ISyntaxToken* endOfDirectiveToken,
                                           bool isActive,
                                           bool isBranchTaken,
                                           bool conditionValue) noexcept;

    virtual ~DelphiIfDirectiveTriviaSyntax() noexcept {}
    inline virtual Core::Syntax::ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual Core::Syntax::ISyntaxToken* ifKeywword() const noexcept { return _pIfKeyword; }
    inline virtual Core::Syntax::ExpressionSyntax* condition() const noexcept override { return _pCondition; }
    inline virtual Core::Syntax::ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }
    inline virtual bool conditionValue() const noexcept override { return _conditionValue; }
    inline pg_size childCount() const noexcept override final { return 4; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    static DelphiIfDirectiveTriviaSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                 Core::Syntax::ISyntaxToken* startToken,
                                                 Core::Syntax::ISyntaxToken* ifKeyword,
                                                 Core::Syntax::ExpressionSyntax* condition,
                                                 Core::Syntax::ISyntaxToken* endOfDirectiveToken,
                                                 bool isActive,
                                                 bool isBranchTaken,
                                                 bool conditionValue) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pStartToken;
    Core::Syntax::ISyntaxToken* _pIfKeyword;
    Core::Syntax::ExpressionSyntax* _pCondition;
    Core::Syntax::ISyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
    bool _conditionValue;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIIFDIRECTIVETRIVIASYNTAX_H
