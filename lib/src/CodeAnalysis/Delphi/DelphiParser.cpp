#include "polyglot/CodeAnalysis/Delphi/DelphiParser.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/QualifiedNameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/DelphiLexer.hpp"
#include <cassert>
#include <iostream>

namespace polyglot::CodeAnalysis
{

DelphiParser::DelphiParser(SharedPtr<SourceText> sourceText) noexcept
    : Parser{std::make_shared<DelphiLexer>(sourceText)},
      _ptrSyntaxFacts{std::make_shared<DelphiSyntaxFacts>()}
{}

SharedPtr<SyntaxNode> DelphiParser::parseRoot() noexcept
{
    if (_ptrSyntaxFacts->isModuleStart(currentToken()->syntaxKind()))
        return parseCompilationUnit();
    else
    {
        // TODO parse different entry points
        return nullptr;
    }
}

SharedPtr<DelphiCompilationUnitSyntax> DelphiParser::parseCompilationUnit() noexcept
{
    SharedPtr<SyntaxToken> ptrCurrentToken = currentToken();
    SharedPtr<DelphiCompilationUnitSyntax> ptrCompilationUnit = nullptr;

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

SharedPtr<DelphiUnitModuleSyntax> DelphiParser::parseUnitModule() noexcept
{
    SharedPtr<DelphiUnitHeadingSyntax> ptrHeading = nullptr;
    SharedPtr<DelphiUnitInterfaceSectionSyntax> ptrInterfaceSection = nullptr;
    SharedPtr<DelphiUnitImplementationSectionSyntax> ptrImplementationSection = nullptr;
    SharedPtr<DelphiUnitInitializationSectionSyntax> ptrInitializationSection = nullptr; // optional
    SharedPtr<DelphiUnitFinalizationSectionSyntax> ptrFinalizationSection = nullptr; // optional, but requires initialization section

    while (true)
    {
        SharedPtr<SyntaxToken> ptrCurrentToken = currentToken();

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
    SharedPtr<SyntaxToken> ptrEndKeyword = takeToken(SyntaxKind::EndKeyword);
    assert(ptrEndKeyword != nullptr);

    SharedPtr<SyntaxToken> ptrDotToken = takeToken(SyntaxKind::DotToken);
    assert(ptrDotToken != nullptr);

    SharedPtr<SyntaxToken> ptrEOFToken = takeToken(SyntaxKind::EndOfFileToken);
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

SharedPtr<DelphiUnitHeadingSyntax> DelphiParser::parseUnitHeading() noexcept
{
    SharedPtr<SyntaxToken> ptrUnitKeyword = takeToken(SyntaxKind::UnitKeyword);
    assert(ptrUnitKeyword != nullptr);

    SharedPtr<NameExpressionSyntax> ptrName = parseQualifiedName();
    assert(ptrName != nullptr);

    SharedPtr<SyntaxToken> ptrSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    assert(ptrSemiColonToken != nullptr);

    return std::make_shared<DelphiUnitHeadingSyntax>(std::move(ptrUnitKeyword), std::move(ptrName), std::move(ptrSemiColonToken));
}

SharedPtr<DelphiUnitInterfaceSectionSyntax> DelphiParser::parseUnitInterfaceSection() noexcept
{
    SharedPtr<SyntaxToken> ptrInterfaceKeyword = takeToken(SyntaxKind::InterfaceKeyword);
    assert(ptrInterfaceKeyword != nullptr);

    SharedPtr<DelphiUsesClauseSyntax> ptrUses = parseUsesClause();
    assert(ptrUses != nullptr);

    auto ptrInterfaceSection = std::make_shared<DelphiUnitInterfaceSectionSyntax>(std::move(ptrInterfaceKeyword));
    ptrInterfaceSection->setUses(std::move(ptrUses));

    return ptrInterfaceSection;
}

SharedPtr<DelphiUnitImplementationSectionSyntax> DelphiParser::parseUnitImplementationSection() noexcept
{
    SharedPtr<SyntaxToken> ptrImplementationKeyword = takeToken(SyntaxKind::ImplementationKeyword);
    assert(ptrImplementationKeyword != nullptr);

    SharedPtr<DelphiUsesClauseSyntax> ptrUses = parseUsesClause();
    assert(ptrUses != nullptr);

    auto ptrImplementationSection = std::make_shared<DelphiUnitImplementationSectionSyntax>(std::move(ptrImplementationKeyword));
    ptrImplementationSection->setUses(std::move(ptrUses));

    return ptrImplementationSection;
}

SharedPtr<DelphiUnitInitializationSectionSyntax> DelphiParser::parseUnitInitializationSection() noexcept
{
    return std::make_shared<DelphiUnitInitializationSectionSyntax>();
}

SharedPtr<DelphiUnitFinalizationSectionSyntax> DelphiParser::parseUnitFinalizationSection() noexcept
{
    return std::make_shared<DelphiUnitFinalizationSectionSyntax>();
}

SharedPtr<DelphiPackageModuleSyntax> DelphiParser::parsePackageModule() noexcept
{
    return std::make_shared<DelphiPackageModuleSyntax>();
}

SharedPtr<DelphiProgramModuleSyntax> DelphiParser::parseProgramModule() noexcept
{
    return std::make_shared<DelphiProgramModuleSyntax>();
}

SharedPtr<DelphiUsesClauseSyntax> DelphiParser::parseUsesClause() noexcept
{
    SharedPtr<SyntaxToken> ptrUsesKeyword = takeToken(SyntaxKind::UsesKeyword);
    std::vector<SharedPtr<DelphiUnitReferenceDeclarationSyntax>> unitReferences{};

    while (true)
    {
        if (currentToken()->syntaxKind() == SyntaxKind::SemiColonToken)
            break;

        SharedPtr<DelphiUnitReferenceDeclarationSyntax> unitReference = parseUnitReference();
        unitReferences.push_back(std::move(unitReference));
    }

    SharedPtr<SyntaxToken> ptrSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    return std::make_shared<DelphiUsesClauseSyntax>(std::move(ptrUsesKeyword), std::move(unitReferences), std::move(ptrSemiColonToken));
}

SharedPtr<DelphiUnitReferenceDeclarationSyntax> DelphiParser::parseUnitReference() noexcept
{
    if (currentToken()->syntaxKind() != SyntaxKind::IdentifierToken)
        return nullptr; // TODO error handling

    SharedPtr<NameExpressionSyntax> ptrUnitName = parseQualifiedName();
    assert(ptrUnitName != nullptr);

    auto ptrUnitReference = std::make_shared<DelphiUnitReferenceDeclarationSyntax>(std::move(ptrUnitName));

    if (currentToken()->syntaxKind() == SyntaxKind::InKeyword)
    {
        SharedPtr<SyntaxToken> ptrInKeyword = takeToken(SyntaxKind::InKeyword);
        assert(ptrInKeyword != nullptr);

        SharedPtr<SyntaxToken> ptrSourceFile = takeToken(SyntaxKind::SingleQuotationStringLiteralToken);
        assert(ptrSourceFile != nullptr);

        ptrUnitReference->setInKeyword(std::move(ptrInKeyword));
        ptrUnitReference->setSourceFile(std::move(ptrSourceFile));
    }

    if (currentToken()->syntaxKind() == SyntaxKind::CommaToken)
    {
        SharedPtr<SyntaxToken> ptrCommaToken = takeToken(SyntaxKind::CommaToken);
        assert(ptrCommaToken != nullptr);
        ptrUnitReference->setCommaToken(std::move(ptrCommaToken));
    }

    return ptrUnitReference;
}

SharedPtr<NameExpressionSyntax> DelphiParser::parseQualifiedName() noexcept
{
    SharedPtr<NameExpressionSyntax> ptrName = parseIdentifierName();
    assert(ptrName != nullptr);

    while (currentToken()->syntaxKind() == SyntaxKind::DotToken)
    {
        SharedPtr<SyntaxToken> separator = takeToken();
        ptrName = parseQualifiedNameRight(std::move(ptrName), std::move(separator));
    }

    return ptrName;
}

SharedPtr<NameExpressionSyntax> DelphiParser::parseQualifiedNameRight(SharedPtr<NameExpressionSyntax> left,
                                                                      SharedPtr<SyntaxToken> dotToken) noexcept
{
    assert(dotToken->syntaxKind() == SyntaxKind::DotToken);
    SharedPtr<SimpleNameExpressionSyntax> ptrRight = parseIdentifierName();
    assert(ptrRight != nullptr);
    return std::make_shared<QualifiedNameExpressionSyntax>(std::move(left), std::move(dotToken), std::move(ptrRight));
}

SharedPtr<IdentifierNameExpressionSyntax> DelphiParser::parseIdentifierName() noexcept
{
    SharedPtr<SyntaxToken> ptrCurrentToken = currentToken();

    if (ptrCurrentToken->syntaxKind() == SyntaxKind::IdentifierToken)
    {
        SharedPtr<SyntaxToken> identifier = takeToken();
        return std::make_shared<IdentifierNameExpressionSyntax>(std::move(identifier));
    }
    else
    {
        // TODO create missing token
        return nullptr;
    }
}

} // end namespace polyglot::CodeAnalysis
