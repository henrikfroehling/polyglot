#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIENDOFMODULESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIENDOFMODULESYNTAX_H

#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
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

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIENDOFMODULESYNTAX_H
