#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHISYNTAXTREE_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHISYNTAXTREE_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/ISyntaxTree.hpp"
#include "CodeAnalysis/Core/Text/SourceText.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxNode;
class SyntaxPool;

class POLYGLOT_API DelphiSyntaxTree : public ISyntaxTree
{
public:
    DelphiSyntaxTree() noexcept = default;

    explicit DelphiSyntaxTree(SharedPtr<SourceText> sourceText,
                              LanguageSyntaxNode* root,
                              SyntaxPool&& syntaxPool) noexcept;

    static SharedPtr<DelphiSyntaxTree> parseSourceText(SharedPtr<SourceText> sourceText) noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHISYNTAXTREE_H
