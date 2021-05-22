#ifndef POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIELSEIFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIELSEIFDIRECTIVETRIVIASYNTAX_H

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

class DelphiElseIfDirectiveTriviaSyntax : public Core::Syntax::ConditionalDirectiveTriviaSyntax
{
public:
    explicit DelphiElseIfDirectiveTriviaSyntax(Core::Syntax::SyntaxKind syntaxKind,
                                               Core::Syntax::ISyntaxToken* startToken,
                                               Core::Syntax::ISyntaxToken* elseIfKeyword,
                                               Core::Syntax::ExpressionSyntax* condition,
                                               Core::Syntax::ISyntaxToken* endOfDirectiveToken,
                                               bool isActive,
                                               bool isBranchTaken,
                                               bool conditionValue) noexcept;

    virtual ~DelphiElseIfDirectiveTriviaSyntax() noexcept {}
    inline virtual Core::Syntax::ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual Core::Syntax::ISyntaxToken* elseIfKeywword() const noexcept { return _pElseIfKeyword; }
    inline virtual Core::Syntax::ExpressionSyntax* condition() const noexcept override { return _pCondition; }
    inline virtual Core::Syntax::ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }
    inline virtual bool conditionValue() const noexcept override { return _conditionValue; }
    inline pg_size childCount() const noexcept override final { return 4; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    virtual pg_string typeName() const noexcept override { return L"DelphiElseIfDirectiveTriviaSyntax"; }

    static DelphiElseIfDirectiveTriviaSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                     Core::Syntax::ISyntaxToken* startToken,
                                                     Core::Syntax::ISyntaxToken* elseIfKeyword,
                                                     Core::Syntax::ExpressionSyntax* condition,
                                                     Core::Syntax::ISyntaxToken* endOfDirectiveToken,
                                                     bool isActive,
                                                     bool isBranchTaken,
                                                     bool conditionValue) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pStartToken;
    Core::Syntax::ISyntaxToken* _pElseIfKeyword;
    Core::Syntax::ExpressionSyntax* _pCondition;
    Core::Syntax::ISyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
    bool _conditionValue;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIELSEIFDIRECTIVETRIVIASYNTAX_H
