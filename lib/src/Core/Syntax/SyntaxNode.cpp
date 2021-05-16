#include "Core/Syntax/SyntaxNode.hpp"
#include <sstream>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxToken.hpp"

namespace polyglot::Core::Syntax
{

SyntaxNode::SyntaxNode(SyntaxKind syntaxKind,
                       pg_size position,
                       pg_size fullWidth,
                       ISyntaxNode* parent,
                       ISyntaxTrivia* trivia) noexcept
    : ISyntaxNode{},
      _position{position},
      _fullWidth{fullWidth},
      _syntaxKind{syntaxKind},
      _flags{SyntaxFlags::None},
      _pParent{parent},
      _pTrivia{trivia},
      _pSyntaxTree{nullptr}
{}

std::string_view SyntaxNode::text() const noexcept
{
    if (_pParent != nullptr && _pParent->syntaxTree() != nullptr)
        return _pParent->syntaxTree()->sourceText()->toString(span());

    return _pSyntaxTree != nullptr ? _pSyntaxTree->sourceText()->toString(span()) : std::string_view{};
}

std::string_view SyntaxNode::textIncludingTrivia() const noexcept
{
    if (_pParent != nullptr && _pParent->syntaxTree() != nullptr)
        return _pParent->syntaxTree()->sourceText()->toString(fullSpan());

    return _pSyntaxTree != nullptr ? _pSyntaxTree->sourceText()->toString(fullSpan()) : std::string_view{};
}

pg_size SyntaxNode::leadingTriviaWidth() const noexcept
{
    ISyntaxToken* pFirstToken = firstToken();

    if (pFirstToken != nullptr)
        return pFirstToken->leadingTriviaWidth();

    return 0;
}

pg_size SyntaxNode::trailingTriviaWidth() const noexcept
{
    ISyntaxToken* pLastToken = lastToken();

    if (pLastToken != nullptr)
        return pLastToken->trailingTriviaWidth();

    return 0;
}

ISyntaxTriviaList* SyntaxNode::leadingTrivia() const noexcept
{
    ISyntaxToken* pFirstToken = firstToken();

    if (pFirstToken != nullptr)
        return pFirstToken->leadingTrivia();

    return nullptr;
}

ISyntaxTriviaList* SyntaxNode::trailingTrivia() const noexcept
{
    ISyntaxToken* pLastToken = lastToken();

    if (pLastToken != nullptr)
        return pLastToken->trailingTrivia();

    return nullptr;
}

bool SyntaxNode::hasMissingTokens() const noexcept
{
    ISyntaxNode* pNode = const_cast<SyntaxNode*>(this);

    for (pg_size i = 0, n = pNode->childCount(); i < n; i++)
    {
        SyntaxVariant nodeOrToken = pNode->child(i);

        if (nodeOrToken.isToken())
        {
            if (nodeOrToken.token->isMissing())
                return true;
        }
        else if (nodeOrToken.isNode())
        {
            if (nodeOrToken.node->hasMissingTokens())
                return true;
        }
    }

    return false;
}

void SyntaxNode::adjustWidthAndFlags(ISyntaxNode* node) noexcept
{
    if (node != nullptr)
    {
        SyntaxNode* pSyntaxNode = static_cast<SyntaxNode*>(node);
        _fullWidth += pSyntaxNode->_fullWidth;
        _flags |= pSyntaxNode->_flags;
        pSyntaxNode->_pParent = this;
    }
}

void SyntaxNode::adjustWidthAndFlags(ISyntaxToken* token) noexcept
{
    if (token != nullptr)
    {
        SyntaxToken* pSyntaxToken = static_cast<SyntaxToken*>(token);
        _fullWidth += pSyntaxToken->_fullWidth;
        pSyntaxToken->_pParent = this;
    }
}

void SyntaxNode::setTriviaParent(ISyntaxTrivia* trivia) noexcept
{
    _pParent = nullptr;
    _pTrivia = trivia;
}

void SyntaxNode::setSyntaxTree(ISyntaxTree* syntaxTree) noexcept
{
    _pSyntaxTree = syntaxTree;
}

std::string SyntaxNode::toString() const noexcept
{
    std::stringstream str;
    str << "Node(Position: " << _position << ", Kind: " << syntaxKindName(_syntaxKind) << ", Value: \"" << text() << "\"" << ", Width: " << width() << ")";
    return str.str();
}

std::string SyntaxNode::toShortString() const noexcept
{
    std::stringstream str;
    str << "Node: " << syntaxKindName(_syntaxKind) << fullSpan();
    return str.str();
}

} // end namespace polyglot::Core::Syntax
