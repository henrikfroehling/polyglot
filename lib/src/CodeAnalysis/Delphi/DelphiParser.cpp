#include "polyglot/CodeAnalysis/Delphi/DelphiParser.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/IdentifierNameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/QualifiedNameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/DelphiLexer.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiProgramModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitFinalizationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitHeadingSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitImplementationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInitializationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInterfaceSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUsesClauseSyntax.hpp"
#include <cassert>
#include <iostream>

namespace polyglot::CodeAnalysis
{

DelphiParser::DelphiParser(SharedPtr<SourceText> sourceText) noexcept
    : Parser{std::make_shared<DelphiLexer>(sourceText)},
      _ptrSyntaxFacts{std::make_shared<DelphiSyntaxFacts>()}
{}

SyntaxNode* DelphiParser::parseRoot() noexcept
{
    if (_ptrSyntaxFacts->isModuleStart(currentToken()->syntaxKind()))
        return parseCompilationUnit();
    else
    {
        // TODO parse different entry points
        return nullptr;
    }
}

DelphiCompilationUnitSyntax* DelphiParser::parseCompilationUnit() noexcept
{
    SyntaxToken* ptrCurrentToken = currentToken();
    DelphiCompilationUnitSyntax* ptrCompilationUnit = nullptr;

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
        {
            auto compilationUnit = std::make_unique<DelphiCompilationUnitSyntax>(SyntaxKind::CompilationUnit);
            ptrCompilationUnit = static_cast<DelphiCompilationUnitSyntax*>(SyntaxPool::addSyntaxNode(std::move(compilationUnit)));
        }
    }

    assert(ptrCompilationUnit != nullptr);
    return ptrCompilationUnit;
}

DelphiUnitModuleSyntax* DelphiParser::parseUnitModule() noexcept
{
    DelphiUnitHeadingSyntax* ptrHeading = nullptr;
    DelphiUnitInterfaceSectionSyntax* ptrInterfaceSection = nullptr;
    DelphiUnitImplementationSectionSyntax* ptrImplementationSection = nullptr;
    DelphiUnitInitializationSectionSyntax* ptrInitializationSection = nullptr; // optional
    DelphiUnitFinalizationSectionSyntax* ptrFinalizationSection = nullptr; // optional, but requires initialization section

    while (true)
    {
        SyntaxToken* ptrCurrentToken = currentToken();

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
    SyntaxToken* ptrEndKeyword = takeToken(SyntaxKind::EndKeyword);
    assert(ptrEndKeyword != nullptr);

    SyntaxToken* ptrDotToken = takeToken(SyntaxKind::DotToken);
    assert(ptrDotToken != nullptr);

    SyntaxToken* ptrEOFToken = takeToken(SyntaxKind::EndOfFileToken);
    assert(ptrEOFToken != nullptr);

    assert(ptrHeading != nullptr);
    assert(ptrInterfaceSection != nullptr);
    assert(ptrImplementationSection != nullptr);

    auto unitModule = std::make_unique<DelphiUnitModuleSyntax>(ptrHeading, ptrInterfaceSection, ptrImplementationSection,
                                                               ptrEndKeyword, ptrDotToken);

    auto ptrUnitModule = static_cast<DelphiUnitModuleSyntax*>(SyntaxPool::addSyntaxNode(std::move(unitModule)));
    ptrUnitModule->setEOFToken(std::move(ptrEOFToken));

    if (ptrFinalizationSection)
    {
        assert(ptrInitializationSection != nullptr);
        ptrUnitModule->setInitializationSection(std::move(ptrInitializationSection));
        ptrUnitModule->setFinalizationSection(std::move(ptrFinalizationSection));
    }

    return ptrUnitModule;
}

DelphiUnitHeadingSyntax* DelphiParser::parseUnitHeading() noexcept
{
    SyntaxToken* ptrUnitKeyword = takeToken(SyntaxKind::UnitKeyword);
    assert(ptrUnitKeyword != nullptr);

    NameExpressionSyntax* ptrName = parseQualifiedName();
    assert(ptrName != nullptr);

    SyntaxToken* ptrSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    assert(ptrSemiColonToken != nullptr);

    auto ptrUnitHeading = std::make_unique<DelphiUnitHeadingSyntax>(ptrUnitKeyword, ptrName, ptrSemiColonToken);
    return static_cast<DelphiUnitHeadingSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrUnitHeading)));
}

DelphiUnitInterfaceSectionSyntax* DelphiParser::parseUnitInterfaceSection() noexcept
{
    SyntaxToken* ptrInterfaceKeyword = takeToken(SyntaxKind::InterfaceKeyword);
    assert(ptrInterfaceKeyword != nullptr);

    DelphiUsesClauseSyntax* ptrUses = parseUsesClause();
    assert(ptrUses != nullptr);

    auto ptrInferfaceSection = std::make_unique<DelphiUnitInterfaceSectionSyntax>(ptrInterfaceKeyword);
    ptrInferfaceSection->setUses(ptrUses);
    return static_cast<DelphiUnitInterfaceSectionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrInferfaceSection)));
}

