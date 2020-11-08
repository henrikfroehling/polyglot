#ifndef POLYGLOT_CODEANALYSIS_CORE_DELPHIDIRECTIVEPARSER_H
#define POLYGLOT_CODEANALYSIS_CORE_DELPHIDIRECTIVEPARSER_H

#include <memory>
#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/DirectiveStack.hpp"
#include "polyglot/CodeAnalysis/Core/Lexer.hpp"
#include "polyglot/CodeAnalysis/Core/Parser.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/DirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DirectiveParser : public Parser
{
public:
    DirectiveParser() = delete;
    explicit DirectiveParser(std::shared_ptr<Lexer> lexer,
                             const DirectiveStack& context) noexcept;

    SyntaxNodePtr parseDirective(bool isActive,
                                 bool endIsActive,
                                 bool isFirstAfterTokenInFile,
                                 bool isAfterNonWhitespaceOnLine) noexcept;

private:
    inline SyntaxNodePtr parseRoot() noexcept override { return nullptr; }

    DirectiveTriviaSyntaxPtr parseIfDirective(SyntaxTokenPtr openBraceDollarToken,
                                              SyntaxTokenPtr keyword,
                                              bool isActive) noexcept;

    DirectiveTriviaSyntaxPtr parseElseDirective(SyntaxTokenPtr openBraceDollarToken,
                                                SyntaxTokenPtr keyword,
                                                bool isActive,
                                                bool endIsActive) noexcept;

    DirectiveTriviaSyntaxPtr parseElseIfDirective(SyntaxTokenPtr openBraceDollarToken,
                                                  SyntaxTokenPtr keyword,
                                                  bool isActive,
                                                  bool endIsActive) noexcept;

    DirectiveTriviaSyntaxPtr parseEndIfDirective(SyntaxTokenPtr openBraceDollarToken,
                                                 SyntaxTokenPtr keyword,
                                                 bool isActive,
                                                 bool endIsActive) noexcept;

    DirectiveTriviaSyntaxPtr parseDefineOrUndefDirective(SyntaxTokenPtr openBraceDollarToken,
                                                         SyntaxTokenPtr keyword,
                                                         bool isActive,
                                                         bool isFollowingToken) noexcept;

    DirectiveTriviaSyntaxPtr parseRegionDirective(SyntaxTokenPtr openBraceDollarToken,
                                                  SyntaxTokenPtr keyword,
                                                  bool isActive) noexcept;

    DirectiveTriviaSyntaxPtr parseEndRegionDirective(SyntaxTokenPtr openBraceDollarToken,
                                                     SyntaxTokenPtr keyword,
                                                     bool isActive) noexcept;

    SyntaxTokenPtr parseEndOfDirective() noexcept;
    ExpressionSyntaxPtr parseExpression() noexcept;
    ExpressionSyntaxPtr parseLogicalOr() noexcept;
    ExpressionSyntaxPtr parseLogicalAnd() noexcept;
    ExpressionSyntaxPtr parseEquality() noexcept;
    ExpressionSyntaxPtr parseLogicalNot() noexcept;
    ExpressionSyntaxPtr parsePrimary() noexcept;
    bool evaluateBool(ExpressionSyntaxPtr expression) const noexcept;
    bool isDefined(std::string_view id) const noexcept;

private:
    const DirectiveStack& _context;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_DELPHIDIRECTIVEPARSER_H
