#include "CodeAnalysis/Delphi/DelphiParser.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Core/Syntax/Expressions/IdentifierNameExpressionSyntax.hpp"
#include "CodeAnalysis/Core/Syntax/Expressions/QualifiedNameExpressionSyntax.hpp"
#include "CodeAnalysis/Delphi/DelphiLexer.hpp"
#include "CodeAnalysis/Delphi/DelphiSyntaxFacts.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageModuleSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiProgramModuleSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitFinalizationSectionSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitHeadingSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitImplementationSectionSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInitializationSectionSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInterfaceSectionSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitModuleSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUsesClauseSyntax.hpp"
#include <cassert>
#include <iostream>

namespace polyglot::CodeAnalysis
{

DelphiParser::DelphiParser(SharedPtr<SourceText> sourceText,
                           SyntaxPool& syntaxPool) noexcept
    : Parser{std::make_shared<DelphiLexer>(sourceText, syntaxPool)}
{}

LanguageSyntaxNode* DelphiParser::parseRoot() noexcept
{
    if (DelphiSyntaxFacts::isModuleStart(currentToken()->syntaxKind()))
        return parseCompilationUnit();
    else
    {
        // TODO parse different entry points
        return nullptr;
    }
}

DelphiCompilationUnitSyntax* DelphiParser::parseCompilationUnit() noexcept
{
    LanguageSyntaxToken* pCurrentToken = currentToken();
    DelphiCompilationUnitSyntax* pCompilationUnit = nullptr;

    switch (pCurrentToken->syntaxKind())
    {
        case SyntaxKind::UnitKeyword:
            pCompilationUnit = parseUnitModule();
            break;
        case SyntaxKind::PackageKeyword:
            pCompilationUnit = parsePackageModule();
            break;
        case SyntaxKind::ProgramKeyword:
            pCompilationUnit = parseProgramModule();
            break;
        default:
        {
            auto compilationUnit = std::make_unique<DelphiCompilationUnitSyntax>(SyntaxKind::CompilationUnit);
            pCompilationUnit = static_cast<DelphiCompilationUnitSyntax*>(SyntaxPool::addSyntaxNode(std::move(compilationUnit)));
        }
    }

    assert(pCompilationUnit != nullptr);
    return pCompilationUnit;
}

DelphiUnitModuleSyntax* DelphiParser::parseUnitModule() noexcept
{
    DelphiUnitHeadingSyntax* pHeading = nullptr;
    DelphiUnitInterfaceSectionSyntax* pInterfaceSection = nullptr;
    DelphiUnitImplementationSectionSyntax* pImplementationSection = nullptr;
    DelphiUnitInitializationSectionSyntax* pInitializationSection = nullptr; // optional
    DelphiUnitFinalizationSectionSyntax* pFinalizationSection = nullptr; // optional, but requires initialization section

    while (true)
    {
        LanguageSyntaxToken* pCurrentToken = currentToken();

        switch (pCurrentToken->syntaxKind())
        {
            case SyntaxKind::UnitKeyword:
                pHeading = parseUnitHeading();
                break;
            case SyntaxKind::InterfaceKeyword:
                pInterfaceSection = parseUnitInterfaceSection();
                break;
            case SyntaxKind::ImplementationKeyword:
                pImplementationSection = parseUnitImplementationSection();
                break;
            case SyntaxKind::InitializationKeyword:
                pInitializationSection = parseUnitInitializationSection();
                advance();
                break;
            case SyntaxKind::FinalizationKeyword:
                pFinalizationSection = parseUnitFinalizationSection();
                advance();
                break;
            case SyntaxKind::EndKeyword:
            {
                if (peekToken(2)->syntaxKind() == SyntaxKind::DotToken)
                    goto endOfUnit;

                break;
            }
            case SyntaxKind::EndOfFileToken:
                goto endOfUnit;
        }
    }

endOfUnit:
    LanguageSyntaxToken* pEndKeyword = takeToken(SyntaxKind::EndKeyword);
    assert(pEndKeyword != nullptr);

    LanguageSyntaxToken* pDotToken = takeToken(SyntaxKind::DotToken);
    assert(pDotToken != nullptr);

    LanguageSyntaxToken* pEOFToken = takeToken(SyntaxKind::EndOfFileToken);
    assert(pEOFToken != nullptr);

    assert(pHeading != nullptr);
    assert(pInterfaceSection != nullptr);
    assert(pImplementationSection != nullptr);

    auto ptrUnitModule = std::make_unique<DelphiUnitModuleSyntax>(pHeading, pInterfaceSection, pImplementationSection,
                                                                  pEndKeyword, pDotToken);

    auto pUnitModule = static_cast<DelphiUnitModuleSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrUnitModule)));
    pUnitModule->setEOFToken(std::move(pEOFToken));

    if (pFinalizationSection)
    {
        assert(pInitializationSection != nullptr);
        pUnitModule->setInitializationSection(std::move(pInitializationSection));
        pUnitModule->setFinalizationSection(std::move(pFinalizationSection));
    }

    return pUnitModule;
}

