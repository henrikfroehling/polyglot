#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXKIND_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXKIND_H

#include <string>
#include "polyglot/polyglot_global.hpp"

namespace polyglot::CodeAnalysis
{

enum class SyntaxKind : unsigned short
{
    // special tokens
    None = 0,
    BadToken,
    EndOfFileToken,
    WhitespaceToken,

    // punctuation
    DotToken = 50, // .
    CommaToken, // ,
    SemiColonToken, // ;
    ColonToken, // :
    EqualToken, // =
    CaretToken, // ^
    LessThanToken, // <
    GreaterThanToken, // >
    OpenParenthesisToken, // (
    CloseParenthesisToken, // )
    OpenBracketToken, // [
    CloseBracketToken, // ]
    OpenBraceToken, // {
    CloseBraceToken, // }
    AtToken, // @
    PlusToken, // +
    MinusToken, // -
    AsteriskToken, // *
    SlashToken, // /
    AmpersandToken, // &
    DollarToken, // $
    UnderscoreToken, // _
    HashToken, // #
    SingleQuoteToken, // '
    DoubleQuoteToken, // "

    // compound punctuation
    DotDotToken = 500, // ..
    CaretDotToken, // ^.
    ColonEqualToken, // :=
    SlashSlashToken, // //
    LessThanEqualToken, // <=
    GreaterThanEqualToken, // >=
    LessThanGreaterThanToken, // <>
    MinusMinusToken, // --
    OpenParenthesisAsteriskToken, // (*
    AsteriskCloseParenthesisToken, // *)
    OpenParenthesisDotToken, // (.
    DotCloseParenthesisToken, // .)
    OpenBraceDollerToken, // {$
    AtAtToken, // @@

