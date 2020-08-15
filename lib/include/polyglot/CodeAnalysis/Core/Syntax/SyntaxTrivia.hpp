#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIA_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIA_H

#include <memory>
#include <string_view>
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "polyglot/polyglot_global.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API SyntaxTrivia : public SyntaxNode
{
public:
    SyntaxTrivia() noexcept;

    explicit SyntaxTrivia(SyntaxKind syntaxKind,
                          std::string_view text) noexcept;

    virtual ~SyntaxTrivia() noexcept;
    SyntaxTrivia(const SyntaxTrivia&) noexcept = default;
    SyntaxTrivia(SyntaxTrivia&&) noexcept = default;
    SyntaxTrivia& operator=(const SyntaxTrivia&) noexcept = default;
    SyntaxTrivia& operator=(SyntaxTrivia&&) noexcept = default;
    inline bool isTrivia() const noexcept override { return true; }

private:
    std::string_view _text;
};

using SyntaxTriviaPtr = std::shared_ptr<SyntaxTrivia>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIA_H
