#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ENDREGIONDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ENDREGIONDIRECTIVETRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class POLYGLOT_API EndRegionDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit EndRegionDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                            SyntaxToken* startToken,
                                            SyntaxToken* endRegionKeyword,
                                            SyntaxToken* endOfDirectiveToken,
                                            bool isActive) noexcept;

    virtual ~EndRegionDirectiveTriviaSyntax() noexcept = default;
    inline virtual SyntaxToken* startToken() const noexcept override { return _ptrStartToken; }
    inline virtual SyntaxToken* endRegionKeyword() const noexcept { return _ptrEndRegionKeyword; }
    inline virtual SyntaxToken* endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static EndRegionDirectiveTriviaSyntax* create(SyntaxToken* startToken,
                                                  SyntaxToken* endRegionKeyword,
                                                  SyntaxToken* endOfDirectiveToken,
                                                  bool isActive) noexcept;

private:
    SyntaxToken* _ptrStartToken;
    SyntaxToken* _ptrEndRegionKeyword;
    SyntaxToken* _ptrEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ENDREGIONDIRECTIVETRIVIASYNTAX_H
