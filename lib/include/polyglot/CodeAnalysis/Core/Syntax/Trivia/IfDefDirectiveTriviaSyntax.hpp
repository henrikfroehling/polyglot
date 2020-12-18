#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFDEFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFDEFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/ConditionalDirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class POLYGLOT_API IfDefDirectiveTriviaSyntax : public ConditionalDirectiveTriviaSyntax
{
public:
    explicit IfDefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                        SyntaxToken* startToken,
                                        SyntaxToken* ifDefKeyword,
                                        SyntaxToken* name,
                                        SyntaxToken* endOfDirectiveToken,
                                        bool isActive,
                                        bool isBranchTaken) noexcept;

    virtual ~IfDefDirectiveTriviaSyntax() noexcept = default;
    inline virtual SyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual SyntaxToken* ifDefKeyword() const noexcept { return _pIfDefKeyword; }
    inline virtual SyntaxToken* name() const noexcept { return _pName; }
    inline virtual SyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }
    inline virtual bool conditionValue() const noexcept override { return false; }
    inline virtual ExpressionSyntax* condition() const noexcept override { return nullptr; }

    static IfDefDirectiveTriviaSyntax* create(SyntaxToken* startToken,
                                              SyntaxToken* ifDefKeyword,
                                              SyntaxToken* name,
                                              SyntaxToken* endOfDirectiveToken,
                                              bool isActive,
                                              bool isBranchTaken) noexcept;

private:
    SyntaxToken* _pStartToken;
    SyntaxToken* _pIfDefKeyword;
    SyntaxToken* _pName;
    SyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFDEFDIRECTIVETRIVIASYNTAX_H
