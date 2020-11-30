#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_REGIONDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_REGIONDIRECTIVETRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API RegionDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit RegionDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                         SharedPtr<SyntaxToken> startToken,
                                         SharedPtr<SyntaxToken> regionKeyword,
                                         SharedPtr<SyntaxToken> endOfDirectiveToken,
                                         bool isActive) noexcept;

    virtual ~RegionDirectiveTriviaSyntax() noexcept = default;
    inline virtual const SharedPtr<SyntaxToken>& startToken() const noexcept override { return _ptrStartToken; }
    inline virtual const SharedPtr<SyntaxToken>& regionKeyword() const noexcept { return _ptrRegionKeyword; }
    inline virtual const SharedPtr<SyntaxToken>& endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static SharedPtr<RegionDirectiveTriviaSyntax> create(SharedPtr<SyntaxToken> startToken,
                                                         SharedPtr<SyntaxToken> regionKeyword,
                                                         SharedPtr<SyntaxToken> endOfDirectiveToken,
                                                         bool isActive) noexcept;
                                       
private:
    SharedPtr<SyntaxToken> _ptrStartToken;
    SharedPtr<SyntaxToken> _ptrRegionKeyword;
    SharedPtr<SyntaxToken> _ptrEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_REGIONDIRECTIVETRIVIASYNTAX_H
