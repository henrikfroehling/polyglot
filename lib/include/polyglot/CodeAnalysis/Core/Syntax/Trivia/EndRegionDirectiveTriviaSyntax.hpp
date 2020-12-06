#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ENDREGIONDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ENDREGIONDIRECTIVETRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API EndRegionDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit EndRegionDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                            Ptr<SyntaxToken> startToken,
                                            Ptr<SyntaxToken> endRegionKeyword,
                                            Ptr<SyntaxToken> endOfDirectiveToken,
                                            bool isActive) noexcept;

    virtual ~EndRegionDirectiveTriviaSyntax() noexcept = default;
    inline virtual const Ptr<SyntaxToken> startToken() const noexcept override { return _ptrStartToken; }
    inline virtual const Ptr<SyntaxToken> endRegionKeyword() const noexcept { return _ptrEndRegionKeyword; }
    inline virtual const Ptr<SyntaxToken> endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static Ptr<EndRegionDirectiveTriviaSyntax> Create(Ptr<SyntaxToken> startToken,
                                                      Ptr<SyntaxToken> endRegionKeyword,
                                                      Ptr<SyntaxToken> endOfDirectiveToken,
                                                      bool isActive) noexcept;

private:
    Ptr<SyntaxToken> _ptrStartToken;
    Ptr<SyntaxToken> _ptrEndRegionKeyword;
    Ptr<SyntaxToken> _ptrEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ENDREGIONDIRECTIVETRIVIASYNTAX_H
