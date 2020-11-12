#include "polyglot/CodeAnalysis/CodeAnalysis.hpp"
#include "polyglot/CodeAnalysis/Core/Text/SourceText.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxTree.hpp"

namespace polyglot::CodeAnalysis
{
namespace Delphi
{

std::shared_ptr<SyntaxTree> parseSourceText(std::string filename,
                                            std::string source) noexcept
{
    SourceTextPtr ptrSourceText = std::make_shared<SourceText>(std::move(filename), std::move(source));
    ptrSourceText->parseLineStarts();
    return DelphiSyntaxTree::parseSourceText(std::move(ptrSourceText));
}

} // end namespace Delphi
} // end namespace polyglot::CodeAnalysis
