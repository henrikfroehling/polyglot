#ifndef POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIIFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIIFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Trivia/DelphiConditionalDirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiExpressionSyntax;

class DelphiIfDirectiveTriviaSyntax : public DelphiConditionalDirectiveTriviaSyntax
{
public:
    explicit DelphiIfDirectiveTriviaSyntax(Core::Syntax::SyntaxKind syntaxKind,
                                           Core::Syntax::ISyntaxToken* startToken,
                                           Core::Syntax::ISyntaxToken* ifKeyword,
                                           DelphiExpressionSyntax* condition,
                                           Core::Syntax::ISyntaxToken* endOfDirectiveToken,
                                           bool isActive,
                                           bool isBranchTaken,
                                           bool conditionValue) noexcept;

    virtual ~DelphiIfDirectiveTriviaSyntax() noexcept {}
    inline virtual Core::Syntax::ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual Core::Syntax::ISyntaxToken* ifKeywword() const noexcept { return _pIfKeyword; }
    inline virtual DelphiExpressionSyntax* condition() const noexcept override { return _pCondition; }
    inline virtual Core::Syntax::ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }
    inline virtual bool conditionValue() const noexcept override { return _conditionValue; }
    inline pg_size childCount() const noexcept override final { return 4; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline virtual pg_string typeName() const noexcept override { return L"DelphiIfDirectiveTriviaSyntax"; }

    static DelphiIfDirectiveTriviaSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                 Core::Syntax::ISyntaxToken* startToken,
                                                 Core::Syntax::ISyntaxToken* ifKeyword,
                                                 DelphiExpressionSyntax* condition,
                                                 Core::Syntax::ISyntaxToken* endOfDirectiveToken,
                                                 bool isActive,
                                                 bool isBranchTaken,
                                                 bool conditionValue) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pStartToken;
    Core::Syntax::ISyntaxToken* _pIfKeyword;
    DelphiExpressionSyntax* _pCondition;
    Core::Syntax::ISyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
    bool _conditionValue;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIIFDIRECTIVETRIVIASYNTAX_H
