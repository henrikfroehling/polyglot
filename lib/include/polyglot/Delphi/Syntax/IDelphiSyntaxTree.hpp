#ifndef POLYGLOT_DELPHI_SYNTAX_IDELPHISYNTAXTREE_H
#define POLYGLOT_DELPHI_SYNTAX_IDELPHISYNTAXTREE_H

#include <string>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Syntax/ISyntaxTree.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::Delphi::Syntax
{

class POLYGLOT_API IDelphiSyntaxTree : public Core::Syntax::ISyntaxTree
{
public:
    virtual ~IDelphiSyntaxTree() noexcept {}

    static SharedPtr<IDelphiSyntaxTree> parseSourceText(std::string filename,
                                                        std::string source) noexcept;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_IDELPHISYNTAXTREE_H
