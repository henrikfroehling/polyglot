#ifndef POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIIFDEFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIIFDEFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Trivia/DelphiConditionalDirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiIfDefDirectiveTriviaSyntax : public DelphiConditionalDirectiveTriviaSyntax
{
public:
    explicit DelphiIfDefDirectiveTriviaSyntax(Core::Syntax::SyntaxKind syntaxKind,
                                              Core::Syntax::ISyntaxToken* startToken,
                                              Core::Syntax::ISyntaxToken* ifDefKeyword,
                                              Core::Syntax::ISyntaxToken* name,
                                              Core::Syntax::ISyntaxToken* endOfDirectiveToken,
                                              bool isActive,
                                              bool isBranchTaken) noexcept;

    virtual ~DelphiIfDefDirectiveTriviaSyntax() noexcept {}
    inline virtual Core::Syntax::ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual Core::Syntax::ISyntaxToken* ifDefKeyword() const noexcept { return _pIfDefKeyword; }
    inline virtual Core::Syntax::ISyntaxToken* name() const noexcept { return _pName; }
    inline virtual Core::Syntax::ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }
    inline virtual bool conditionValue() const noexcept override { return false; }
    inline virtual DelphiExpressionSyntax* condition() const noexcept override { return nullptr; }
    inline pg_size childCount() const noexcept override final { return 4; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline virtual pg_string typeName() const noexcept override { return L"DelphiIfDefDirectiveTriviaSyntax"; }

    static DelphiIfDefDirectiveTriviaSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                    Core::Syntax::ISyntaxToken* startToken,
                                                    Core::Syntax::ISyntaxToken* ifDefKeyword,
                                                    Core::Syntax::ISyntaxToken* name,
                                                    Core::Syntax::ISyntaxToken* endOfDirectiveToken,
                                                    bool isActive,
                                                    bool isBranchTaken) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pStartToken;
    Core::Syntax::ISyntaxToken* _pIfDefKeyword;
    Core::Syntax::ISyntaxToken* _pName;
    Core::Syntax::ISyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIIFDEFDIRECTIVETRIVIASYNTAX_H
