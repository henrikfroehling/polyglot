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
                                       Ptr<SyntaxToken> startToken,
                                       Ptr<SyntaxToken> elseKeyword,
                                       Ptr<SyntaxToken> endOfDirectiveToken,
                                       bool isActive,
                                       bool isBranchTaken) noexcept;

    virtual ~ElseDirectiveTriviaSyntax() noexcept = default;
    inline virtual const Ptr<SyntaxToken> startToken() const noexcept override { return _ptrStartToken; }
    inline virtual const Ptr<SyntaxToken> elseKeyword() const noexcept { return _ptrElseKeyword; }
    inline virtual const Ptr<SyntaxToken> endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }

    static Ptr<ElseDirectiveTriviaSyntax> create(Ptr<SyntaxToken> startToken,
                                                 Ptr<SyntaxToken> elseKeyword,
                                                 Ptr<SyntaxToken> endOfDirectiveToken,
                                                 bool isActive,
                                                 bool isBranchTaken) noexcept;

private:
    Ptr<SyntaxToken> _ptrStartToken;
    Ptr<SyntaxToken> _ptrElseKeyword;
    Ptr<SyntaxToken> _ptrEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ELSEDIRECTIVETRIVIASYNTAX_H
