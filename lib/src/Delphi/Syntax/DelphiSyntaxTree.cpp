#include "Delphi/Syntax/DelphiSyntaxTree.hpp"
#include "Core/Syntax/SyntaxNode.hpp"
#include "Core/Syntax/SyntaxPool.hpp"
#include "Delphi/Parser/DelphiParser.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiSyntaxTree::DelphiSyntaxTree(SharedPtr<Core::Text::SourceText> sourceText,
                                   Core::Syntax::ISyntaxNode* root,
                                   Core::Syntax::SyntaxPool&& syntaxPool) noexcept
    : IDelphiSyntaxTree{},
      Core::Syntax::SyntaxTree{std::move(sourceText), root, std::move(syntaxPool)}
{
    static_cast<Core::Syntax::SyntaxNode*>(_pRoot)->setSyntaxTree(static_cast<IDelphiSyntaxTree*>(this));
}

SharedPtr<IDelphiSyntaxTree> DelphiSyntaxTree::parseSourceText(SharedPtr<Core::Text::SourceText> sourceText) noexcept
{
    Parser::DelphiParser parser{sourceText};
    Core::Syntax::ISyntaxNode* pSyntaxTreeRoot = parser.parse();
    return std::make_shared<DelphiSyntaxTree>(std::move(sourceText), pSyntaxTreeRoot, parser.takeSyntaxPool());
}

} // end namespace polyglot::Delphi::Syntax
