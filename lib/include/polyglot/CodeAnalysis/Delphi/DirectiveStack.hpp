#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DIRECTIVESTACK_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DIRECTIVESTACK_H

#include <stack>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Delphi/Directive.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DirectiveStack
{
public:
    DirectiveStack() noexcept;

private:
    std::stack<DirectivePtr> _directives;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DIRECTIVESTACK_H
