#ifndef POLYGLOT_CORE_SYNTAX_SYNTAXTREE_H
#define POLYGLOT_CORE_SYNTAX_SYNTAXTREE_H

#include "polyglot/Core/Syntax/ISyntaxTree.hpp"
#include "polyglot/Core/LanguageKind.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Text/SourceText.hpp"
#include "SyntaxPool.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;

class SyntaxTree : public ISyntaxTree
{
public:
    virtual ~SyntaxTree() noexcept {}

    inline ISyntaxNode* root() const noexcept override final { return _pRoot; }
    inline virtual LanguageKind languageKind() const noexcept override { return LanguageKind::Unknown; }

protected:
    explicit SyntaxTree(SharedPtr<Text::SourceText> sourceText,
                        ISyntaxNode* root,
                        SyntaxPool&& syntaxPool) noexcept;

protected:
    SharedPtr<Text::SourceText> _ptrSourceText;
    ISyntaxNode* _pRoot;
    SyntaxPool _syntaxPool;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_SYNTAXTREE_H
