#include "Core/Syntax/SourceTree.hpp"

namespace polyglot::Core::Syntax
{

SyntaxTree::SyntaxTree(SharedPtr<SourceText> sourceText,
                        ISyntaxNode* root,
                        SyntaxPool&& syntaxPool) noexcept
    : _ptrSourceText{std::move(sourceText)},
      _pRoot{root},
      _syntaxPool{std::move(syntaxPool)}
{}

} // end namespace polyglot::Core::Syntax
