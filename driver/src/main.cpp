#include <string>
#include <polyglot/CodeAnalysis/CodeAnalysis.hpp>
#include <polyglot/CodeAnalysis/Core/Syntax/SyntaxTree.hpp>

int main()
{
    using namespace polyglot::CodeAnalysis;

    const std::string sourceText{"unit Unit1;\n\n"
                                 "interface\n\n"
                                 "implementation\n\n"
                                 "end.\n"};

    SyntaxTree* syntaxTree = Delphi::parseSourceText(sourceText);
    delete syntaxTree;
    return 0;
}