DelphiUnitImplementationSectionSyntax* DelphiParser::parseUnitImplementationSection() noexcept
{
    SyntaxToken* ptrImplementationKeyword = takeToken(SyntaxKind::ImplementationKeyword);
    assert(ptrImplementationKeyword != nullptr);

    DelphiUsesClauseSyntax* ptrUses = parseUsesClause();
    assert(ptrUses != nullptr);

    auto ptrImplementationSection = std::make_unique<DelphiUnitImplementationSectionSyntax>(ptrImplementationKeyword);
    ptrImplementationSection->setUses(ptrUses);
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
    SyntaxToken* ptrUsesKeyword = takeToken(SyntaxKind::UsesKeyword);
    std::vector<DelphiUnitReferenceDeclarationSyntax*> unitReferences{};

    while (true)
    {
        if (currentToken()->syntaxKind() == SyntaxKind::SemiColonToken)
            break;

        DelphiUnitReferenceDeclarationSyntax* unitReference = parseUnitReference();
        unitReferences.push_back(unitReference);
    }

    SyntaxToken* ptrSemiColonToken = takeToken(SyntaxKind::SemiColonToken);

    auto ptrUsesClauseSyntax = std::make_unique<DelphiUsesClauseSyntax>(ptrUsesKeyword, std::move(unitReferences), ptrSemiColonToken);
    return static_cast<DelphiUsesClauseSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrUsesClauseSyntax)));
}

DelphiUnitReferenceDeclarationSyntax* DelphiParser::parseUnitReference() noexcept
{
    if (currentToken()->syntaxKind() != SyntaxKind::IdentifierToken)
        return nullptr; // TODO error handling

    NameExpressionSyntax* ptrUnitName = parseQualifiedName();
    assert(ptrUnitName != nullptr);

    auto unitReference = std::make_unique<DelphiUnitReferenceDeclarationSyntax>(ptrUnitName);
    auto ptrUnitReference = static_cast<DelphiUnitReferenceDeclarationSyntax*>(SyntaxPool::addSyntaxNode(std::move(unitReference)));

    if (currentToken()->syntaxKind() == SyntaxKind::InKeyword)
    {
        SyntaxToken* ptrInKeyword = takeToken(SyntaxKind::InKeyword);
        assert(ptrInKeyword != nullptr);

        SyntaxToken* ptrSourceFile = takeToken(SyntaxKind::SingleQuotationStringLiteralToken);
        assert(ptrSourceFile != nullptr);

        ptrUnitReference->setInKeyword(ptrInKeyword);
        ptrUnitReference->setSourceFile(ptrSourceFile);
    }

    if (currentToken()->syntaxKind() == SyntaxKind::CommaToken)
    {
        SyntaxToken* ptrCommaToken = takeToken(SyntaxKind::CommaToken);
        assert(ptrCommaToken != nullptr);
        ptrUnitReference->setCommaToken(ptrCommaToken);
    }

    return ptrUnitReference;
}

NameExpressionSyntax* DelphiParser::parseQualifiedName() noexcept
{
    NameExpressionSyntax* ptrName = parseIdentifierName();
    assert(ptrName != nullptr);

    while (currentToken()->syntaxKind() == SyntaxKind::DotToken)
    {
        SyntaxToken* separator = takeToken();
        ptrName = parseQualifiedNameRight(ptrName, separator);
    }

    return ptrName;
}

NameExpressionSyntax* DelphiParser::parseQualifiedNameRight(NameExpressionSyntax* left,
                                                            SyntaxToken* dotToken) noexcept
{
    assert(dotToken->syntaxKind() == SyntaxKind::DotToken);
    SimpleNameExpressionSyntax* ptrRight = parseIdentifierName();
    assert(ptrRight != nullptr);

    auto ptrNameExpression = std::make_unique<QualifiedNameExpressionSyntax>(left, dotToken, ptrRight);
    return static_cast<QualifiedNameExpressionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrNameExpression)));
}

IdentifierNameExpressionSyntax* DelphiParser::parseIdentifierName() noexcept
{
    SyntaxToken* ptrCurrentToken = currentToken();

    if (ptrCurrentToken->syntaxKind() == SyntaxKind::IdentifierToken)
    {
        SyntaxToken* identifier = takeToken();

        auto ptrIdentifierNameExpression = std::make_unique<IdentifierNameExpressionSyntax>(identifier);
        return static_cast<IdentifierNameExpressionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrIdentifierNameExpression)));
    }
    else
    {
        // TODO create missing token
        return nullptr;
    }
}

} // end namespace polyglot::CodeAnalysis
