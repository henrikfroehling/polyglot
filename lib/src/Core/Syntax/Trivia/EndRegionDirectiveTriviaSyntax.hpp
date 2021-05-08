#ifndef POLYGLOT_CORE_SYNTAX_TRIVIA_ENDREGIONDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CORE_SYNTAX_TRIVIA_ENDREGIONDIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "DirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;
class ISyntaxToken;
class SyntaxFactory;

class EndRegionDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit EndRegionDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                            ISyntaxToken* startToken,
                                            ISyntaxToken* endRegionKeyword,
                                            ISyntaxToken* endOfDirectiveToken,
                                            bool isActive) noexcept;

    virtual ~EndRegionDirectiveTriviaSyntax() noexcept = default;
    inline virtual ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual ISyntaxToken* endRegionKeyword() const noexcept { return _pEndRegionKeyword; }
    inline virtual ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline pg_size childCount() const noexcept override { return 3; }
    ISyntaxNode* child(pg_size index) const override;

    static EndRegionDirectiveTriviaSyntax* create(SyntaxFactory& syntaxFactory,
                                                  ISyntaxToken* startToken,
                                                  ISyntaxToken* endRegionKeyword,
                                                  ISyntaxToken* endOfDirectiveToken,
                                                  bool isActive) noexcept;

private:
    ISyntaxToken* _pStartToken;
    ISyntaxToken* _pEndRegionKeyword;
    ISyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_TRIVIA_ENDREGIONDIRECTIVETRIVIASYNTAX_H
