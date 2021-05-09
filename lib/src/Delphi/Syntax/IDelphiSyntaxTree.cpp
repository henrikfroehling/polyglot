#include "polyglot/Delphi/Syntax/IDelphiSyntaxTree.hpp"
#include "polyglot/Core/Text/SourceText.hpp"
#include "DelphiSyntaxTree.hpp"

namespace polyglot::Delphi::Syntax
{

SharedPtr<IDelphiSyntaxTree> IDelphiSyntaxTree::parseSourceText(std::string filename,
                                                                std::string source) noexcept
{
    SharedPtr<Core::Text::SourceText> ptrSourceText = std::make_unique<Core::Text::SourceText>(std::move(filename), std::move(source));
    ptrSourceText->parseLineStarts();
    return DelphiSyntaxTree::parseSourceText(std::move(ptrSourceText));
}

} // end namespace polyglot::Delphi::Syntax
