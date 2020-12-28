#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODEFLAGS_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODEFLAGS_H

#include <type_traits>

namespace polyglot::CodeAnalysis::_impl
{

enum class SyntaxNodeFlags : unsigned char
{
    None = 0,
    ContainsTrivia = 1 << 0,
    ContainsDirectives = 1 << 1
};

inline SyntaxNodeFlags operator|(SyntaxNodeFlags lhs,
                                 SyntaxNodeFlags rhs)
{
    return static_cast<SyntaxNodeFlags>(
        static_cast<std::underlying_type_t<SyntaxNodeFlags>>(lhs)
        | static_cast<std::underlying_type_t<SyntaxNodeFlags>>(rhs));
}

inline SyntaxNodeFlags operator&(SyntaxNodeFlags lhs,
                                 SyntaxNodeFlags rhs)
{
    return static_cast<SyntaxNodeFlags>(
        static_cast<std::underlying_type_t<SyntaxNodeFlags>>(lhs)
        & static_cast<std::underlying_type_t<SyntaxNodeFlags>>(rhs));
}

inline SyntaxNodeFlags operator^(SyntaxNodeFlags lhs,
                                 SyntaxNodeFlags rhs)
{
    return static_cast<SyntaxNodeFlags>(
        static_cast<std::underlying_type_t<SyntaxNodeFlags>>(lhs)
        ^ static_cast<std::underlying_type_t<SyntaxNodeFlags>>(rhs));
}

inline SyntaxNodeFlags operator~(SyntaxNodeFlags flags)
{
    return static_cast<SyntaxNodeFlags>(~static_cast<std::underlying_type_t<SyntaxNodeFlags>>(flags));
}

inline SyntaxNodeFlags& operator|=(SyntaxNodeFlags& lhs,
                                   SyntaxNodeFlags rhs)
{
    lhs = static_cast<SyntaxNodeFlags>(
        static_cast<std::underlying_type_t<SyntaxNodeFlags>>(lhs)
        | static_cast<std::underlying_type_t<SyntaxNodeFlags>>(rhs));

    return lhs;
}

inline SyntaxNodeFlags& operator&=(SyntaxNodeFlags& lhs,
                                   SyntaxNodeFlags rhs)
{
    lhs = static_cast<SyntaxNodeFlags>(
        static_cast<std::underlying_type_t<SyntaxNodeFlags>>(lhs)
        & static_cast<std::underlying_type_t<SyntaxNodeFlags>>(rhs));

    return lhs;
}

inline SyntaxNodeFlags& operator^=(SyntaxNodeFlags& lhs,
                                   SyntaxNodeFlags rhs)
{
    lhs = static_cast<SyntaxNodeFlags>(
        static_cast<std::underlying_type_t<SyntaxNodeFlags>>(lhs)
        ^ static_cast<std::underlying_type_t<SyntaxNodeFlags>>(rhs));

    return lhs;
}

} // end namespace polyglot::CodeAnalysis::_impl

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODEFLAGS_H
