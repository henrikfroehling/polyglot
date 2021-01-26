#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxTree.hpp"
#include "CodeAnalysis/Core/Parser/SyntaxPool.hpp"
#include "CodeAnalysis/Delphi/Parser/DelphiParser.hpp"

namespace polyglot::CodeAnalysis
{

DelphiSyntaxTree::DelphiSyntaxTree(SharedPtr<SourceText> sourceText,
                                   LanguageSyntaxNode* root,
                                   SyntaxPool&& syntaxPool) noexcept
    : SyntaxTree{std::move(sourceText), root, std::move(syntaxPool)}
{}

SharedPtr<DelphiSyntaxTree> DelphiSyntaxTree::parseSourceText(SharedPtr<SourceText> sourceText) noexcept
{
    SyntaxPool syntaxPool{};
    DelphiParser parser{sourceText, syntaxPool};
    LanguageSyntaxNode* pSyntaxTreeRoot = parser.parse();
    return std::make_shared<DelphiSyntaxTree>(std::move(sourceText), pSyntaxTreeRoot, std::move(syntaxPool));
}

} // end namespace polyglot::CodeAnalysis