    // keywords
    AndKeyword = 1000, // and
    ArrayKeyword, // array
    AsKeyword, // as
    AsmKeyword, // asm
    BeginKeyword, // begin
    CaseKeyword, // case
    ClassKeyword, // class
    ConstKeyword, // const
    ConstructorKeyword, // constructor
    DestructorKeyword, // destructor
    DispInterfaceKeyword, // dispinterface
    DivKeyword, // div
    DoKeyword, // do
    DownToKeyword, // downto
    ElseKeyword, // else
    EndKeyword, // end
    ExceptKeyword, // except
    ExportsKeyword, // exports
    FileKeyword, // file
    FinalizationKeyword, // finalization
    FinallyKeyword, // finally
    ForKeyword, // for
    FunctionKeyword, // function
    GoToKeyword, // goto
    IfKeyword, // if
    ImplementationKeyword, // implementation
    InKeyword, // in
    InheritedKeyword, // inherited
    InitializationKeyword, // initialization
    InlineKeyword, // inline
    InterfaceKeyword, // interface
    IsKeyword, // is
    LabelKeyword, // label
    LibraryKeyword, // library
    ModKeyword, // mod
    NilKeyword, // nil
    NotKeyword, // not
    ObjectKeyword, // object
    OfKeyword, // of
    OrKeyword, // or
    PackedKeyword, // packed
    ProcedureKeyword, // procedure
    ProgramKeyword, // program
    PropertyKeyword, // property
    RaiseKeyword, // raise
    RecordKeyword, // record
    RepeatKeyword, // repeat
    ResourceStringKeyword, // resourcestring
    SetKeyword, // set
    ShiftLeftKeyword, // shl
    ShiftRightKeyword, // shr
    StringKeyword, // string
    ThenKeyword, // then
    ThreadVarKeyword, // threadvar
    ToKeyword, // to
    TryKeyword, // try
    TypeKeyword, // type
    UnitKeyword, // unit
    UntilKeyword, // until
    UsesKeyword, // uses
    VarKeyword, // var
    WhileKeyword, // while
    WithKeyword, // with
    XorKeyword, // xor
    AbsoluteKeyword, // absolute
    AbstractKeyword, // abstract
    AssemblerKeyword, // assembler
    AutomatedKeyword, // automated
    CdeclKeyword, // cdecl
    ContainsKeyword, // contains
    DefaultKeyword, // default
    DelayedKeyword, // delayed
    DeprecatedKeyword, // deprecated
    DispIdKeyword, // dispid
    DynamicKeyword, // dynamic
    ExperimentalKeyword, // experimental
    ExportKeyword, // export
    ExternalKeyword, // external
    FarKeyword, // far
    FinalKeyword, // final
    ForwardKeyword, // forward
    HelperKeyword, // helper
    ImplementsKeyword, // implements
    IndexKeyword, // index
    LocalKeyword, // local
    MessageKeyword, // message
    NameKeyword, // name
    NearKeyword, // near
    NoDefaultKeyword, // nodefault
    OperatorKeyword, // operator
    OutKeyword, // out
    OverloadKeyword, // overload
    OverrideKeyword, // override
    PackageKeyword, // package
    PascalKeyword, // pascal
    PlatformKeyword, // platform
    PrivateKeyword, // private
    ProtectedKeyword, // protected
    PublicKeyword, // public
    PublishedKeyword, // published
    ReadKeyword, // read
    ReadOnlyKeyword, // readonly
    ReferenceKeyword, // reference
    RegisterKeyword, // register
    ReintroduceKeyword, // reintroduce
    RequiresKeyword, // requires
    ResidentKeyword, // resident
    SafeCallKeyword, // safecall
    SealedKeyword, // sealed
    StaticKeyword, // static
    StdCallKeyword, // stdcall
    StrictKeyword, // strict
    StoredKeyword, // stored
    UnsafeKeyword, // unsafe
    VarArgsKeyword, // varargs
    VirtualKeyword, // virtual
    WinApiKeyword, // winapi
    WriteKeyword, // write
    WriteOnlyKeyword, // writeonly
    ByteKeyword, // byte
    ShortIntKeyword, // shortint
    WordKeyword, // word
    SmallIntKeyword, // smallint
    CardinalKeyword, // cardinal
    LongWordKeyword, // longword
    FixedUIntKeyword, // fixeduint
    IntegerKeyword, // integer
    LongIntKeyword, // longint
    FixedIntKeyword, // fixedint
    UInt64Keyword, // uint64
    Int64Keyword, // int64
    NativeUIntKeyword, // nativeuint
    NativeIntKeyword, // nativeint
    BytePointerKeyword, // pbyte
    ShortIntPointerKeyword, // pshortint
    WordPointerKeyword, // pword
    SmallIntPointerKeyword, // psmallint
    CardinalPointerKeyword, // cardinal
    LongWordPointerKeyword, // plongword
    FixedUIntPointerKeyword, // pfixeduint
    IntegerPointerKeyword, // pinteger
    LongIntPointerKeyword, // plongint
    FixedIntPointerKeyword, // pfixedint
    UInt64PointerKeyword, // puint64
    Int64PointerKeyword, // pint64
    NativeUIntPointerKeyword, // pnativeuint
    NativeIntPointerKeyword, // pnativeint
    SingleKeyword, // single
    DoubleKeyword, // double,
    ExtendedKeyword, // extended
    RealKeyword, // real
    SinglePointerKeyword, // psingle
    DoublePointerKeyword, // pdouble
    ExtendedPointerKeyword, // pextended
    AnsiCharKeyword, // ansichar
    CharKeyword, // char
    WideCharKeyword, // widechar
    AnsiStringKeyword, // ansistring
    RawByteStringKeyword, // rawbytestring
    UnicodeStringKeyword, // unicodestring
    ShortStringKeyword, // shortstring
    WideStringKeyword, // widestring
    AnsiCharPointerKeyword, // pansichar
    CharPointerKeyword, // pchar
    WideCharPointerKeyword, // pwidechar
    AnsiStringPointerKeyword, // pansistring
    RawByteStringPointerKeyword, // prawbytestring
    UnicodeStringPointerKeyword, // punicodestring
    StringPointerKeyword, // pstring
    ShortStringPointerKeyword, // pshortstring
    WideStringPointerKeyword, // pwidestring
    BooleanKeyword, // boolean
    ByteBoolKeyword, // bytebool
    WordBoolKeyword, // wordbool
    LongBoolKeyword, // longbool
    BooleanPointerKeyword, // pboolean
    WordBoolPointerKeyword, // pwordbool
    LongBoolPointerKeyword, // plongbool
    PointerKeyword, // pointer
    VariantKeyword, // variant
    CurrencyKeyword, // currency
    PointerPointerKeyword, // ppointer
    VariantPointerKeyword, // pvariant
    CurrencyPointerKeyword, // pcurrency
    Real48Keyword, // real48
    UTF8StringKeyword, // utf8string
    OleVariantKeyword, // olevariant
    OleVariantPointerKeyword, // polevariant
    AddKeyword, // add
    RemoveKeyword, // remove
    AssemblyKeyword, // assembly
    BreakKeyword, // break
    ContinueKeyword, // continue

    // trivia
    WhitespaceTrivia = 2000,
    SingleLineCommentTrivia,
    MultiLineCommentTrivia,
    EndOfLineTrivia,

    StringLiteralToken = 2500,
    NumberLiteralToken,
    IdentifierToken
};

std::string POLYGLOT_API syntaxKindName(SyntaxKind syntaxKind) noexcept;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXKIND_H
