#ifndef POLYGLOT_DELPHI_PARSER_PRECEDENCE_H
#define POLYGLOT_DELPHI_PARSER_PRECEDENCE_H

namespace polyglot::Delphi::Parser
{

enum class Precedence : unsigned char
{
    // lowest
    Expression = 0,
    Assignment = Expression,

    // fifth precedence
    Equality = 1,
    Relational = Equality,

    // fourth precedence
    Additive = 2,
    Subtractive = Additive,
    ConditionalOr = Subtractive,
    ConditionalXor = ConditionalOr,

    // third precedence
    Multiplicative = 3,
    ConditionalAnd = Multiplicative,
    Shift = ConditionalAnd,
    As = Shift,

    // second precedence
    Unary = 5,

    // first precedence (highest)
    Primary = 6
};

} // end namespace polyglot::Delphi::Parser

#endif // POLYGLOT_DELPHI_PARSER_PRECEDENCE_H
