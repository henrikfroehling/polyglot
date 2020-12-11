#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_IFDEFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_IFDEFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class POLYGLOT_API IfDefDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit IfDefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                        SyntaxToken* startToken,
                                        SyntaxToken* ifDefKeyword,
                                        SyntaxToken* name,
                                        SyntaxToken* endOfDirectiveToken,
                                        bool isActive) noexcept;

    virtual ~IfDefDirectiveTriviaSyntax() noexcept = default;
    inline virtual SyntaxToken* startToken() const noexcept override { return _ptrStartToken; }
    inline virtual SyntaxToken* ifDefKeyword() const noexcept { return _ptrIfDefKeyword; }
    inline virtual SyntaxToken* name() const noexcept { return _ptrName; }
    inline virtual SyntaxToken* endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static IfDefDirectiveTriviaSyntax* create(SyntaxToken* startToken,
                                              SyntaxToken* ifDefKeyword,
                                              SyntaxToken* name,
                                              SyntaxToken* endOfDirectiveToken,
                                              bool isActive) noexcept;

private:
    SyntaxToken* _ptrStartToken;
    SyntaxToken* _ptrIfDefKeyword;
    SyntaxToken* _ptrName;
    SyntaxToken* _ptrEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_IFDEFDIRECTIVETRIVIASYNTAX_H
