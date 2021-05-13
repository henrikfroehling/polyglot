#ifndef POLYGLOT_CORE_SYNTAX_SYNTAXNODEFLAGS_H
#define POLYGLOT_CORE_SYNTAX_SYNTAXNODEFLAGS_H

#include <type_traits>

namespace polyglot::Core::Syntax
{

enum class SyntaxFlags : unsigned char
{
    None = 0,
    ContainsTrivia = 1 << 0,
    ContainsStructuredTrivia = 1 << 1,
    ContainsSkippedText = 1 << 2,
    ContainsDirectives = 1 << 3,
    IsMissing = 1 << 4
};

inline SyntaxFlags operator|(SyntaxFlags lhs,
                             SyntaxFlags rhs)
{
    return static_cast<SyntaxFlags>(
        static_cast<std::underlying_type_t<SyntaxFlags>>(lhs)
        | static_cast<std::underlying_type_t<SyntaxFlags>>(rhs));
}

inline SyntaxFlags operator&(SyntaxFlags lhs,
                             SyntaxFlags rhs)
{
    return static_cast<SyntaxFlags>(
        static_cast<std::underlying_type_t<SyntaxFlags>>(lhs)
        & static_cast<std::underlying_type_t<SyntaxFlags>>(rhs));
}

inline SyntaxFlags operator^(SyntaxFlags lhs,
                             SyntaxFlags rhs)
{
    return static_cast<SyntaxFlags>(
        static_cast<std::underlying_type_t<SyntaxFlags>>(lhs)
        ^ static_cast<std::underlying_type_t<SyntaxFlags>>(rhs));
}

inline SyntaxFlags operator~(SyntaxFlags flags)
{
    return static_cast<SyntaxFlags>(~static_cast<std::underlying_type_t<SyntaxFlags>>(flags));
}

inline SyntaxFlags& operator|=(SyntaxFlags& lhs,
                               SyntaxFlags rhs)
{
    lhs = static_cast<SyntaxFlags>(
        static_cast<std::underlying_type_t<SyntaxFlags>>(lhs)
        | static_cast<std::underlying_type_t<SyntaxFlags>>(rhs));

    return lhs;
}

inline SyntaxFlags& operator&=(SyntaxFlags& lhs,
                               SyntaxFlags rhs)
{
    lhs = static_cast<SyntaxFlags>(
        static_cast<std::underlying_type_t<SyntaxFlags>>(lhs)
        & static_cast<std::underlying_type_t<SyntaxFlags>>(rhs));

    return lhs;
}

inline SyntaxFlags& operator^=(SyntaxFlags& lhs,
                               SyntaxFlags rhs)
{
    lhs = static_cast<SyntaxFlags>(
        static_cast<std::underlying_type_t<SyntaxFlags>>(lhs)
        ^ static_cast<std::underlying_type_t<SyntaxFlags>>(rhs));

    return lhs;
}

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_SYNTAXNODEFLAGS_H
