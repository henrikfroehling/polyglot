#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHIDIRECTIVEPARSER_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHIDIRECTIVEPARSER_H

#include <memory>
#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/DirectiveParser.hpp"
#include "polyglot/CodeAnalysis/Core/DirectiveStack.hpp"
#include "polyglot/CodeAnalysis/Core/Lexer.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxFacts.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiDirectiveParser final : public DirectiveParser
{
public:
    explicit DelphiDirectiveParser(std::shared_ptr<Lexer> lexer,
                                   const DirectiveStack& context,
                                   std::shared_ptr<SyntaxFacts> syntaxFacts) noexcept;

    SyntaxNodePtr parseDirective(bool isActive,
                                 bool endIsActive,
                                 bool isFirstAfterTokenInFile,
                                 bool isAfterNonWhitespaceOnLine) noexcept override final;

private:
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
    bool evaluateBool(const ExpressionSyntaxPtr& expression) const noexcept;
    bool isDefined(std::string_view id) const noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHIDIRECTIVEPARSER_H
