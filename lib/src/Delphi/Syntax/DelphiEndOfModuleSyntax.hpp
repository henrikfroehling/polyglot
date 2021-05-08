#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIENDOFMODULESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIENDOFMODULESYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "DelphiSyntaxNode.hpp"

namespace polyglot::Delphi::Syntax
{

class ISyntaxNode;
class ISyntaxToken;
class SyntaxFactory;

class DelphiEndOfModuleSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiEndOfModuleSyntax(ISyntaxToken* endKeyword,
                                     ISyntaxToken* dotToken) noexcept;

    virtual ~DelphiEndOfModuleSyntax() noexcept = default;

    inline ISyntaxToken* endKeyword() const noexcept { return _pEndKeyword; }
    inline ISyntaxToken* dotToken() const noexcept { return _pDotToken; }
    inline pg_size childCount() const noexcept override { return 2; }
    ISyntaxNode* child(pg_size index) const override;

    static DelphiEndOfModuleSyntax* create(SyntaxFactory& syntaxFactory,
                                           ISyntaxToken* endKeyword,
                                           ISyntaxToken* dotToken) noexcept;

private:
    ISyntaxToken* _pEndKeyword;
    ISyntaxToken* _pDotToken;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIENDOFMODULESYNTAX_H
