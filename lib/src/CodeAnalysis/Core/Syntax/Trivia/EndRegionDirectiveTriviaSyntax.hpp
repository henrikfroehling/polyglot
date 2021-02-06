#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_ENDREGIONDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_ENDREGIONDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;
class SyntaxFactory;

class EndRegionDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit EndRegionDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                            LanguageSyntaxToken* startToken,
                                            LanguageSyntaxToken* endRegionKeyword,
                                            LanguageSyntaxToken* endOfDirectiveToken,
                                            bool isActive) noexcept;

    virtual ~EndRegionDirectiveTriviaSyntax() noexcept = default;
    inline virtual LanguageSyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual LanguageSyntaxToken* endRegionKeyword() const noexcept { return _pEndRegionKeyword; }
    inline virtual LanguageSyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static EndRegionDirectiveTriviaSyntax* create(SyntaxFactory& syntaxFactory,
                                                  LanguageSyntaxToken* startToken,
                                                  LanguageSyntaxToken* endRegionKeyword,
                                                  LanguageSyntaxToken* endOfDirectiveToken,
                                                  bool isActive) noexcept;

private:
    LanguageSyntaxToken* _pStartToken;
    LanguageSyntaxToken* _pEndRegionKeyword;
    LanguageSyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_ENDREGIONDIRECTIVETRIVIASYNTAX_H