DelphiUnitHeadingSyntax* DelphiParser::parseUnitHeading() noexcept
{
    LanguageSyntaxToken* pUnitKeyword = takeToken(SyntaxKind::UnitKeyword);
    assert(pUnitKeyword != nullptr);

    NameExpressionSyntax* pName = parseQualifiedName();
    assert(pName != nullptr);

    LanguageSyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    assert(pSemiColonToken != nullptr);

    auto ptrUnitHeading = std::make_unique<DelphiUnitHeadingSyntax>(pUnitKeyword, pName, pSemiColonToken);
    return static_cast<DelphiUnitHeadingSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrUnitHeading)));
}

DelphiUnitInterfaceSectionSyntax* DelphiParser::parseUnitInterfaceSection() noexcept
{
    LanguageSyntaxToken* pInterfaceKeyword = takeToken(SyntaxKind::InterfaceKeyword);
    assert(pInterfaceKeyword != nullptr);

    DelphiUsesClauseSyntax* pUses = parseUsesClause();
    assert(pUses != nullptr);

    auto ptrInferfaceSection = std::make_unique<DelphiUnitInterfaceSectionSyntax>(pInterfaceKeyword);
    ptrInferfaceSection->setUses(pUses);
    return static_cast<DelphiUnitInterfaceSectionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrInferfaceSection)));
}

DelphiUnitImplementationSectionSyntax* DelphiParser::parseUnitImplementationSection() noexcept
{
    LanguageSyntaxToken* pImplementationKeyword = takeToken(SyntaxKind::ImplementationKeyword);
    assert(pImplementationKeyword != nullptr);

    DelphiUsesClauseSyntax* pUses = parseUsesClause();
    assert(pUses != nullptr);

    auto ptrImplementationSection = std::make_unique<DelphiUnitImplementationSectionSyntax>(pImplementationKeyword);
    ptrImplementationSection->setUses(pUses);
    return static_cast<DelphiUnitImplementationSectionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrImplementationSection)));
}

DelphiUnitInitializationSectionSyntax* DelphiParser::parseUnitInitializationSection() noexcept
{
    auto ptrUnitInitializationSectionSyntax = std::make_unique<DelphiUnitInitializationSectionSyntax>();
    return static_cast<DelphiUnitInitializationSectionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrUnitInitializationSectionSyntax)));
}

DelphiUnitFinalizationSectionSyntax* DelphiParser::parseUnitFinalizationSection() noexcept
{
    auto ptrUnitFinalizationSectionSyntax = std::make_unique<DelphiUnitFinalizationSectionSyntax>();
    return static_cast<DelphiUnitFinalizationSectionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrUnitFinalizationSectionSyntax)));
}

DelphiPackageModuleSyntax* DelphiParser::parsePackageModule() noexcept
{
    auto ptrPackageModuleSyntax = std::make_unique<DelphiPackageModuleSyntax>();
    return static_cast<DelphiPackageModuleSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrPackageModuleSyntax)));
}

