#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHISYNTAXTREE_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHISYNTAXTREE_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Syntax/ISyntaxTree.hpp"
#include "Core/Text/SourceText.hpp"

namespace polyglot::Delphi::Syntax
{

class ISyntaxNode;
class SyntaxPool;

class POLYGLOT_API DelphiSyntaxTree : public ISyntaxTree
{
public:
    DelphiSyntaxTree() noexcept = default;

    explicit DelphiSyntaxTree(SharedPtr<SourceText> sourceText,
                              ISyntaxNode* root,
                              SyntaxPool&& syntaxPool) noexcept;

    static SharedPtr<DelphiSyntaxTree> parseSourceText(SharedPtr<SourceText> sourceText) noexcept;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHISYNTAXTREE_H
