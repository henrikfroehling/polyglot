#ifndef POLYGLOT_CORE_SYNTAX_TRIVIA_REGIONDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CORE_SYNTAX_TRIVIA_REGIONDIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "DirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;
class ISyntaxToken;
class SyntaxFactory;

class RegionDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit RegionDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                         ISyntaxToken* startToken,
                                         ISyntaxToken* regionKeyword,
                                         ISyntaxToken* endOfDirectiveToken,
                                         bool isActive) noexcept;

    virtual ~RegionDirectiveTriviaSyntax() noexcept = default;
    inline virtual ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual ISyntaxToken* regionKeyword() const noexcept { return _pRegionKeyword; }
    inline virtual ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline pg_size childCount() const noexcept override { return 3; }
    ISyntaxNode* child(pg_size index) const override;

    static RegionDirectiveTriviaSyntax* create(SyntaxFactory& syntaxFactory,
                                               ISyntaxToken* startToken,
                                               ISyntaxToken* regionKeyword,
                                               ISyntaxToken* endOfDirectiveToken,
                                               bool isActive) noexcept;

private:
    ISyntaxToken* _pStartToken;
    ISyntaxToken* _pRegionKeyword;
    ISyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_TRIVIA_REGIONDIRECTIVETRIVIASYNTAX_H
