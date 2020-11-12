#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ENDREGIONDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ENDREGIONDIRECTIVETRIVIASYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class EndRegionDirectiveTriviaSyntax;
using EndRegionDirectiveTriviaSyntaxPtr = std::shared_ptr<EndRegionDirectiveTriviaSyntax>;

class POLYGLOT_API EndRegionDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit EndRegionDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                            SyntaxTokenPtr startToken,
                                            SyntaxTokenPtr endRegionKeyword,
                                            SyntaxTokenPtr endOfDirectiveToken,
                                            bool isActive) noexcept;

    virtual ~EndRegionDirectiveTriviaSyntax() noexcept = default;
    inline virtual const SyntaxTokenPtr& startToken() const noexcept override { return _ptrStartToken; }
    inline virtual const SyntaxTokenPtr& endRegionKeyword() const noexcept { return _ptrEndRegionKeyword; }
    inline virtual const SyntaxTokenPtr& endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static EndRegionDirectiveTriviaSyntaxPtr Create(SyntaxTokenPtr startToken,
                                                    SyntaxTokenPtr endRegionKeyword,
                                                    SyntaxTokenPtr endOfDirectiveToken,
                                                    bool isActive) noexcept;

private:
    SyntaxTokenPtr _ptrStartToken;
    SyntaxTokenPtr _ptrEndRegionKeyword;
    SyntaxTokenPtr _ptrEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ENDREGIONDIRECTIVETRIVIASYNTAX_H
