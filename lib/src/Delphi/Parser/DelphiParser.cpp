#include "Delphi/Parser/DelphiParser.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxList.hpp"
#include "polyglot/Core/Syntax/ISyntaxNode.hpp"
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "Core/Syntax/Expressions/IdentifierNameExpressionSyntax.hpp"
#include "Core/Syntax/Expressions/QualifiedNameExpressionSyntax.hpp"
#include "Delphi/Parser/DelphiLexer.hpp"
#include "Delphi/Parser/DelphiSyntaxFacts.hpp"
#include "Delphi/Syntax/DelphiAssemblerStatementSyntax.hpp"
#include "Delphi/Syntax/DelphiCaseStatementSyntax.hpp"
#include "Delphi/Syntax/DelphiCompoundStatementSyntax.hpp"
#include "Delphi/Syntax/DelphiEndOfModuleSyntax.hpp"
#include "Delphi/Syntax/DelphiForStatementSyntax.hpp"
#include "Delphi/Syntax/DelphiIfStatementSyntax.hpp"
#include "Delphi/Syntax/DelphiPackageModuleSyntax.hpp"
#include "Delphi/Syntax/DelphiProgramModuleSyntax.hpp"
#include "Delphi/Syntax/DelphiRaiseStatementSyntax.hpp"
#include "Delphi/Syntax/DelphiRepeatStatementSyntax.hpp"
#include "Delphi/Syntax/DelphiStatementListSyntax.hpp"
#include "Delphi/Syntax/DelphiStatementSyntax.hpp"
#include "Delphi/Syntax/DelphiTryStatementSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitFinalizationSectionSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitHeadSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitImplementationSectionSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitInitializationSectionSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitInterfaceSectionSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitModuleSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitReferenceDeclarationSyntax.hpp"
#include "Delphi/Syntax/DelphiUsesClauseSyntax.hpp"
#include "Delphi/Syntax/DelphiWhileStatementSyntax.hpp"
#include "Delphi/Syntax/DelphiWithStatementSyntax.hpp"

namespace polyglot::Delphi::Parser
{

using namespace Core::Syntax;
using namespace Delphi::Syntax;

DelphiParser::DelphiParser(SharedPtr<Core::Text::SourceText> sourceText) noexcept
    : Core::Parser::Parser{std::make_shared<DelphiLexer>(sourceText)},
      _syntaxFactory{_ptrLexer->syntaxPool()}
{}

ISyntaxNode* DelphiParser::parseRoot() noexcept
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
    ISyntaxToken* pCurrentToken = currentToken();
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
            ISyntaxToken* pEOFToken = takeToken(SyntaxKind::EndOfFileToken);
            pCompilationUnit = DelphiCompilationUnitSyntax::create(_syntaxFactory, SyntaxKind::CompilationUnit, pEOFToken);
        }
    }

    assert(pCompilationUnit != nullptr);
    return pCompilationUnit;
}

DelphiUnitModuleSyntax* DelphiParser::parseUnitModule() noexcept
{
    DelphiUnitHeadSyntax* pHead = nullptr;
    DelphiUnitInterfaceSectionSyntax* pInterfaceSection = nullptr;
    DelphiUnitImplementationSectionSyntax* pImplementationSection = nullptr;
    DelphiUnitInitializationSectionSyntax* pInitializationSection = nullptr; // optional
    DelphiUnitFinalizationSectionSyntax* pFinalizationSection = nullptr; // optional, but requires initialization section

    pHead = parseUnitHead();
    pInterfaceSection = parseUnitInterfaceSection();
    pImplementationSection = parseUnitImplementationSection();

    if (currentToken()->syntaxKind() == SyntaxKind::InitializationKeyword)
    {
        pInitializationSection = parseUnitInitializationSection();

        if (currentToken()->syntaxKind() == SyntaxKind::FinalizationKeyword)
            pFinalizationSection = parseUnitFinalizationSection();
    }

    DelphiEndOfModuleSyntax* endOfModule = parseEndOfModule();
    ISyntaxToken* pEOFToken = takeToken(SyntaxKind::EndOfFileToken);

    return DelphiUnitModuleSyntax::create(_syntaxFactory, pHead, pInterfaceSection, pImplementationSection,
                                          endOfModule, pEOFToken, pInitializationSection, pFinalizationSection);
}

DelphiUnitHeadSyntax* DelphiParser::parseUnitHead() noexcept
{
    ISyntaxToken* pUnitKeyword = takeToken(SyntaxKind::UnitKeyword);
    NameExpressionSyntax* pName = parseQualifiedName();
    ISyntaxToken* pInKeyword{nullptr};
    ISyntaxToken* pFilename{nullptr};

    if (peekToken(1)->syntaxKind() == SyntaxKind::InKeyword)
    {
        pInKeyword = takeToken();
        pFilename = takeToken(SyntaxKind::SingleQuotationStringLiteralToken);
    }

    ISyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    return DelphiUnitHeadSyntax::create(_syntaxFactory, pUnitKeyword, pName, pSemiColonToken, pInKeyword, pFilename);
}

