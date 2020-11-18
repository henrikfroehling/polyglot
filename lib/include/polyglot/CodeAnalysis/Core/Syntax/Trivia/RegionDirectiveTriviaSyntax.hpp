#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_REGIONDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_REGIONDIRECTIVETRIVIASYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class RegionDirectiveTriviaSyntax;
using RegionDirectiveTriviaSyntaxPtr = std::shared_ptr<RegionDirectiveTriviaSyntax>;

class POLYGLOT_API RegionDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit RegionDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                         SyntaxTokenPtr startToken,
                                         SyntaxTokenPtr regionKeyword,
                                         SyntaxTokenPtr endOfDirectiveToken,
                                         bool isActive) noexcept;

    virtual ~RegionDirectiveTriviaSyntax() noexcept = default;
    inline virtual const SyntaxTokenPtr& startToken() const noexcept override { return _ptrStartToken; }
    inline virtual const SyntaxTokenPtr& regionKeyword() const noexcept { return _ptrRegionKeyword; }
    inline virtual const SyntaxTokenPtr& endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static RegionDirectiveTriviaSyntaxPtr create(SyntaxTokenPtr startToken,
                                                 SyntaxTokenPtr regionKeyword,
                                                 SyntaxTokenPtr endOfDirectiveToken,
                                                 bool isActive) noexcept;
                                       
private:
    SyntaxTokenPtr _ptrStartToken;
    SyntaxTokenPtr _ptrRegionKeyword;
    SyntaxTokenPtr _ptrEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_REGIONDIRECTIVETRIVIASYNTAX_H
