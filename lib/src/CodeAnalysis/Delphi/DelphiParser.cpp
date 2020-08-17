#include "polyglot/CodeAnalysis/Delphi/DelphiParser.hpp"
#include "polyglot/CodeAnalysis/Delphi/DelphiLexer.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiQualifiedNameSyntax.hpp"
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

SyntaxNodePtr DelphiParser::parseRoot() noexcept
{
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
    SyntaxTokenPtr ptrCurrentToken = currentToken();
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
            ptrCompilationUnit = std::make_shared<DelphiCompilationUnitSyntax>(SyntaxKind::CompilationUnit);
    }

    assert(ptrCompilationUnit != nullptr);
    return ptrCompilationUnit;
}

DelphiUnitModuleSyntaxPtr DelphiParser::parseUnitModule() noexcept
{
    DelphiUnitHeadingSyntaxPtr ptrHeading = nullptr;
    DelphiUnitInterfaceSectionSyntaxPtr ptrInterfaceSection = nullptr;
    DelphiUnitImplementationSectionSyntaxPtr ptrImplementationSection = nullptr;
    DelphiUnitInitializationSectionSyntaxPtr ptrInitializationSection = nullptr; // optional
    DelphiUnitFinalizationSectionSyntaxPtr ptrFinalizationSection = nullptr; // optional, but requires initialization section

    while (true)
    {
        SyntaxTokenPtr ptrCurrentToken = currentToken();

        switch (ptrCurrentToken->syntaxKind())
        {
            case SyntaxKind::UnitKeyword:
                ptrHeading = parseUnitHeading();
                break;
            case SyntaxKind::InterfaceKeyword:
                ptrInterfaceSection = parseUnitInterfaceSection();
                break;
            case SyntaxKind::ImplementationKeyword:
                ptrImplementationSection = parseUnitImplementationSection();
                break;
            case SyntaxKind::InitializationKeyword:
                ptrInitializationSection = parseUnitInitializationSection();
                break;
            case SyntaxKind::FinalizationKeyword:
                ptrFinalizationSection = parseUnitFinalizationSection();
                break;
            case SyntaxKind::EndOfFileToken:
                goto endOfUnit;
        }

        advance();
    }

endOfUnit:
    SyntaxTokenPtr ptrEOFToken = takeToken(SyntaxKind::EndOfFileToken);
    assert(ptrEOFToken != nullptr);

    assert(ptrHeading != nullptr);
    assert(ptrInterfaceSection != nullptr);
    assert(ptrImplementationSection != nullptr);

    auto ptrUnitModule = std::make_shared<DelphiUnitModuleSyntax>(std::move(ptrHeading), std::move(ptrInterfaceSection), std::move(ptrImplementationSection));
    ptrUnitModule->setEOFToken(std::move(ptrEOFToken));

    if (ptrFinalizationSection)
    {
        assert(ptrInitializationSection != nullptr);
        ptrUnitModule->setInitializationSection(std::move(ptrInitializationSection));
        ptrUnitModule->setFinalizationSection(std::move(ptrFinalizationSection));
    }

    return ptrUnitModule;
}

DelphiUnitHeadingSyntaxPtr DelphiParser::parseUnitHeading() noexcept
{
    SyntaxTokenPtr ptrUnitKeyword = takeToken(SyntaxKind::UnitKeyword);
    assert(ptrUnitKeyword != nullptr);

    DelphiNameSyntaxPtr ptrName = parseQualifiedName();
    assert(ptrName != nullptr);

    return std::make_shared<DelphiUnitHeadingSyntax>(std::move(ptrUnitKeyword), std::move(ptrName));
}

DelphiUnitInterfaceSectionSyntaxPtr DelphiParser::parseUnitInterfaceSection() noexcept
{
    return std::make_shared<DelphiUnitInterfaceSectionSyntax>();
}

DelphiUnitImplementationSectionSyntaxPtr DelphiParser::parseUnitImplementationSection() noexcept
{
    return std::make_shared<DelphiUnitImplementationSectionSyntax>();
}

DelphiUnitInitializationSectionSyntaxPtr DelphiParser::parseUnitInitializationSection() noexcept
{
    return std::make_shared<DelphiUnitInitializationSectionSyntax>();
}

DelphiUnitFinalizationSectionSyntaxPtr DelphiParser::parseUnitFinalizationSection() noexcept
{
    return std::make_shared<DelphiUnitFinalizationSectionSyntax>();
}

DelphiPackageModuleSyntaxPtr DelphiParser::parsePackageModule() noexcept
{
    return std::make_shared<DelphiPackageModuleSyntax>();
}

DelphiProgramModuleSyntaxPtr DelphiParser::parseProgramModule() noexcept
{
    return std::make_shared<DelphiProgramModuleSyntax>();
}

DelphiNameSyntaxPtr DelphiParser::parseQualifiedName() noexcept
{
    DelphiNameSyntaxPtr ptrName = parseIdentifierName();
    assert(ptrName != nullptr);

    while (currentToken()->syntaxKind() == SyntaxKind::DotToken)
    {
        SyntaxTokenPtr separator = takeToken();
        ptrName = parseQualifiedNameRight(std::move(ptrName), std::move(separator));
    }

    return ptrName;
}

DelphiNameSyntaxPtr DelphiParser::parseQualifiedNameRight(DelphiNameSyntaxPtr left,
                                                          SyntaxTokenPtr dotToken) noexcept
{
    assert(dotToken->syntaxKind() == SyntaxKind::DotToken);
    DelphiSimpleNameSyntaxPtr ptrRight = parseIdentifierName();
    assert(ptrRight != nullptr);
    return std::make_shared<DelphiQualifiedNameSyntax>(std::move(left), std::move(dotToken), std::move(ptrRight));
}

DelphiIdentifierNameSyntaxPtr DelphiParser::parseIdentifierName() noexcept
{
    SyntaxTokenPtr ptrCurrentToken = currentToken();

    if (ptrCurrentToken->syntaxKind() == SyntaxKind::IdentifierToken)
    {
        SyntaxTokenPtr identifier = takeToken();
        return std::make_shared<DelphiIdentifierNameSyntax>(std::move(identifier));
    }
    else
    {
        // TODO create missing token
        return nullptr;
    }
}

} // end namespace polyglot::CodeAnalysis
