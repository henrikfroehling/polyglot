#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODEFLAGS_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODEFLAGS_H

#include <type_traits>

namespace polyglot::CodeAnalysis
{

enum class SyntaxNodeFlags : unsigned char
{
    None = 0,
    ContainsTrivia = 1 << 0,
    ContainsStructuredTrivia = 1 << 1,
    ContainsSkippedText = 1 << 2,
    ContainsDirectives = 1 << 3,
    IsMissing = 1 << 4
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

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODEFLAGS_H
