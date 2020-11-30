#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ELSEDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ELSEDIRECTIVETRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/BranchingDirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API ElseDirectiveTriviaSyntax : public BranchingDirectiveTriviaSyntax
{
public:
    explicit ElseDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                       SharedPtr<SyntaxToken> startToken,
                                       SharedPtr<SyntaxToken> elseKeyword,
                                       SharedPtr<SyntaxToken> endOfDirectiveToken,
                                       bool isActive,
                                       bool isBranchTaken) noexcept;

    virtual ~ElseDirectiveTriviaSyntax() noexcept = default;
    inline virtual const SharedPtr<SyntaxToken>& startToken() const noexcept override { return _ptrStartToken; }
    inline virtual const SharedPtr<SyntaxToken>& elseKeyword() const noexcept { return _ptrElseKeyword; }
    inline virtual const SharedPtr<SyntaxToken>& endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }

    static SharedPtr<ElseDirectiveTriviaSyntax> create(SharedPtr<SyntaxToken> startToken,
                                                       SharedPtr<SyntaxToken> elseKeyword,
                                                       SharedPtr<SyntaxToken> endOfDirectiveToken,
                                                       bool isActive,
                                                       bool isBranchTaken) noexcept;

private:
    SharedPtr<SyntaxToken> _ptrStartToken;
    SharedPtr<SyntaxToken> _ptrElseKeyword;
    SharedPtr<SyntaxToken> _ptrEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ELSEDIRECTIVETRIVIASYNTAX_H