DelphiProgramModuleSyntax* DelphiParser::parseProgramModule() noexcept
{
    auto ptrProgramModuleSyntax = std::make_unique<DelphiProgramModuleSyntax>();
    return static_cast<DelphiProgramModuleSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrProgramModuleSyntax)));
}

DelphiUsesClauseSyntax* DelphiParser::parseUsesClause() noexcept
{
    LanguageSyntaxToken* pUsesKeyword = takeToken(SyntaxKind::UsesKeyword);
    std::vector<DelphiUnitReferenceDeclarationSyntax*> unitReferences{};

    while (true)
    {
        if (currentToken()->syntaxKind() == SyntaxKind::SemiColonToken)
            break;

        DelphiUnitReferenceDeclarationSyntax* pUnitReference = parseUnitReference();
        unitReferences.push_back(pUnitReference);
    }

    LanguageSyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    auto ptrUsesClauseSyntax = std::make_unique<DelphiUsesClauseSyntax>(pUsesKeyword, std::move(unitReferences), pSemiColonToken);
    return static_cast<DelphiUsesClauseSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrUsesClauseSyntax)));
}

DelphiUnitReferenceDeclarationSyntax* DelphiParser::parseUnitReference() noexcept
{
    if (currentToken()->syntaxKind() != SyntaxKind::IdentifierToken)
        return nullptr; // TODO error handling

    NameExpressionSyntax* pUnitName = parseQualifiedName();
    assert(pUnitName != nullptr);

    auto ptrUnitReference = std::make_unique<DelphiUnitReferenceDeclarationSyntax>(pUnitName);
    auto pUnitReference = static_cast<DelphiUnitReferenceDeclarationSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrUnitReference)));

    if (currentToken()->syntaxKind() == SyntaxKind::InKeyword)
    {
        LanguageSyntaxToken* pInKeyword = takeToken(SyntaxKind::InKeyword);
        assert(pInKeyword != nullptr);

        LanguageSyntaxToken* pSourceFile = takeToken(SyntaxKind::SingleQuotationStringLiteralToken);
        assert(pSourceFile != nullptr);

        pUnitReference->setInKeyword(pInKeyword);
        pUnitReference->setSourceFile(pSourceFile);
    }

    if (currentToken()->syntaxKind() == SyntaxKind::CommaToken)
    {
        LanguageSyntaxToken* pCommaToken = takeToken(SyntaxKind::CommaToken);
        assert(pCommaToken != nullptr);
        pUnitReference->setCommaToken(pCommaToken);
    }

    return pUnitReference;
}

NameExpressionSyntax* DelphiParser::parseQualifiedName() noexcept
{
    NameExpressionSyntax* pName = parseIdentifierName();
    assert(pName != nullptr);

    while (currentToken()->syntaxKind() == SyntaxKind::DotToken)
    {
        LanguageSyntaxToken* pSeparator = takeToken();
        pName = parseQualifiedNameRight(pName, pSeparator);
    }

    return pName;
}

NameExpressionSyntax* DelphiParser::parseQualifiedNameRight(NameExpressionSyntax* left,
                                                            LanguageSyntaxToken* dotToken) noexcept
{
    assert(dotToken->syntaxKind() == SyntaxKind::DotToken);
    SimpleNameExpressionSyntax* pRight = parseIdentifierName();
    assert(pRight != nullptr);

    auto ptrNameExpression = std::make_unique<QualifiedNameExpressionSyntax>(left, dotToken, pRight);
    return static_cast<QualifiedNameExpressionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrNameExpression)));
}

IdentifierNameExpressionSyntax* DelphiParser::parseIdentifierName() noexcept
{
    LanguageSyntaxToken* pCurrentToken = currentToken();

    if (pCurrentToken->syntaxKind() == SyntaxKind::IdentifierToken)
    {
        LanguageSyntaxToken* pIdentifier = takeToken();

        auto ptrIdentifierNameExpression = std::make_unique<IdentifierNameExpressionSyntax>(pIdentifier);
        return static_cast<IdentifierNameExpressionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrIdentifierNameExpression)));
    }
    else
    {
        // TODO create missing token
        return nullptr;
    }
}

} // end namespace polyglot::CodeAnalysis
