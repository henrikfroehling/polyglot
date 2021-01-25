#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_ENDREGIONDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_ENDREGIONDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;

class EndRegionDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit EndRegionDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                            SyntaxToken* startToken,
                                            SyntaxToken* endRegionKeyword,
                                            SyntaxToken* endOfDirectiveToken,
                                            bool isActive) noexcept;

    virtual ~EndRegionDirectiveTriviaSyntax() noexcept = default;
    inline virtual SyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual SyntaxToken* endRegionKeyword() const noexcept { return _pEndRegionKeyword; }
    inline virtual SyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static EndRegionDirectiveTriviaSyntax* create(SyntaxToken* startToken,
                                                  SyntaxToken* endRegionKeyword,
                                                  SyntaxToken* endOfDirectiveToken,
                                                  bool isActive) noexcept;

private:
    SyntaxToken* _pStartToken;
    SyntaxToken* _pEndRegionKeyword;
    SyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_ENDREGIONDIRECTIVETRIVIASYNTAX_H
