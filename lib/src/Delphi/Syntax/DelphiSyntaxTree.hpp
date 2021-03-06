#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHISYNTAXTREE_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHISYNTAXTREE_H

#include "polyglot/Delphi/Syntax/IDelphiSyntaxTree.hpp"
#include "Core/Syntax/SyntaxTree.hpp"
#include "Core/Text/SourceText.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;
class SyntaxPool;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiSyntaxTree : public Core::Syntax::SyntaxTree, public virtual IDelphiSyntaxTree
{
public:
    explicit DelphiSyntaxTree(SharedPtr<Core::Text::SourceText> sourceText,
                              Core::Syntax::ISyntaxNode* root,
                              Core::Syntax::SyntaxPool&& syntaxPool) noexcept;

    inline Core::Syntax::ISyntaxNode* root() const noexcept override final { return Core::Syntax::SyntaxTree::root(); }
    inline Core::LanguageKind languageKind() const noexcept override final { return Core::LanguageKind::Delphi; }

    inline const SharedPtr<Core::Text::SourceText>& sourceText() const noexcept override { return Core::Syntax::SyntaxTree::sourceText(); }

    static SharedPtr<IDelphiSyntaxTree> parseSourceText(SharedPtr<Core::Text::SourceText> sourceText) noexcept;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHISYNTAXTREE_H
