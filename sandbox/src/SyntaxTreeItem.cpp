#include "SyntaxTreeItem.hpp"
#include <QtCore/QString>
#include <polyglot/Core/Syntax/ISyntaxList.hpp>
#include <polyglot/Core/Syntax/ISyntaxNode.hpp>
#include <polyglot/Core/Syntax/ISyntaxToken.hpp>
#include <polyglot/Core/Syntax/ISyntaxTrivia.hpp>
#include <polyglot/Core/Syntax/ISyntaxTriviaList.hpp>

namespace models
{

using namespace polyglot::Core::Syntax;

SyntaxTreeItem::SyntaxTreeItem() noexcept
    : _children{},
      _value{SyntaxVariant::empty()},
      _row{},
      _pParentItem{nullptr}
{}

SyntaxTreeItem::SyntaxTreeItem(SyntaxVariant value,
                               SyntaxTreeItem* parent) noexcept
    : _children{},
      _value{std::move(value)},
      _row{},
      _pParentItem{parent}
{}

SyntaxTreeItem* SyntaxTreeItem::child(int row) const noexcept
{
    if (row >= 0 && row < _children.size())
        return _children[row].get();

    return nullptr;
}

QVariant SyntaxTreeItem::data() const noexcept
{
    if (_value.isEmpty())
        return QVariant{};

    if (_value.isNode())
        return QString::fromStdString(_value.node->toShortString());
    else if (_value.isToken())
        return QString::fromStdString(_value.token->toShortString());
    else if (_value.isList())
        return QString::fromStdString(_value.list->toShortString());
    else if (_value.isTrivia())
        return QString::fromStdString(_value.trivia->toShortString());

    return QVariant{};
}

void SyntaxTreeItem::add(SyntaxVariant value) noexcept
{
    std::unique_ptr<SyntaxTreeItem> item = std::make_unique<SyntaxTreeItem>(value, this);

    if (value.isNode())
    {
        for (int i = 0; i < value.node->childCount(); i++)
            item->add(value.node->child(i));

        _children.push_back(std::move(item));
        _children.back().get()->setRow(_children.size() - 1);
    }
    else if (value.isToken())
    {
        if (value.token->hasLeadingTrivia())
        {
            for (int i = 0; i < value.token->leadingTrivia()->count(); i++)
                item->add(SyntaxVariant::asTrivia(value.token->leadingTrivia()->child(i)));
        }

        if (value.token->hasTrailingTrivia())
        {
            for (int i = 0; i < value.token->trailingTrivia()->count(); i++)
                item->add(SyntaxVariant::asTrivia(value.token->trailingTrivia()->child(i)));
        }

        _children.push_back(std::move(item));
        _children.back().get()->setRow(_children.size() - 1);
    }
    else if (value.isList())
    {
        for (int i = 0; i < value.list->childCount(); i++)
            item->add(value.list->child(i));

        _children.push_back(std::move(item));
        _children.back().get()->setRow(_children.size() - 1);
    }
    else if (value.isTrivia())
    {
        _children.push_back(std::move(item));
        _children.back().get()->setRow(_children.size() - 1);
    }
}

void SyntaxTreeItem::clear() noexcept
{
    _children.clear();
    _value = SyntaxVariant::empty();
    _row = 0;
    _pParentItem = nullptr;
}

} // end namespace models
