#include "polyglot/CodeAnalysis/Delphi/DelphiParser.hpp"
#include "polyglot/CodeAnalysis/Delphi/DelphiLexer.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxFacts.hpp"
#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>

namespace polyglot::CodeAnalysis
{

DelphiParser::DelphiParser(SourceText* sourceText) noexcept
    : Parser{std::make_unique<DelphiLexer>(sourceText)}
{}

SyntaxNodePtr DelphiParser::parseCore() noexcept
{
    Parser::parse();
    if (DelphiSyntaxFacts::isModuleStart(currentToken()->syntaxKind()))
        return parseCompilationUnit();
    else
    {
        // TODO parse different entry points
        return nullptr;
    }
}

DelphiCompilationUnitSyntaxPtr DelphiParser::parseCompilationUnit() noexcept
{
    auto ptrCurrentToken = currentToken();
    DelphiCompilationUnitSyntaxPtr ptrCompilationUnit = nullptr;

    switch (ptrCurrentToken->syntaxKind())
    {
        case SyntaxKind::UnitKeyword:
            ptrCompilationUnit = parseUnitModule();
            break;
        case SyntaxKind::PackageKeyword:
            ptrCompilationUnit = parsePackageModule();
            break;
        case SyntaxKind::ProgramKeyword:
            ptrCompilationUnit = parseProgramModule();
            break;
        default:
            ptrCompilationUnit = std::make_shared<DelphiCompilationUnitSyntax>(SyntaxKind::CompilationUnitSyntax);
    }

    assert(ptrCompilationUnit != nullptr);
    auto ptrEOFToken = takeToken(SyntaxKind::EndOfFileToken);
    assert(ptrEOFToken != nullptr);
    ptrCompilationUnit->setEOFToken(ptrEOFToken);
    return ptrCompilationUnit;
}

DelphiUnitModuleSyntaxPtr DelphiParser::parseUnitModule() noexcept
{
    return std::make_shared<DelphiUnitModuleSyntax>(SyntaxKind::UnitModuleSyntax);
}

DelphiPackageModuleSyntaxPtr DelphiParser::parsePackageModule() noexcept
{
    return std::make_shared<DelphiPackageModuleSyntax>(SyntaxKind::PackageModuleSyntax);
}

DelphiProgramModuleSyntaxPtr DelphiParser::parseProgramModule() noexcept
{
    return std::make_shared<DelphiProgramModuleSyntax>(SyntaxKind::ProgramModuleSyntax);
}

} // end namespace polyglot::CodeAnalysis
