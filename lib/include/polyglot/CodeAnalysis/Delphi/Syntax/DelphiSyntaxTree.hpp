#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXTREE_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXTREE_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTree.hpp"
#include "polyglot/CodeAnalysis/Core/Text/SourceText.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiSyntaxTree : public SyntaxTree
{
public:
    DelphiSyntaxTree() noexcept = default;

    explicit DelphiSyntaxTree(SharedPtr<SourceText> sourceText,
                              SyntaxNode* root) noexcept;

    static SharedPtr<DelphiSyntaxTree> parseSourceText(SharedPtr<SourceText> sourceText) noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXTREE_H
