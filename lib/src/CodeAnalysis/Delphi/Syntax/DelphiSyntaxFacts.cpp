#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxFacts.hpp"
#include <algorithm>
#include <unordered_map>

namespace polyglot::CodeAnalysis::DelphiSyntaxFacts
{

static const std::unordered_map<std::string, SyntaxKind> SYNTAXKEYWORDS =
{
    { "and", SyntaxKind::AndKeyword },
    { "array", SyntaxKind::ArrayKeyword },
    { "as", SyntaxKind::AsKeyword },
    { "asm", SyntaxKind::AsmKeyword },
    { "begin", SyntaxKind::BeginKeyword },
    { "case", SyntaxKind::CaseKeyword },
    { "class", SyntaxKind::ClassKeyword },
    { "const", SyntaxKind::ConstKeyword },
    { "constructor", SyntaxKind::ConstructorKeyword },
    { "destructor", SyntaxKind::DestructorKeyword },
    { "dispinterface", SyntaxKind::DispInterfaceKeyword },
    { "div", SyntaxKind::DivKeyword },
    { "do", SyntaxKind::DoKeyword },
    { "downto", SyntaxKind::DownToKeyword },
    { "else", SyntaxKind::ElseKeyword },
    { "end", SyntaxKind::EndKeyword },
    { "except", SyntaxKind::ExceptKeyword },
    { "exports", SyntaxKind::ExportsKeyword },
    { "file", SyntaxKind::FileKeyword },
    { "finalization", SyntaxKind::FinalizationKeyword },
    { "finally", SyntaxKind::FinallyKeyword },
    { "for", SyntaxKind::ForKeyword },
    { "function", SyntaxKind::FunctionKeyword },
    { "goto", SyntaxKind::GoToKeyword },
    { "else if", SyntaxKind::IfKeyword },
    { "implementation", SyntaxKind::ImplementationKeyword },
    { "in", SyntaxKind::InKeyword },
    { "inherited", SyntaxKind::InheritedKeyword },
    { "initialization", SyntaxKind::InitializationKeyword },
    { "inline", SyntaxKind::InlineKeyword },
    { "interface", SyntaxKind::InterfaceKeyword },
    { "is", SyntaxKind::IsKeyword },
    { "label", SyntaxKind::LabelKeyword },
    { "library", SyntaxKind::LibraryKeyword },
    { "mod", SyntaxKind::ModKeyword },
    { "nil", SyntaxKind::NilKeyword },
    { "not", SyntaxKind::NotKeyword },
    { "object", SyntaxKind::ObjectKeyword },
    { "of", SyntaxKind::OfKeyword },
    { "or", SyntaxKind::OrKeyword },
    { "packed", SyntaxKind::PackedKeyword },
    { "procedure", SyntaxKind::ProcedureKeyword },
    { "program", SyntaxKind::ProgramKeyword },
    { "property", SyntaxKind::PropertyKeyword },
    { "raise", SyntaxKind::RaiseKeyword },
    { "record", SyntaxKind::RecordKeyword },
    { "repeat", SyntaxKind::RepeatKeyword },
    { "resourcestring", SyntaxKind::ResourceStringKeyword },
    { "set", SyntaxKind::SetKeyword },
    { "shl", SyntaxKind::ShiftLeftKeyword },
    { "shr", SyntaxKind::ShiftRightKeyword },
    { "string", SyntaxKind::StringKeyword },
    { "then", SyntaxKind::ThenKeyword },
    { "threadvar", SyntaxKind::ThreadVarKeyword },
    { "to", SyntaxKind::ToKeyword },
    { "try", SyntaxKind::TryKeyword },
    { "type", SyntaxKind::TypeKeyword },
    { "unit", SyntaxKind::UnitKeyword },
    { "until", SyntaxKind::UntilKeyword },
    { "uses", SyntaxKind::UsesKeyword },
    { "var", SyntaxKind::VarKeyword },
    { "while", SyntaxKind::WhileKeyword },
    { "with", SyntaxKind::WithKeyword },
    { "xor", SyntaxKind::XorKeyword },
    { "absolute", SyntaxKind::AbsoluteKeyword },
    { "abstract", SyntaxKind::AbstractKeyword },
    { "assembler", SyntaxKind::AssemblerKeyword },
    { "automated", SyntaxKind::AutomatedKeyword },
    { "cdecl", SyntaxKind::CdeclKeyword },
    { "contains", SyntaxKind::ContainsKeyword },
    { "default", SyntaxKind::DefaultKeyword },
    { "delayed", SyntaxKind::DelayedKeyword },
    { "deprecated", SyntaxKind::DeprecatedKeyword },
    { "dispid", SyntaxKind::DispIdKeyword },
    { "dynamic", SyntaxKind::DynamicKeyword },
    { "experimental", SyntaxKind::ExperimentalKeyword },
    { "export", SyntaxKind::ExportKeyword },
    { "external", SyntaxKind::ExternalKeyword },
    { "far", SyntaxKind::FarKeyword },
    { "final", SyntaxKind::FinalKeyword },
    { "forward", SyntaxKind::ForwardKeyword },
    { "helper", SyntaxKind::HelperKeyword },
    { "implements", SyntaxKind::ImplementsKeyword },
    { "index", SyntaxKind::IndexKeyword },
    { "local", SyntaxKind::LocalKeyword },
    { "message", SyntaxKind::MessageKeyword },
    { "name", SyntaxKind::NameKeyword },
    { "near", SyntaxKind::NearKeyword },
    { "nodefault", SyntaxKind::NoDefaultKeyword },
    { "operator", SyntaxKind::OperatorKeyword },
    { "out", SyntaxKind::OutKeyword },
    { "overload", SyntaxKind::OverloadKeyword },
    { "override", SyntaxKind::OverrideKeyword },
    { "package", SyntaxKind::PackageKeyword },
    { "pascal", SyntaxKind::PascalKeyword },
    { "platform", SyntaxKind::PlatformKeyword },
    { "private", SyntaxKind::PrivateKeyword },
    { "protected", SyntaxKind::ProtectedKeyword },
    { "public", SyntaxKind::PublicKeyword },
    { "published", SyntaxKind::PublishedKeyword },
    { "read", SyntaxKind::ReadKeyword },
    { "readonly", SyntaxKind::ReadOnlyKeyword },
    { "reference", SyntaxKind::ReferenceKeyword },
    { "register", SyntaxKind::RegisterKeyword },
    { "reintroduce", SyntaxKind::ReintroduceKeyword },
    { "requires", SyntaxKind::RequiresKeyword },
    { "resident", SyntaxKind::ResidentKeyword },
    { "safecall", SyntaxKind::SafeCallKeyword },
    { "sealed", SyntaxKind::SealedKeyword },
    { "static", SyntaxKind::StaticKeyword },
    { "stdcall", SyntaxKind::StdCallKeyword },
    { "strict", SyntaxKind::StrictKeyword },
    { "stored", SyntaxKind::StoredKeyword },
    { "unsafe", SyntaxKind::UnsafeKeyword },
    { "varargs", SyntaxKind::VarArgsKeyword },
    { "virtual", SyntaxKind::VirtualKeyword },
    { "winapi", SyntaxKind::WinApiKeyword },
    { "write", SyntaxKind::WriteKeyword },
    { "writeonly", SyntaxKind::WriteOnlyKeyword },
    { "byte", SyntaxKind::ByteKeyword },
    { "shortint", SyntaxKind::ShortIntKeyword },
    { "word", SyntaxKind::WordKeyword },
    { "smallint", SyntaxKind::SmallIntKeyword },
    { "cardinal", SyntaxKind::CardinalKeyword },
    { "longword", SyntaxKind::LongWordKeyword },
    { "fixeduint", SyntaxKind::FixedUIntKeyword },
    { "integer", SyntaxKind::IntegerKeyword },
    { "longint", SyntaxKind::LongIntKeyword },
    { "fixedint", SyntaxKind::FixedIntKeyword },
    { "uint64", SyntaxKind::UInt64Keyword },
    { "int64", SyntaxKind::Int64Keyword },
    { "nativeuint", SyntaxKind::NativeUIntKeyword },
    { "nativeint", SyntaxKind::NativeIntKeyword },
    { "pbyte", SyntaxKind::BytePointerKeyword },
    { "pshortint", SyntaxKind::ShortIntPointerKeyword },
    { "pword", SyntaxKind::WordPointerKeyword },
    { "psmallint", SyntaxKind::SmallIntPointerKeyword },
    { "pcardinal", SyntaxKind::CardinalPointerKeyword },
    { "plongword", SyntaxKind::LongWordPointerKeyword },
    { "pfixeduint", SyntaxKind::FixedUIntPointerKeyword },
    { "pinteger", SyntaxKind::IntegerPointerKeyword },
    { "plongint", SyntaxKind::LongIntPointerKeyword },
    { "pfixedint", SyntaxKind::FixedIntPointerKeyword },
    { "puint64", SyntaxKind::UInt64PointerKeyword },
    { "pint64", SyntaxKind::Int64PointerKeyword },
    { "pnativeuint", SyntaxKind::NativeUIntPointerKeyword },
    { "pnativeint", SyntaxKind::NativeIntPointerKeyword },
    { "single", SyntaxKind::SingleKeyword },
    { "double", SyntaxKind::DoubleKeyword },
    { "extended", SyntaxKind::ExtendedKeyword },
    { "real", SyntaxKind::RealKeyword },
    { "psingle", SyntaxKind::SinglePointerKeyword },
    { "pdouble", SyntaxKind::DoublePointerKeyword },
    { "pextended", SyntaxKind::ExtendedPointerKeyword },
    { "ansichar", SyntaxKind::AnsiCharKeyword },
    { "char", SyntaxKind::CharKeyword },
    { "widechar", SyntaxKind::WideCharKeyword },
    { "ansistring", SyntaxKind::AnsiStringKeyword },
    { "rawbytestring", SyntaxKind::RawByteStringKeyword },
    { "unicodestring", SyntaxKind::UnicodeStringKeyword },
    { "shortstring", SyntaxKind::ShortStringKeyword },
    { "widestring", SyntaxKind::WideStringKeyword },
    { "pansichar", SyntaxKind::AnsiCharPointerKeyword },
    { "pchar", SyntaxKind::CharPointerKeyword },
    { "pwidechar", SyntaxKind::WideCharPointerKeyword },
    { "pansistring", SyntaxKind::AnsiStringPointerKeyword },
    { "prawbytestring", SyntaxKind::RawByteStringPointerKeyword },
    { "punicodestring", SyntaxKind::UnicodeStringPointerKeyword },
    { "pstring", SyntaxKind::StringPointerKeyword },
    { "pshortstring", SyntaxKind::ShortStringPointerKeyword },
    { "pwidestring", SyntaxKind::WideStringPointerKeyword },
    { "boolean", SyntaxKind::BooleanKeyword },
    { "bytebool", SyntaxKind::ByteBoolKeyword },
    { "wordbool", SyntaxKind::WordBoolKeyword },
    { "longbool", SyntaxKind::LongBoolKeyword },
    { "pboolean", SyntaxKind::BooleanPointerKeyword },
    { "pwordbool", SyntaxKind::WordBoolPointerKeyword },
    { "plongbool", SyntaxKind::LongBoolPointerKeyword },
    { "pointer", SyntaxKind::PointerKeyword },
    { "variant", SyntaxKind::VariantKeyword },
    { "currency", SyntaxKind::CurrencyKeyword },
    { "ppointer", SyntaxKind::PointerPointerKeyword },
    { "pvariant", SyntaxKind::VariantPointerKeyword },
    { "pcurrency", SyntaxKind::CurrencyPointerKeyword },
    { "real48", SyntaxKind::Real48Keyword },
    { "utf8string", SyntaxKind::UTF8StringKeyword },
    { "olevariant", SyntaxKind::OleVariantKeyword },
    { "polevariant", SyntaxKind::OleVariantPointerKeyword },
    { "add", SyntaxKind::AddKeyword },
    { "remove", SyntaxKind::RemoveKeyword },
    { "assembly", SyntaxKind::AssemblyKeyword },
    { "break", SyntaxKind::BreakKeyword },
    { "continue", SyntaxKind::ContinueKeyword }
};

bool isPunctuation(SyntaxKind syntaxKind) noexcept
{
    switch (syntaxKind)
    {
        case SyntaxKind::DotToken:
        case SyntaxKind::CommaToken:
        case SyntaxKind::SemiColonToken:
        case SyntaxKind::ColonToken:
        case SyntaxKind::EqualToken:
        case SyntaxKind::CaretToken:
        case SyntaxKind::LessThanToken:
        case SyntaxKind::GreaterThanToken:
        case SyntaxKind::OpenParenthesisToken:
        case SyntaxKind::CloseParenthesisToken:
        case SyntaxKind::OpenBracketToken:
        case SyntaxKind::CloseBracketToken:
        case SyntaxKind::OpenBraceToken:
        case SyntaxKind::CloseBraceToken:
        case SyntaxKind::AtToken:
        case SyntaxKind::PlusToken:
        case SyntaxKind::MinusToken:
        case SyntaxKind::AsteriskToken:
        case SyntaxKind::SlashToken:
        case SyntaxKind::AmpersandToken:
        case SyntaxKind::DollarToken:
        case SyntaxKind::UnderscoreToken:
        case SyntaxKind::HashToken:
        case SyntaxKind::SingleQuoteToken:
        case SyntaxKind::DoubleQuoteToken:
            return true;
    }

    return false;
}

bool isCompoundPunctuation(SyntaxKind syntaxKind) noexcept
{
    switch (syntaxKind)
    {
        case SyntaxKind::DotDotToken:
        case SyntaxKind::CaretDotToken:
        case SyntaxKind::ColonEqualToken:
        case SyntaxKind::SlashSlashToken:
        case SyntaxKind::LessThanEqualToken:
        case SyntaxKind::GreaterThanEqualToken:
        case SyntaxKind::LessThanGreaterThanToken:
        case SyntaxKind::MinusMinusToken:
        case SyntaxKind::OpenParenthesisAsteriskToken:
        case SyntaxKind::AsteriskCloseParenthesisToken:
        case SyntaxKind::OpenParenthesisDotToken:
        case SyntaxKind::DotCloseParenthesisToken:
        case SyntaxKind::OpenBraceDollerToken:
        case SyntaxKind::AtAtToken:
            return true;
    }

    return false;
}

bool isKeyword(SyntaxKind syntaxKind) noexcept
{
    switch (syntaxKind)
    {
        case SyntaxKind::AndKeyword:
        case SyntaxKind::ArrayKeyword:
        case SyntaxKind::AsKeyword:
        case SyntaxKind::AsmKeyword:
        case SyntaxKind::BeginKeyword:
        case SyntaxKind::CaseKeyword:
        case SyntaxKind::ClassKeyword:
        case SyntaxKind::ConstKeyword:
        case SyntaxKind::ConstructorKeyword:
        case SyntaxKind::DestructorKeyword:
        case SyntaxKind::DispInterfaceKeyword:
        case SyntaxKind::DivKeyword:
        case SyntaxKind::DoKeyword:
        case SyntaxKind::DownToKeyword:
        case SyntaxKind::ElseKeyword:
        case SyntaxKind::EndKeyword:
        case SyntaxKind::ExceptKeyword:
        case SyntaxKind::ExportsKeyword:
        case SyntaxKind::FileKeyword:
        case SyntaxKind::FinalizationKeyword:
        case SyntaxKind::FinallyKeyword:
        case SyntaxKind::ForKeyword:
        case SyntaxKind::FunctionKeyword:
        case SyntaxKind::GoToKeyword:
        case SyntaxKind::IfKeyword:
        case SyntaxKind::ImplementationKeyword:
        case SyntaxKind::InKeyword:
        case SyntaxKind::InheritedKeyword:
        case SyntaxKind::InitializationKeyword:
        case SyntaxKind::InlineKeyword:
        case SyntaxKind::InterfaceKeyword:
        case SyntaxKind::IsKeyword:
        case SyntaxKind::LabelKeyword:
        case SyntaxKind::LibraryKeyword:
        case SyntaxKind::ModKeyword:
        case SyntaxKind::NilKeyword:
        case SyntaxKind::NotKeyword:
        case SyntaxKind::ObjectKeyword:
        case SyntaxKind::OfKeyword:
        case SyntaxKind::OrKeyword:
        case SyntaxKind::PackedKeyword:
        case SyntaxKind::ProcedureKeyword:
        case SyntaxKind::ProgramKeyword:
        case SyntaxKind::PropertyKeyword:
        case SyntaxKind::RaiseKeyword:
        case SyntaxKind::RecordKeyword:
        case SyntaxKind::RepeatKeyword:
        case SyntaxKind::ResourceStringKeyword:
        case SyntaxKind::SetKeyword:
        case SyntaxKind::ShiftLeftKeyword:
        case SyntaxKind::ShiftRightKeyword:
        case SyntaxKind::StringKeyword:
        case SyntaxKind::ThenKeyword:
        case SyntaxKind::ThreadVarKeyword:
        case SyntaxKind::ToKeyword:
        case SyntaxKind::TryKeyword:
        case SyntaxKind::TypeKeyword:
        case SyntaxKind::UnitKeyword:
        case SyntaxKind::UntilKeyword:
        case SyntaxKind::UsesKeyword:
        case SyntaxKind::VarKeyword:
        case SyntaxKind::WhileKeyword:
        case SyntaxKind::WithKeyword:
        case SyntaxKind::XorKeyword:
        case SyntaxKind::AbsoluteKeyword:
        case SyntaxKind::AbstractKeyword:
        case SyntaxKind::AssemblerKeyword:
        case SyntaxKind::AutomatedKeyword:
        case SyntaxKind::CdeclKeyword:
        case SyntaxKind::ContainsKeyword:
        case SyntaxKind::DefaultKeyword:
        case SyntaxKind::DelayedKeyword:
        case SyntaxKind::DeprecatedKeyword:
        case SyntaxKind::DispIdKeyword:
        case SyntaxKind::DynamicKeyword:
        case SyntaxKind::ExperimentalKeyword:
        case SyntaxKind::ExportKeyword:
        case SyntaxKind::ExternalKeyword:
        case SyntaxKind::FarKeyword:
        case SyntaxKind::FinalKeyword:
        case SyntaxKind::ForwardKeyword:
        case SyntaxKind::HelperKeyword:
        case SyntaxKind::ImplementsKeyword:
        case SyntaxKind::IndexKeyword:
        case SyntaxKind::LocalKeyword:
        case SyntaxKind::MessageKeyword:
        case SyntaxKind::NameKeyword:
        case SyntaxKind::NearKeyword:
        case SyntaxKind::NoDefaultKeyword:
        case SyntaxKind::OperatorKeyword:
        case SyntaxKind::OutKeyword:
        case SyntaxKind::OverloadKeyword:
        case SyntaxKind::OverrideKeyword:
        case SyntaxKind::PackageKeyword:
        case SyntaxKind::PascalKeyword:
        case SyntaxKind::PlatformKeyword:
        case SyntaxKind::PrivateKeyword:
        case SyntaxKind::ProtectedKeyword:
        case SyntaxKind::PublicKeyword:
        case SyntaxKind::PublishedKeyword:
        case SyntaxKind::ReadKeyword:
        case SyntaxKind::ReadOnlyKeyword:
        case SyntaxKind::ReferenceKeyword:
        case SyntaxKind::RegisterKeyword:
        case SyntaxKind::ReintroduceKeyword:
        case SyntaxKind::RequiresKeyword:
        case SyntaxKind::ResidentKeyword:
        case SyntaxKind::SafeCallKeyword:
        case SyntaxKind::SealedKeyword:
        case SyntaxKind::StaticKeyword:
        case SyntaxKind::StdCallKeyword:
        case SyntaxKind::StrictKeyword:
        case SyntaxKind::StoredKeyword:
        case SyntaxKind::UnsafeKeyword:
        case SyntaxKind::VarArgsKeyword:
        case SyntaxKind::VirtualKeyword:
        case SyntaxKind::WinApiKeyword:
        case SyntaxKind::WriteKeyword:
        case SyntaxKind::WriteOnlyKeyword:
        case SyntaxKind::ByteKeyword:
        case SyntaxKind::ShortIntKeyword:
        case SyntaxKind::WordKeyword:
        case SyntaxKind::SmallIntKeyword:
        case SyntaxKind::CardinalKeyword:
        case SyntaxKind::LongWordKeyword:
        case SyntaxKind::FixedUIntKeyword:
        case SyntaxKind::IntegerKeyword:
        case SyntaxKind::LongIntKeyword:
        case SyntaxKind::FixedIntKeyword:
        case SyntaxKind::UInt64Keyword:
        case SyntaxKind::Int64Keyword:
        case SyntaxKind::NativeUIntKeyword:
        case SyntaxKind::NativeIntKeyword:
        case SyntaxKind::BytePointerKeyword:
        case SyntaxKind::ShortIntPointerKeyword:
        case SyntaxKind::WordPointerKeyword:
        case SyntaxKind::SmallIntPointerKeyword:
        case SyntaxKind::CardinalPointerKeyword:
        case SyntaxKind::LongWordPointerKeyword:
        case SyntaxKind::FixedUIntPointerKeyword:
        case SyntaxKind::IntegerPointerKeyword:
        case SyntaxKind::LongIntPointerKeyword:
        case SyntaxKind::FixedIntPointerKeyword:
        case SyntaxKind::UInt64PointerKeyword:
        case SyntaxKind::Int64PointerKeyword:
        case SyntaxKind::NativeUIntPointerKeyword:
        case SyntaxKind::NativeIntPointerKeyword:
        case SyntaxKind::SingleKeyword:
        case SyntaxKind::DoubleKeyword:
        case SyntaxKind::ExtendedKeyword:
        case SyntaxKind::RealKeyword:
        case SyntaxKind::SinglePointerKeyword:
        case SyntaxKind::DoublePointerKeyword:
        case SyntaxKind::ExtendedPointerKeyword:
        case SyntaxKind::AnsiCharKeyword:
        case SyntaxKind::CharKeyword:
        case SyntaxKind::WideCharKeyword:
        case SyntaxKind::AnsiStringKeyword:
        case SyntaxKind::RawByteStringKeyword:
        case SyntaxKind::UnicodeStringKeyword:
        case SyntaxKind::ShortStringKeyword:
        case SyntaxKind::WideStringKeyword:
        case SyntaxKind::AnsiCharPointerKeyword:
        case SyntaxKind::CharPointerKeyword:
        case SyntaxKind::WideCharPointerKeyword:
        case SyntaxKind::AnsiStringPointerKeyword:
        case SyntaxKind::RawByteStringPointerKeyword:
        case SyntaxKind::UnicodeStringPointerKeyword:
        case SyntaxKind::StringPointerKeyword:
        case SyntaxKind::ShortStringPointerKeyword:
        case SyntaxKind::WideStringPointerKeyword:
        case SyntaxKind::BooleanKeyword:
        case SyntaxKind::ByteBoolKeyword:
        case SyntaxKind::WordBoolKeyword:
        case SyntaxKind::LongBoolKeyword:
        case SyntaxKind::BooleanPointerKeyword:
        case SyntaxKind::WordBoolPointerKeyword:
        case SyntaxKind::LongBoolPointerKeyword:
        case SyntaxKind::PointerKeyword:
        case SyntaxKind::VariantKeyword:
        case SyntaxKind::CurrencyKeyword:
        case SyntaxKind::PointerPointerKeyword:
        case SyntaxKind::VariantPointerKeyword:
        case SyntaxKind::CurrencyPointerKeyword:
        case SyntaxKind::Real48Keyword:
        case SyntaxKind::UTF8StringKeyword:
        case SyntaxKind::OleVariantKeyword:
        case SyntaxKind::OleVariantPointerKeyword:
        case SyntaxKind::AddKeyword:
        case SyntaxKind::RemoveKeyword:
        case SyntaxKind::AssemblyKeyword:
        case SyntaxKind::BreakKeyword:
        case SyntaxKind::ContinueKeyword:
            return true;
    }

    return false;
}

SyntaxKind keywordKind(std::string_view text) noexcept
{
    std::string lowerCaseText{text};
    std::transform(std::begin(lowerCaseText), std::end(lowerCaseText), std::begin(lowerCaseText), std::tolower);

    if (SYNTAXKEYWORDS.find(lowerCaseText) != SYNTAXKEYWORDS.end())
        return SYNTAXKEYWORDS.at(lowerCaseText);

    return SyntaxKind::None;
}

} // end namespace polyglot::CodeAnalysis::DelphiSyntaxFacts
