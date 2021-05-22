#ifndef POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIMESSAGEDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIMESSAGEDIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiMessageDirectiveTriviaSyntax : public Core::Syntax::DirectiveTriviaSyntax
{
public:
    explicit DelphiMessageDirectiveTriviaSyntax(Core::Syntax::SyntaxKind syntaxKind,
                                                Core::Syntax::ISyntaxToken* startToken,
                                                Core::Syntax::ISyntaxToken* messageKeyword,
                                                Core::Syntax::ISyntaxToken* messageTypeToken,
                                                Core::Syntax::ISyntaxToken* messageLiteralToken,
                                                Core::Syntax::ISyntaxToken* endOfDirectiveToken) noexcept;

    virtual ~DelphiMessageDirectiveTriviaSyntax() noexcept {}
    inline virtual Core::Syntax::ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual Core::Syntax::ISyntaxToken* messageKeyword() const noexcept { return _pMessageKeyword; }
    inline virtual Core::Syntax::ISyntaxToken* messageTypeToken() const noexcept { return _pMessageTypeToken; }
    inline virtual Core::Syntax::ISyntaxToken* messageLiteralToken() const noexcept { return _pMessageLiteralToken; }
    inline virtual Core::Syntax::ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return false; }
    inline pg_size childCount() const noexcept override final { return _pMessageTypeToken != nullptr ? 5 : 4; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    virtual pg_string typeName() const noexcept override { return L"DelphiMessageDirectiveTriviaSyntax"; }

    static DelphiMessageDirectiveTriviaSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                      Core::Syntax::ISyntaxToken* startToken,
                                                      Core::Syntax::ISyntaxToken* messageKeyword,
                                                      Core::Syntax::ISyntaxToken* messageTypeToken,
                                                      Core::Syntax::ISyntaxToken* messageLiteralToken,
                                                      Core::Syntax::ISyntaxToken* endOfDirectiveToken) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pStartToken;
    Core::Syntax::ISyntaxToken* _pMessageKeyword;
    Core::Syntax::ISyntaxToken* _pMessageTypeToken; // optional
    Core::Syntax::ISyntaxToken* _pMessageLiteralToken;
    Core::Syntax::ISyntaxToken* _pEndOfDirectiveToken;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIMESSAGEDIRECTIVETRIVIASYNTAX_H
