#include "Core/Syntax/SyntaxTree.hpp"

namespace polyglot::Core::Syntax
{

SyntaxTree::SyntaxTree(SharedPtr<Text::SourceText> sourceText,
                        ISyntaxNode* root,
                        SyntaxPool&& syntaxPool) noexcept
    : _ptrSourceText{std::move(sourceText)},
      _pRoot{root},
      _syntaxPool{std::move(syntaxPool)}
{}

} // end namespace polyglot::Core::Syntax
