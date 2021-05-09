#ifndef POLYGLOT_CORE_SYNTAX_TRIVIA_IFDEFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CORE_SYNTAX_TRIVIA_IFDEFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxNodeOrToken.hpp"
#include "polyglot/Core/Types.hpp"
#include "ConditionalDirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

class IfDefDirectiveTriviaSyntax : public ConditionalDirectiveTriviaSyntax
{
public:
    explicit IfDefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                        ISyntaxToken* startToken,
                                        ISyntaxToken* ifDefKeyword,
                                        ISyntaxToken* name,
                                        ISyntaxToken* endOfDirectiveToken,
                                        bool isActive,
                                        bool isBranchTaken) noexcept;

    virtual ~IfDefDirectiveTriviaSyntax() noexcept {}
    inline virtual ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual ISyntaxToken* ifDefKeyword() const noexcept { return _pIfDefKeyword; }
    inline virtual ISyntaxToken* name() const noexcept { return _pName; }
    inline virtual ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }
    inline virtual bool conditionValue() const noexcept override { return false; }
    inline virtual ExpressionSyntax* condition() const noexcept override { return nullptr; }
    inline pg_size childCount() const noexcept override final { return 4; }
    SyntaxNodeOrToken child(pg_size index) const override final;

    static IfDefDirectiveTriviaSyntax* create(SyntaxFactory& syntaxFactory,
                                              ISyntaxToken* startToken,
                                              ISyntaxToken* ifDefKeyword,
                                              ISyntaxToken* name,
                                              ISyntaxToken* endOfDirectiveToken,
                                              bool isActive,
                                              bool isBranchTaken) noexcept;

private:
    ISyntaxToken* _pStartToken;
    ISyntaxToken* _pIfDefKeyword;
    ISyntaxToken* _pName;
    ISyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_TRIVIA_IFDEFDIRECTIVETRIVIASYNTAX_H
