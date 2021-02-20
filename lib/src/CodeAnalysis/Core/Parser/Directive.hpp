#ifndef POLYGLOT_CODEANALYSIS_CORE_PARSER_DIRECTIVE_H
#define POLYGLOT_CODEANALYSIS_CORE_PARSER_DIRECTIVE_H

#include <string_view>
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class Directive
{
public:
    explicit Directive(DirectiveTriviaSyntax* node) noexcept;
    virtual ~Directive() noexcept = default;
    inline SyntaxKind syntaxKind() const noexcept { return _pNode != nullptr ? static_cast<SyntaxNode*>(_pNode)->syntaxKind() : SyntaxKind::None; }
    inline bool isActive() const noexcept { return _pNode != nullptr ? _pNode->isActive() : false; }
    bool isBranchTaken() const noexcept;
    std::string_view identifier() const noexcept;

    friend bool operator==(const Directive& lhs,
                           const Directive& rhs) noexcept;

    friend bool operator!=(const Directive& lhs,
                           const Directive& rhs) noexcept;

private:
    DirectiveTriviaSyntax* _pNode;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_PARSER_DIRECTIVE_H
