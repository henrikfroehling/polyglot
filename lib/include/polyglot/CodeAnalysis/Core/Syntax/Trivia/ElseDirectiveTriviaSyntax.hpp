#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ELSEDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ELSEDIRECTIVETRIVIASYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/BranchingDirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class ElseDirectiveTriviaSyntax;
using ElseDirectiveTriviaSyntaxPtr = std::shared_ptr<ElseDirectiveTriviaSyntax>;

class POLYGLOT_API ElseDirectiveTriviaSyntax : public BranchingDirectiveTriviaSyntax
{
public:
    explicit ElseDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                       SyntaxTokenPtr startToken,
                                       SyntaxTokenPtr elseKeyword,
                                       SyntaxTokenPtr endOfDirectiveToken,
                                       bool isActive,
                                       bool isBranchTaken) noexcept;

    virtual ~ElseDirectiveTriviaSyntax() noexcept = default;
    inline virtual const SyntaxTokenPtr& startToken() const noexcept override { return _ptrStartToken; }
    inline virtual const SyntaxTokenPtr& elseKeyword() const noexcept { return _ptrElseKeyword; }
    inline virtual const SyntaxTokenPtr& endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }

    static ElseDirectiveTriviaSyntaxPtr Create(SyntaxTokenPtr startToken,
                                               SyntaxTokenPtr elseKeyword,
                                               SyntaxTokenPtr endOfDirectiveToken,
                                               bool isActive,
                                               bool isBranchTaken) noexcept;

private:
    SyntaxTokenPtr _ptrStartToken;
    SyntaxTokenPtr _ptrElseKeyword;
    SyntaxTokenPtr _ptrEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ELSEDIRECTIVETRIVIASYNTAX_H