DelphiUnitInterfaceSectionSyntax* DelphiParser::parseUnitInterfaceSection() noexcept
{
    ISyntaxToken* pInterfaceKeyword = takeToken(SyntaxKind::InterfaceKeyword);
    DelphiUsesClauseSyntax* pUses{nullptr};

    if (peekToken(1)->syntaxKind() == SyntaxKind::UsesKeyword)
        pUses = parseUsesClause();

    return DelphiUnitInterfaceSectionSyntax::create(_syntaxFactory, pInterfaceKeyword, pUses);
}

DelphiUnitImplementationSectionSyntax* DelphiParser::parseUnitImplementationSection() noexcept
{
    ISyntaxToken* pImplementationKeyword = takeToken(SyntaxKind::ImplementationKeyword);
    DelphiUsesClauseSyntax* pUses{nullptr};

    if (peekToken(1)->syntaxKind() == SyntaxKind::UsesKeyword)
        pUses = parseUsesClause();

    return DelphiUnitImplementationSectionSyntax::create(_syntaxFactory, pImplementationKeyword, pUses);
}

DelphiUnitInitializationSectionSyntax* DelphiParser::parseUnitInitializationSection() noexcept
{
    return DelphiUnitInitializationSectionSyntax::create(_syntaxFactory);
}

DelphiUnitFinalizationSectionSyntax* DelphiParser::parseUnitFinalizationSection() noexcept
{
    return DelphiUnitFinalizationSectionSyntax::create(_syntaxFactory);
}

DelphiPackageModuleSyntax* DelphiParser::parsePackageModule() noexcept
{
    return DelphiPackageModuleSyntax::create(_syntaxFactory);
}

DelphiProgramModuleSyntax* DelphiParser::parseProgramModule() noexcept
{
    return DelphiProgramModuleSyntax::create(_syntaxFactory);
}

DelphiUsesClauseSyntax* DelphiParser::parseUsesClause() noexcept
{
    ISyntaxToken* pUsesKeyword = takeToken(SyntaxKind::UsesKeyword);
    std::vector<SyntaxVariant> unitReferences;

    DelphiUnitReferenceDeclarationSyntax* pUnitReference = parseUnitReference();
    unitReferences.push_back(SyntaxVariant::asNode(pUnitReference));

    while (currentToken()->syntaxKind() == SyntaxKind::CommaToken)
    {
        ISyntaxToken* pCommaToken = takeToken();
        pUnitReference = parseUnitReference();
        unitReferences.push_back(SyntaxVariant::asToken(pCommaToken));
        unitReferences.push_back(SyntaxVariant::asNode(pUnitReference));
    }

    ISyntaxList* pUnitReferences = _syntaxFactory.syntaxList(SyntaxKind::UnitReferencesList, std::move(unitReferences));
    ISyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    return DelphiUsesClauseSyntax::create(_syntaxFactory, pUsesKeyword, pUnitReferences, pSemiColonToken);
}

DelphiUnitReferenceDeclarationSyntax* DelphiParser::parseUnitReference() noexcept
{
    if (currentToken()->syntaxKind() != SyntaxKind::IdentifierToken)
        return nullptr; // TODO error handling

    NameExpressionSyntax* pUnitName = parseQualifiedName();
    ISyntaxToken* pInKeyword{nullptr};
    ISyntaxToken* pSourceFile{nullptr};

    if (currentToken()->syntaxKind() == SyntaxKind::InKeyword)
    {
        pInKeyword = takeToken(SyntaxKind::InKeyword);
        pSourceFile = takeToken(SyntaxKind::SingleQuotationStringLiteralToken);
    }

    return DelphiUnitReferenceDeclarationSyntax::create(_syntaxFactory, pUnitName, pInKeyword, pSourceFile);
}

NameExpressionSyntax* DelphiParser::parseQualifiedName() noexcept
{
    NameExpressionSyntax* pName = parseIdentifierName();

    while (currentToken()->syntaxKind() == SyntaxKind::DotToken)
    {
        ISyntaxToken* pSeparator = takeToken();
        pName = parseQualifiedNameRight(pName, pSeparator);
    }

    return pName;
}

NameExpressionSyntax* DelphiParser::parseQualifiedNameRight(NameExpressionSyntax* left,
                                                            ISyntaxToken* dotToken) noexcept
{
    assert(dotToken != nullptr);
    assert(dotToken->syntaxKind() == SyntaxKind::DotToken);
    SimpleNameExpressionSyntax* pRight = parseIdentifierName();
    return QualifiedNameExpressionSyntax::create(_syntaxFactory, left, dotToken, pRight);
}

