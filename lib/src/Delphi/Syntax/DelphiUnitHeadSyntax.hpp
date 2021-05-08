#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIUNITHEADSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIUNITHEADSYNTAX_H

#include "DelphiSyntaxNode.hpp"

namespace polyglot::Delphi::Syntax
{

class ISyntaxNode;
class ISyntaxToken;
class NameExpressionSyntax;
class SyntaxFactory;

class DelphiUnitHeadSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitHeadSyntax(ISyntaxToken* unitKeyword,
                                  NameExpressionSyntax* name,
                                  ISyntaxToken* semiColonToken,
                                  ISyntaxToken* inKeyword = nullptr,
                                  ISyntaxToken* filename = nullptr) noexcept;

    virtual ~DelphiUnitHeadSyntax() noexcept = default;
    inline ISyntaxToken* unitKeyword() const noexcept { return _pUnitKeyword; }
    inline NameExpressionSyntax* name() const noexcept { return _pName; }
    inline ISyntaxToken* semiColonToken() const noexcept { return _pSemiColonToken; }
    inline ISyntaxToken* inKeyword() const noexcept { return _pInKeyword; }
    inline ISyntaxToken* filename() const noexcept { return _pFilename; }
    inline pg_size childCount() const noexcept override { return _pFilename != nullptr ? 5 : 3; }
    ISyntaxNode* child(pg_size index) const override;

    static DelphiUnitHeadSyntax* create(SyntaxFactory& syntaxFactory,
                                        ISyntaxToken* unitKeyword,
                                        NameExpressionSyntax* name,
                                        ISyntaxToken* semiColonToken,
                                        ISyntaxToken* inKeyword = nullptr,
                                        ISyntaxToken* filename = nullptr) noexcept;

private:
    ISyntaxToken* _pUnitKeyword;
    NameExpressionSyntax* _pName;
    ISyntaxToken* _pSemiColonToken;
    ISyntaxToken* _pInKeyword; // optional
    ISyntaxToken* _pFilename; // optional
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIUNITHEADSYNTAX_H
