#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxTree.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include "CodeAnalysis/Delphi/Parser/DelphiParser.hpp"

namespace polyglot::CodeAnalysis
{

DelphiSyntaxTree::DelphiSyntaxTree(SharedPtr<SourceText> sourceText,
                                   LanguageSyntaxNode* root,
                                   SyntaxPool&& syntaxPool) noexcept
    : ISyntaxTree{std::move(sourceText), root, std::move(syntaxPool)}
{}

SharedPtr<DelphiSyntaxTree> DelphiSyntaxTree::parseSourceText(SharedPtr<SourceText> sourceText) noexcept
{
    DelphiParser parser{sourceText};
    LanguageSyntaxNode* pSyntaxTreeRoot = parser.parse();
    return std::make_shared<DelphiSyntaxTree>(std::move(sourceText), pSyntaxTreeRoot, parser.takeSyntaxPool());
}

} // end namespace polyglot::CodeAnalysis
