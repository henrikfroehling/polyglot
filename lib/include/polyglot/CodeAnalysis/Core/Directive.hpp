#ifndef POLYGLOT_CODEANALYSIS_CORE_DIRECTIVE_H
#define POLYGLOT_CODEANALYSIS_CORE_DIRECTIVE_H

#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API Directive
{
public:
    explicit Directive(DirectiveTriviaSyntax* node) noexcept;
    virtual ~Directive() noexcept = default;
    inline SyntaxKind syntaxKind() const noexcept { return _node->syntaxKind(); }
    inline bool isActive() const noexcept { return _node->isActive(); }
    bool isBranchTaken() const noexcept;
    std::string_view identifier() const noexcept;

    friend bool operator==(const Directive& lhs,
                           const Directive& rhs) noexcept;

    friend bool operator!=(const Directive& lhs,
                           const Directive& rhs) noexcept;

private:
    DirectiveTriviaSyntax* _node;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_DIRECTIVE_H
