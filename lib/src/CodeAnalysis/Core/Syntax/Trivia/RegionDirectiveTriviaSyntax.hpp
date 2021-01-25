#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_REGIONDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_REGIONDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class RegionDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit RegionDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                         SyntaxToken* startToken,
                                         SyntaxToken* regionKeyword,
                                         SyntaxToken* endOfDirectiveToken,
                                         bool isActive) noexcept;

    virtual ~RegionDirectiveTriviaSyntax() noexcept = default;
    inline virtual SyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual SyntaxToken* regionKeyword() const noexcept { return _pRegionKeyword; }
    inline virtual SyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static RegionDirectiveTriviaSyntax* create(SyntaxToken* startToken,
                                               SyntaxToken* regionKeyword,
                                               SyntaxToken* endOfDirectiveToken,
                                               bool isActive) noexcept;

private:
    SyntaxToken* _pStartToken;
    SyntaxToken* _pRegionKeyword;
    SyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_REGIONDIRECTIVETRIVIASYNTAX_H
