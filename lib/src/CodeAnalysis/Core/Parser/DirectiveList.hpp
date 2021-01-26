#ifndef POLYGLOT_CODEANALYSIS_CORE_PARSER_DIRECTIVELIST_H
#define POLYGLOT_CODEANALYSIS_CORE_PARSER_DIRECTIVELIST_H

#include "polyglot/Core/Types.hpp"

namespace polyglot::CodeAnalysis
{

class Directive;

class DirectiveList : public std::enable_shared_from_this<DirectiveList>
{
public:
    DirectiveList() noexcept;

    explicit DirectiveList(SharedPtr<Directive> head,
                           SharedPtr<DirectiveList> tail) noexcept;

    inline const SharedPtr<Directive>& head() const noexcept { return _ptrHead; }
    inline const SharedPtr<DirectiveList>& tail() const noexcept { return _ptrTail; }
    inline SharedPtr<DirectiveList> push(SharedPtr<Directive> value) noexcept { return std::make_shared<DirectiveList>(std::move(value), shared_from_this()); }
    bool any() const noexcept;
    static SharedPtr<DirectiveList> empty() noexcept;

    static SharedPtr<DirectiveList> create(SharedPtr<Directive> directive,
                                           SharedPtr<DirectiveList> tail) noexcept;

    friend bool operator==(const DirectiveList& lhs,
                           const DirectiveList& rhs) noexcept;

    friend bool operator!=(const DirectiveList& lhs,
                           const DirectiveList& rhs) noexcept;

private:
    SharedPtr<Directive> _ptrHead;
    SharedPtr<DirectiveList> _ptrTail;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_PARSER_DIRECTIVELIST_H
