#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFDEFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFDEFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/ConditionalDirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxNode;
class LanguageSyntaxToken;
class SyntaxFactory;

class IfDefDirectiveTriviaSyntax : public ConditionalDirectiveTriviaSyntax
{
public:
    explicit IfDefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                        LanguageSyntaxToken* startToken,
                                        LanguageSyntaxToken* ifDefKeyword,
                                        LanguageSyntaxToken* name,
                                        LanguageSyntaxToken* endOfDirectiveToken,
                                        bool isActive,
                                        bool isBranchTaken) noexcept;

    virtual ~IfDefDirectiveTriviaSyntax() noexcept = default;
    inline virtual LanguageSyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual LanguageSyntaxToken* ifDefKeyword() const noexcept { return _pIfDefKeyword; }
    inline virtual LanguageSyntaxToken* name() const noexcept { return _pName; }
    inline virtual LanguageSyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }
    inline virtual bool conditionValue() const noexcept override { return false; }
    inline virtual ExpressionSyntax* condition() const noexcept override { return nullptr; }
    LanguageSyntaxNode* child(pg_size index) const override;
    inline pg_size childCount() const noexcept override { return 4; }

    static IfDefDirectiveTriviaSyntax* create(SyntaxFactory& syntaxFactory,
                                              LanguageSyntaxToken* startToken,
                                              LanguageSyntaxToken* ifDefKeyword,
                                              LanguageSyntaxToken* name,
                                              LanguageSyntaxToken* endOfDirectiveToken,
                                              bool isActive,
                                              bool isBranchTaken) noexcept;

private:
    LanguageSyntaxToken* _pStartToken;
    LanguageSyntaxToken* _pIfDefKeyword;
    LanguageSyntaxToken* _pName;
    LanguageSyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_IFDEFDIRECTIVETRIVIASYNTAX_H
