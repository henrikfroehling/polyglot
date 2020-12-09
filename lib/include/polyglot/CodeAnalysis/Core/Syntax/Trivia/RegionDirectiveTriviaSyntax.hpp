#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_REGIONDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_REGIONDIRECTIVETRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class POLYGLOT_API RegionDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit RegionDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                         SyntaxToken* startToken,
                                         SyntaxToken* regionKeyword,
                                         SyntaxToken* endOfDirectiveToken,
                                         bool isActive) noexcept;

    virtual ~RegionDirectiveTriviaSyntax() noexcept = default;
    inline virtual SyntaxToken* startToken() const noexcept override { return _ptrStartToken; }
    inline virtual SyntaxToken* regionKeyword() const noexcept { return _ptrRegionKeyword; }
    inline virtual SyntaxToken* endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static RegionDirectiveTriviaSyntax* create(SyntaxToken* startToken,
                                               SyntaxToken* regionKeyword,
                                               SyntaxToken* endOfDirectiveToken,
                                               bool isActive) noexcept;

private:
    SyntaxToken* _ptrStartToken;
    SyntaxToken* _ptrRegionKeyword;
    SyntaxToken* _ptrEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_REGIONDIRECTIVETRIVIASYNTAX_H
