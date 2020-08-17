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

DelphiParser::DelphiParser(SourceTextPtr sourceText) noexcept
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
                advance();
                break;
            case SyntaxKind::FinalizationKeyword:
                ptrFinalizationSection = parseUnitFinalizationSection();
                advance();
                break;
            case SyntaxKind::EndKeyword:
            {
                if (peekToken(1)->syntaxKind() == SyntaxKind::DotToken)
                    goto endOfUnit;

                break;
            }
            case SyntaxKind::EndOfFileToken:
                goto endOfUnit;
        }
    }

endOfUnit:
    SyntaxTokenPtr ptrEndKeyword = takeToken(SyntaxKind::EndKeyword);
    assert(ptrEndKeyword != nullptr);

    SyntaxTokenPtr ptrDotToken = takeToken(SyntaxKind::DotToken);
    assert(ptrDotToken != nullptr);

    SyntaxTokenPtr ptrEOFToken = takeToken(SyntaxKind::EndOfFileToken);
    assert(ptrEOFToken != nullptr);

    assert(ptrHeading != nullptr);
    assert(ptrInterfaceSection != nullptr);
    assert(ptrImplementationSection != nullptr);

    auto ptrUnitModule = std::make_shared<DelphiUnitModuleSyntax>(std::move(ptrHeading), std::move(ptrInterfaceSection), std::move(ptrImplementationSection),
                                                                  std::move(ptrEndKeyword), std::move(ptrDotToken));

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

    SyntaxTokenPtr ptrSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    assert(ptrSemiColonToken != nullptr);

    return std::make_shared<DelphiUnitHeadingSyntax>(std::move(ptrUnitKeyword), std::move(ptrName), std::move(ptrSemiColonToken));
}

DelphiUnitInterfaceSectionSyntaxPtr DelphiParser::parseUnitInterfaceSection() noexcept
{
    SyntaxTokenPtr ptrInterfaceKeyword = takeToken(SyntaxKind::InterfaceKeyword);
    assert(ptrInterfaceKeyword != nullptr);

    DelphiUsesClauseSyntaxPtr ptrUses = parseUsesClause();
    assert(ptrUses != nullptr);

    auto ptrInterfaceSection = std::make_shared<DelphiUnitInterfaceSectionSyntax>(std::move(ptrInterfaceKeyword));
    ptrInterfaceSection->setUses(std::move(ptrUses));

    return ptrInterfaceSection;
}

DelphiUnitImplementationSectionSyntaxPtr DelphiParser::parseUnitImplementationSection() noexcept
{
    SyntaxTokenPtr ptrImplementationKeyword = takeToken(SyntaxKind::ImplementationKeyword);
    assert(ptrImplementationKeyword != nullptr);

    DelphiUsesClauseSyntaxPtr ptrUses = parseUsesClause();
    assert(ptrUses != nullptr);

    auto ptrImplementationSection = std::make_shared<DelphiUnitImplementationSectionSyntax>(std::move(ptrImplementationKeyword));
    ptrImplementationSection->setUses(std::move(ptrUses));

    return ptrImplementationSection;
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

DelphiUsesClauseSyntaxPtr DelphiParser::parseUsesClause() noexcept
{
    SyntaxTokenPtr ptrUsesKeyword = takeToken(SyntaxKind::UsesKeyword);
    std::vector<DelphiUnitReferenceDeclarationSyntaxPtr> unitReferences{};

    while (true)
    {
        if (currentToken()->syntaxKind() == SyntaxKind::SemiColonToken)
            break;

        DelphiUnitReferenceDeclarationSyntaxPtr unitReference = parseUnitReference();
        unitReferences.push_back(std::move(unitReference));
    }

    SyntaxTokenPtr ptrSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    return std::make_shared<DelphiUsesClauseSyntax>(std::move(ptrUsesKeyword), std::move(unitReferences), std::move(ptrSemiColonToken));
}

DelphiUnitReferenceDeclarationSyntaxPtr DelphiParser::parseUnitReference() noexcept
{
    if (currentToken()->syntaxKind() != SyntaxKind::IdentifierToken)
        return nullptr; // TODO error handling

    DelphiNameSyntaxPtr ptrUnitName = parseQualifiedName();
    assert(ptrUnitName != nullptr);

    auto ptrUnitReference = std::make_shared<DelphiUnitReferenceDeclarationSyntax>(std::move(ptrUnitName));

    if (currentToken()->syntaxKind() == SyntaxKind::InKeyword)
    {
        SyntaxTokenPtr ptrInKeyword = takeToken(SyntaxKind::InKeyword);
        assert(ptrInKeyword != nullptr);

        SyntaxTokenPtr ptrSourceFile = takeToken(SyntaxKind::SingleQuotationStringLiteralToken);
        assert(ptrSourceFile != nullptr);

        ptrUnitReference->setInKeyword(std::move(ptrInKeyword));
        ptrUnitReference->setSourceFile(std::move(ptrSourceFile));
    }

    if (currentToken()->syntaxKind() == SyntaxKind::CommaToken)
    {
        SyntaxTokenPtr ptrCommaToken = takeToken(SyntaxKind::CommaToken);
        assert(ptrCommaToken != nullptr);
        ptrUnitReference->setCommaToken(std::move(ptrCommaToken));
    }

    return ptrUnitReference;
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
