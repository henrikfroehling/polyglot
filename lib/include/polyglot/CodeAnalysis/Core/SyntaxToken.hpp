#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAXTOKEN_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAXTOKEN_H

#include <string>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::CodeAnalysis
{

struct POLYGLOT_API SyntaxToken
{
    SyntaxKind kind;
    pg_size position;
    std::string text;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAXTOKEN_H