IdentifierNameExpressionSyntax* DelphiParser::parseIdentifierName() noexcept
{
    ISyntaxToken* pCurrentToken = currentToken();

    if (pCurrentToken->syntaxKind() == SyntaxKind::IdentifierToken)
    {
        ISyntaxToken* pIdentifier = takeToken();
        return IdentifierNameExpressionSyntax::create(_syntaxFactory, pIdentifier);
    }
    else
    {
        ISyntaxToken* pMissingIdentifier = _syntaxFactory.missingToken(SyntaxKind::IdentifierToken, pCurrentToken->text(), pCurrentToken->position());
        return IdentifierNameExpressionSyntax::create(_syntaxFactory, pMissingIdentifier);
    }
}

DelphiEndOfModuleSyntax* DelphiParser::parseEndOfModule() noexcept
{
    ISyntaxToken* pEndKeyword = takeToken(SyntaxKind::EndKeyword);
    ISyntaxToken* pDotToken = takeToken(SyntaxKind::DotToken);
    return DelphiEndOfModuleSyntax::create(_syntaxFactory, pEndKeyword, pDotToken);
}

DelphiCompoundStatementSyntax* DelphiParser::parseCompoundStatement() noexcept
{
    ISyntaxToken* pBeginToken = takeToken(SyntaxKind::BeginKeyword);
    DelphiStatementListSyntax* pStatementList = parseStatementList();
    ISyntaxToken* pEndToken = takeToken(SyntaxKind::EndKeyword);
    return DelphiCompoundStatementSyntax::create(_syntaxFactory, pBeginToken, pStatementList, pEndToken);
}

DelphiStatementListSyntax* DelphiParser::parseStatementList() noexcept
{
    std::vector<SyntaxVariant> statements{};
    DelphiStatementSyntax* pStatement = parseStatement();
    assert(pStatement != nullptr);
    statements.push_back(SyntaxVariant::asNode(pStatement));

    while (DelphiSyntaxFacts::isStatementStart(currentToken()->syntaxKind()))
    {
        pStatement = parseStatement();
        assert(pStatement != nullptr);
        statements.push_back(SyntaxVariant::asNode(pStatement));

        if (DelphiSyntaxFacts::isStatementStart(peekToken(1)->syntaxKind()))
        {
            // if there is another statement following, a semicolon is required, otherwise it's optional
            ISyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
            statements.push_back(SyntaxVariant::asToken(pSemiColonToken));
        }
        else if (currentToken()->syntaxKind() == SyntaxKind::SemiColonToken)
        {
            // take semicolon, if there's one
            statements.push_back(SyntaxVariant::asToken(takeToken()));
        }
    }

    return DelphiStatementListSyntax::create(_syntaxFactory, std::move(statements));
}

DelphiStatementSyntax* DelphiParser::parseStatement() noexcept
{
    // statement => [identifier | int num literal | hex num literal ':'],
    //              If Statement | Case Statement | Repeat Statement | While Statement | For Statement | With Statement
    //              | Try Statement | Raise Statement | Assembler Statement | Compound Statement | Simple Statement

    SyntaxKind currentSyntaxKind = currentToken()->syntaxKind();

    // Structured Statements
    switch (currentSyntaxKind)
    {
        case SyntaxKind::IfKeyword:
            return parseIfStatement();
        case SyntaxKind::CaseKeyword:
            return parseCaseStatement();
        case SyntaxKind::RepeatKeyword:
            return parseRepeatStatement();
        case SyntaxKind::WhileKeyword:
            return parseWhileStatement();
        case SyntaxKind::ForKeyword:
            return parseForStatement();
        case SyntaxKind::WithKeyword:
            return parseWithStatement();
        case SyntaxKind::TryKeyword:
            return parseTryStatement();
        case SyntaxKind::RaiseKeyword:
            return parseRaiseStatement();
        case SyntaxKind::AssemblerKeyword:
            return parseAssemblerStatement();
        case SyntaxKind::BeginKeyword:
            return parseCompoundStatement();
    }

    // Simple Statement
    return nullptr;
}

DelphiIfStatementSyntax* DelphiParser::parseIfStatement() noexcept
{
    return nullptr;
}

DelphiCaseStatementSyntax* DelphiParser::parseCaseStatement() noexcept
{
    return nullptr;
}

DelphiRepeatStatementSyntax* DelphiParser::parseRepeatStatement() noexcept
{
    return nullptr;
}

DelphiWhileStatementSyntax* DelphiParser::parseWhileStatement() noexcept
{
    return nullptr;
}

DelphiForStatementSyntax* DelphiParser::parseForStatement() noexcept
{
    return nullptr;
}

DelphiWithStatementSyntax* DelphiParser::parseWithStatement() noexcept
{
    return nullptr;
}

DelphiTryStatementSyntax* DelphiParser::parseTryStatement() noexcept
{
    return nullptr;
}

DelphiRaiseStatementSyntax* DelphiParser::parseRaiseStatement() noexcept
{
    return nullptr;
}

DelphiAssemblerStatementSyntax* DelphiParser::parseAssemblerStatement() noexcept
{
    return nullptr;
}

} // end namespace polyglot::Delphi::Parser
