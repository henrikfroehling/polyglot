#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

std::string syntaxKindName(SyntaxKind syntaxKind) noexcept
{
    switch (syntaxKind)
    {
        // special tokens
        case SyntaxKind::None: return "None";
        case SyntaxKind::BadToken: return "BadToken";
        case SyntaxKind::EndOfFileToken: return "EndOfFileToken";
        case SyntaxKind::WhitespaceToken: return "WhitespaceToken";

        // punctuation
        case SyntaxKind::DotToken: return "DotToken";
        case SyntaxKind::CommaToken: return "CommaToken";
        case SyntaxKind::SemiColonToken: return "SemiColonToken";
        case SyntaxKind::ColonToken: return "ColonToken";
        case SyntaxKind::EqualToken: return "EqualToken";
        case SyntaxKind::CaretToken: return "CaretToken";
        case SyntaxKind::LessThanToken: return "LessThanToken";
        case SyntaxKind::GreaterThanToken: return "GreaterThanToken";
        case SyntaxKind::OpenParenthesisToken: return "OpenParenthesisToken";
        case SyntaxKind::CloseParenthesisToken: return "CloseParenthesisToken";
        case SyntaxKind::OpenBracketToken: return "OpenBracketToken";
        case SyntaxKind::CloseBracketToken: return "CloseBracketToken";
        case SyntaxKind::OpenBraceToken: return "OpenBraceToken";
        case SyntaxKind::CloseBraceToken: return "CloseBraceToken";
        case SyntaxKind::AtToken: return "AtToken";
        case SyntaxKind::PlusToken: return "PlusToken";
        case SyntaxKind::MinusToken: return "MinusToken";
        case SyntaxKind::AsteriskToken: return "AsteriskToken";
        case SyntaxKind::SlashToken: return "SlashToken";
        case SyntaxKind::AmpersandToken: return "AmpersandToken";
        case SyntaxKind::DollarToken: return "DollarToken";
        case SyntaxKind::UnderscoreToken: return "UnderscoreToken";
        case SyntaxKind::HashToken: return "HashToken";
        case SyntaxKind::SingleQuoteToken: return "SingleQuoteToken";
        case SyntaxKind::DoubleQuoteToken: return "DoubleQuoteToken";
        case SyntaxKind::ExclamationMarkToken: return "ExclamationMarkToken";

        // compound punctuation
        case SyntaxKind::DotDotToken: return "DotDotToken";
        case SyntaxKind::CaretDotToken: return "CaretDotToken";
        case SyntaxKind::ColonEqualToken: return "ColonEqualToken";
        case SyntaxKind::SlashSlashToken: return "SlashSlashToken";
        case SyntaxKind::LessThanEqualToken: return "LessThanEqualToken";
        case SyntaxKind::GreaterThanEqualToken: return "GreaterThanEqualToken";
        case SyntaxKind::LessThanGreaterThanToken: return "LessThanGreaterThanToken";
        case SyntaxKind::MinusMinusToken: return "MinusMinusToken";
        case SyntaxKind::OpenParenthesisAsteriskToken: return "OpenParenthesisAsteriskToken";
        case SyntaxKind::AsteriskCloseParenthesisToken: return "AsteriskCloseParenthesisToken";
        case SyntaxKind::OpenParenthesisDotToken: return "OpenParenthesisDotToken";
        case SyntaxKind::DotCloseParenthesisToken: return "DotCloseParenthesisToken";
        case SyntaxKind::OpenBraceDollarToken: return "OpenBraceDollarToken";
        case SyntaxKind::OpenParenthesisDollarToken: return "OpenParenthesisDollarToken";
        case SyntaxKind::AtAtToken: return "AtAtToken";

        // keywords
        case SyntaxKind::AndKeyword: return "AndKeyword";
        case SyntaxKind::ArrayKeyword: return "ArrayKeyword";
        case SyntaxKind::AsKeyword: return "AsKeyword";
        case SyntaxKind::AsmKeyword: return "AsmKeyword";
        case SyntaxKind::BeginKeyword: return "BeginKeyword";
        case SyntaxKind::CaseKeyword: return "CaseKeyword";
        case SyntaxKind::ClassKeyword: return "ClassKeyword";
        case SyntaxKind::ConstKeyword: return "ConstKeyword";
        case SyntaxKind::ConstructorKeyword: return "ConstructorKeyword";
        case SyntaxKind::DestructorKeyword: return "DestructorKeyword";
        case SyntaxKind::DispInterfaceKeyword: return "DispInterfaceKeyword";
        case SyntaxKind::DivKeyword: return "DivKeyword";
        case SyntaxKind::DoKeyword: return "DoKeyword";
        case SyntaxKind::DownToKeyword: return "DownToKeyword";
        case SyntaxKind::ElseKeyword: return "ElseKeyword";
        case SyntaxKind::EndKeyword: return "EndKeyword";
        case SyntaxKind::ExceptKeyword: return "ExceptKeyword";
        case SyntaxKind::ExportsKeyword: return "ExportsKeyword";
        case SyntaxKind::FileKeyword: return "FileKeyword";
        case SyntaxKind::FinalizationKeyword: return "FinalizationKeyword";
        case SyntaxKind::FinallyKeyword: return "FinallyKeyword";
        case SyntaxKind::ForKeyword: return "ForKeyword";
        case SyntaxKind::FunctionKeyword: return "FunctionKeyword";
        case SyntaxKind::GoToKeyword: return "GoToKeyword";
        case SyntaxKind::IfKeyword: return "IfKeyword";
        case SyntaxKind::ImplementationKeyword: return "ImplementationKeyword";
        case SyntaxKind::InKeyword: return "InKeyword";
        case SyntaxKind::InheritedKeyword: return "InheritedKeyword";
        case SyntaxKind::InitializationKeyword: return "InitializationKeyword";
        case SyntaxKind::InlineKeyword: return "InlineKeyword";
        case SyntaxKind::InterfaceKeyword: return "InterfaceKeyword";
        case SyntaxKind::IsKeyword: return "IsKeyword";
        case SyntaxKind::LabelKeyword: return "LabelKeyword";
        case SyntaxKind::LibraryKeyword: return "LibraryKeyword";
        case SyntaxKind::ModKeyword: return "ModKeyword";
        case SyntaxKind::NilKeyword: return "NilKeyword";
        case SyntaxKind::NotKeyword: return "NotKeyword";
        case SyntaxKind::ObjectKeyword: return "ObjectKeyword";
        case SyntaxKind::OfKeyword: return "OfKeyword";
        case SyntaxKind::OrKeyword: return "OrKeyword";
        case SyntaxKind::PackedKeyword: return "PackedKeyword";
        case SyntaxKind::ProcedureKeyword: return "ProcedureKeyword";
        case SyntaxKind::ProgramKeyword: return "ProgramKeyword";
        case SyntaxKind::PropertyKeyword: return "PropertyKeyword";
        case SyntaxKind::RaiseKeyword: return "RaiseKeyword";
        case SyntaxKind::RecordKeyword: return "RecordKeyword";
        case SyntaxKind::RepeatKeyword: return "RepeatKeyword";
        case SyntaxKind::ResourceStringKeyword: return "ResourceStringKeyword";
        case SyntaxKind::SetKeyword: return "SetKeyword";
        case SyntaxKind::ShiftLeftKeyword: return "ShiftLeftKeyword";
        case SyntaxKind::ShiftRightKeyword: return "ShiftRightKeyword";
        case SyntaxKind::StringKeyword: return "StringKeyword";
        case SyntaxKind::ThenKeyword: return "ThenKeyword";
        case SyntaxKind::ThreadVarKeyword: return "ThreadVarKeyword";
        case SyntaxKind::ToKeyword: return "ToKeyword";
        case SyntaxKind::TryKeyword: return "TryKeyword";
        case SyntaxKind::TypeKeyword: return "TypeKeyword";
        case SyntaxKind::UnitKeyword: return "UnitKeyword";
        case SyntaxKind::UntilKeyword: return "UntilKeyword";
        case SyntaxKind::UsesKeyword: return "UsesKeyword";
        case SyntaxKind::VarKeyword: return "VarKeyword";
        case SyntaxKind::WhileKeyword: return "WhileKeyword";
        case SyntaxKind::WithKeyword: return "WithKeyword";
        case SyntaxKind::XorKeyword: return "XorKeyword";
        case SyntaxKind::AbsoluteKeyword: return "AbsoluteKeyword";
        case SyntaxKind::AbstractKeyword: return "AbstractKeyword";
        case SyntaxKind::AssemblerKeyword: return "AssemblerKeyword";
        case SyntaxKind::AutomatedKeyword: return "AutomatedKeyword";
        case SyntaxKind::CdeclKeyword: return "CdeclKeyword";
        case SyntaxKind::ContainsKeyword: return "ContainsKeyword";
        case SyntaxKind::DefaultKeyword: return "DefaultKeyword";
        case SyntaxKind::DelayedKeyword: return "DelayedKeyword";
        case SyntaxKind::DeprecatedKeyword: return "DeprecatedKeyword";
        case SyntaxKind::DispIdKeyword: return "DispIdKeyword";
        case SyntaxKind::DynamicKeyword: return "DynamicKeyword";
        case SyntaxKind::ExperimentalKeyword: return "ExperimentalKeyword";
        case SyntaxKind::ExportKeyword: return "ExportKeyword";
        case SyntaxKind::ExternalKeyword: return "ExternalKeyword";
        case SyntaxKind::FarKeyword: return "FarKeyword";
        case SyntaxKind::FinalKeyword: return "FinalKeyword";
        case SyntaxKind::ForwardKeyword: return "ForwardKeyword";
        case SyntaxKind::HelperKeyword: return "HelperKeyword";
        case SyntaxKind::ImplementsKeyword: return "ImplementsKeyword";
        case SyntaxKind::IndexKeyword: return "IndexKeyword";
        case SyntaxKind::LocalKeyword: return "LocalKeyword";
        case SyntaxKind::MessageKeyword: return "MessageKeyword";
        case SyntaxKind::NameKeyword: return "NameKeyword";
        case SyntaxKind::NearKeyword: return "NearKeyword";
        case SyntaxKind::NoDefaultKeyword: return "NoDefaultKeyword";
        case SyntaxKind::OperatorKeyword: return "OperatorKeyword";
        case SyntaxKind::OutKeyword: return "OutKeyword";
        case SyntaxKind::OverloadKeyword: return "OverloadKeyword";
        case SyntaxKind::OverrideKeyword: return "OverrideKeyword";
        case SyntaxKind::PackageKeyword: return "PackageKeyword";
        case SyntaxKind::PascalKeyword: return "PascalKeyword";
        case SyntaxKind::PlatformKeyword: return "PlatformKeyword";
        case SyntaxKind::PrivateKeyword: return "PrivateKeyword";
        case SyntaxKind::ProtectedKeyword: return "ProtectedKeyword";
        case SyntaxKind::PublicKeyword: return "PublicKeyword";
        case SyntaxKind::PublishedKeyword: return "PublishedKeyword";
        case SyntaxKind::ReadKeyword: return "ReadKeyword";
        case SyntaxKind::ReadOnlyKeyword: return "ReadOnlyKeyword";
        case SyntaxKind::ReferenceKeyword: return "ReferenceKeyword";
        case SyntaxKind::RegisterKeyword: return "RegisterKeyword";
        case SyntaxKind::ReintroduceKeyword: return "ReintroduceKeyword";
        case SyntaxKind::RequiresKeyword: return "RequiresKeyword";
        case SyntaxKind::ResidentKeyword: return "ResidentKeyword";
        case SyntaxKind::SafeCallKeyword: return "SafeCallKeyword";
        case SyntaxKind::SealedKeyword: return "SealedKeyword";
        case SyntaxKind::StaticKeyword: return "StaticKeyword";
        case SyntaxKind::StdCallKeyword: return "StdCallKeyword";
        case SyntaxKind::StrictKeyword: return "StrictKeyword";
        case SyntaxKind::StoredKeyword: return "StoredKeyword";
        case SyntaxKind::UnsafeKeyword: return "UnsafeKeyword";
        case SyntaxKind::VarArgsKeyword: return "VarArgsKeyword";
        case SyntaxKind::VirtualKeyword: return "VirtualKeyword";
        case SyntaxKind::WinApiKeyword: return "WinApiKeyword";
        case SyntaxKind::WriteKeyword: return "WriteKeyword";
        case SyntaxKind::WriteOnlyKeyword: return "WriteOnlyKeyword";
        case SyntaxKind::ByteKeyword: return "ByteKeyword";
        case SyntaxKind::ShortIntKeyword: return "ShortIntKeyword";
        case SyntaxKind::WordKeyword: return "WordKeyword";
        case SyntaxKind::SmallIntKeyword: return "SmallIntKeyword";
        case SyntaxKind::CardinalKeyword: return "CardinalKeyword";
        case SyntaxKind::LongWordKeyword: return "LongWordKeyword";
        case SyntaxKind::FixedUIntKeyword: return "FixedUIntKeyword";
        case SyntaxKind::IntegerKeyword: return "IntegerKeyword";
        case SyntaxKind::LongIntKeyword: return "LongIntKeyword";
        case SyntaxKind::FixedIntKeyword: return "FixedIntKeyword";
        case SyntaxKind::UInt64Keyword: return "UInt64Keyword";
        case SyntaxKind::Int64Keyword: return "Int64Keyword";
        case SyntaxKind::NativeUIntKeyword: return "NativeUIntKeyword";
        case SyntaxKind::NativeIntKeyword: return "NativeIntKeyword";
        case SyntaxKind::BytePointerKeyword: return "BytePointerKeyword";
        case SyntaxKind::ShortIntPointerKeyword: return "ShortIntPointerKeyword";
        case SyntaxKind::WordPointerKeyword: return "WordPointerKeyword";
        case SyntaxKind::SmallIntPointerKeyword: return "SmallIntPointerKeyword";
        case SyntaxKind::CardinalPointerKeyword: return "CardinalPointerKeyword";
        case SyntaxKind::LongWordPointerKeyword: return "LongWordPointerKeyword";
        case SyntaxKind::FixedUIntPointerKeyword: return "FixedUIntPointerKeyword";
        case SyntaxKind::IntegerPointerKeyword: return "IntegerPointerKeyword";
        case SyntaxKind::LongIntPointerKeyword: return "LongIntPointerKeyword";
        case SyntaxKind::FixedIntPointerKeyword: return "FixedIntPointerKeyword";
        case SyntaxKind::UInt64PointerKeyword: return "UInt64PointerKeyword";
        case SyntaxKind::Int64PointerKeyword: return "Int64PointerKeyword";
        case SyntaxKind::NativeUIntPointerKeyword: return "NativeUIntPointerKeyword";
        case SyntaxKind::NativeIntPointerKeyword: return "NativeIntPointerKeyword";
        case SyntaxKind::SingleKeyword: return "SingleKeyword";
        case SyntaxKind::DoubleKeyword: return "DoubleKeyword";
        case SyntaxKind::ExtendedKeyword: return "ExtendedKeyword";
        case SyntaxKind::RealKeyword: return "RealKeyword";
        case SyntaxKind::SinglePointerKeyword: return "SinglePointerKeyword";
        case SyntaxKind::DoublePointerKeyword: return "DoublePointerKeyword";
        case SyntaxKind::ExtendedPointerKeyword: return "ExtendedPointerKeyword";
        case SyntaxKind::AnsiCharKeyword: return "AnsiCharKeyword";
        case SyntaxKind::CharKeyword: return "CharKeyword";
        case SyntaxKind::WideCharKeyword: return "WideCharKeyword";
        case SyntaxKind::AnsiStringKeyword: return "AnsiStringKeyword";
        case SyntaxKind::RawByteStringKeyword: return "RawByteStringKeyword";
        case SyntaxKind::UnicodeStringKeyword: return "UnicodeStringKeyword";
        case SyntaxKind::ShortStringKeyword: return "ShortStringKeyword";
        case SyntaxKind::WideStringKeyword: return "WideStringKeyword";
        case SyntaxKind::AnsiCharPointerKeyword: return "AnsiCharPointerKeyword";
        case SyntaxKind::CharPointerKeyword: return "CharPointerKeyword";
        case SyntaxKind::WideCharPointerKeyword: return "WideCharPointerKeyword";
        case SyntaxKind::AnsiStringPointerKeyword: return "AnsiStringPointerKeyword";
        case SyntaxKind::RawByteStringPointerKeyword: return "RawByteStringPointerKeyword";
        case SyntaxKind::UnicodeStringPointerKeyword: return "UnicodeStringPointerKeyword";
        case SyntaxKind::StringPointerKeyword: return "StringPointerKeyword";
        case SyntaxKind::ShortStringPointerKeyword: return "ShortStringPointerKeyword";
        case SyntaxKind::WideStringPointerKeyword: return "WideStringPointerKeyword";
        case SyntaxKind::BooleanKeyword: return "BooleanKeyword";
        case SyntaxKind::ByteBoolKeyword: return "ByteBoolKeyword";
        case SyntaxKind::WordBoolKeyword: return "WordBoolKeyword";
        case SyntaxKind::LongBoolKeyword: return "LongBoolKeyword";
        case SyntaxKind::BooleanPointerKeyword: return "BooleanPointerKeyword";
        case SyntaxKind::WordBoolPointerKeyword: return "WordBoolPointerKeyword";
        case SyntaxKind::LongBoolPointerKeyword: return "LongBoolPointerKeyword";
        case SyntaxKind::PointerKeyword: return "PointerKeyword";
        case SyntaxKind::VariantKeyword: return "VariantKeyword";
        case SyntaxKind::CurrencyKeyword: return "CurrencyKeyword";
        case SyntaxKind::PointerPointerKeyword: return "PointerPointerKeyword";
        case SyntaxKind::VariantPointerKeyword: return "VariantPointerKeyword";
        case SyntaxKind::CurrencyPointerKeyword: return "CurrencyPointerKeyword";
        case SyntaxKind::Real48Keyword: return "Real48Keyword";
        case SyntaxKind::UTF8StringKeyword: return "UTF8StringKeyword";
        case SyntaxKind::OleVariantKeyword: return "OleVariantKeyword";
        case SyntaxKind::OleVariantPointerKeyword: return "OleVariantPointerKeyword";
        case SyntaxKind::AddKeyword: return "AddKeyword";
        case SyntaxKind::RemoveKeyword: return "RemoveKeyword";
        case SyntaxKind::AssemblyKeyword: return "AssemblyKeyword";
        case SyntaxKind::BreakKeyword: return "BreakKeyword";
        case SyntaxKind::ContinueKeyword: return "ContinueKeyword";
        case SyntaxKind::TrueKeyword: return "TrueKeyword";
        case SyntaxKind::FalseKeyword: return "FalseKeyword";

        case SyntaxKind::SingleQuotationStringLiteralToken: return "SingleQuotationStringLiteralToken";
        case SyntaxKind::DoubleQuotationStringLiteralToken: return "DoubleQuotationStringLiteralToken";
        case SyntaxKind::NumberLiteralToken: return "NumberLiteralToken";
        case SyntaxKind::IdentifierToken: return "IdentifierToken";

        // trivia
        case SyntaxKind::WhitespaceTrivia: return "WhitespaceTrivia";
        case SyntaxKind::SingleLineCommentTrivia: return "SingleLineCommentTrivia";
        case SyntaxKind::MultiLineCommentTrivia: return "MultiLineCommentTrivia";
        case SyntaxKind::EndOfLineTrivia: return "EndOfLineTrivia";
        case SyntaxKind::BadDirectiveTrivia: return "BadDirectiveTrivia";
        case SyntaxKind::IfDirectiveTrivia: return "IfDirectiveTrivia";
        case SyntaxKind::IfDefDirectiveTrivia: return "IfDefDirectiveTrivia";
        case SyntaxKind::IfNDefDirectiveTrivia: return "IfNDefDirectiveTrivia";
        case SyntaxKind::IfEndDirectiveTrivia: return "IfEndDirectiveTrivia";
        case SyntaxKind::ElseIfDirectiveTrivia: return "ElseIfDirectiveTrivia";
        case SyntaxKind::ElseDirectiveTrivia: return "ElseDirectiveTrivia";
        case SyntaxKind::EndIfDirectiveTrivia: return "EndIfDirectiveTrivia";
        case SyntaxKind::DefineDirectiveTrivia: return "DefineDirectiveTrivia";
        case SyntaxKind::UndefDirectiveTrivia: return "UndefDirectiveTrivia";
        case SyntaxKind::RegionDirectiveTrivia: return "RegionDirectiveTrivia";
        case SyntaxKind::EndRegionDirectiveTrivia: return "EndRegionDirectiveTrivia";
        case SyntaxKind::MessageDirectiveTrivia: return "MessageDirectiveTrivia";
        case SyntaxKind::SwitchDirectiveTrivia: return "SwitchDirectiveTrivia";
        case SyntaxKind::SkippedTokensTrivia: return "SkippedTokensTrivia";

        // directives
        case SyntaxKind::IfDirectiveKeyword: return "IfDirectiveKeyword";
        case SyntaxKind::ElseIfDirectiveKeyword: return "ElseIfDirectiveKeyword";
        case SyntaxKind::ElseDirectiveKeyword: return "ElseDirectiveKeyword";
        case SyntaxKind::EndIfDirectiveKeyword: return "EndIfDirectiveKeyword";
        case SyntaxKind::DefineDirectiveKeyword: return "DefineDirectiveKeyword";
        case SyntaxKind::UndefDirectiveKeyword: return "UndefDirectiveKeyword";
        case SyntaxKind::RegionDirectiveKeyword: return "RegionDirectiveKeyword";
        case SyntaxKind::EndRegionDirectiveKeyword: return "EndRegionDirectiveKeyword";
        case SyntaxKind::MessageDirectiveKeyword: return "MessageDirectiveKeyword";
        case SyntaxKind::OnDirectiveKeyword: return "OnDirectiveKeyword";
        case SyntaxKind::OffDirectiveKeyword: return "OffDirectiveKeyword";
        case SyntaxKind::EndOfDirectiveToken: return "EndOfDirectiveToken";

        case SyntaxKind::SyntaxList: return "SyntaxList";
        case SyntaxKind::CompilationUnit: return "CompilationUnit";
        case SyntaxKind::UnitModule: return "UnitModule";
        case SyntaxKind::UnitHeading: return "UnitHeading";
        case SyntaxKind::UnitInterfaceSection: return "UnitInterfaceSection";
        case SyntaxKind::UnitImplementationSection: return "UnitImplementationSection";
        case SyntaxKind::UnitInitializationSection: return "UnitInitializationSection";
        case SyntaxKind::UnitFinalizationSection: return "UnitFinalizationSection";
        case SyntaxKind::PackageModule: return "PackageModule";
        case SyntaxKind::PackageHeading: return "PackageHeading";
        case SyntaxKind::ProgramModule: return "ProgramModule";
        case SyntaxKind::ProgramHeading: return "ProgramHeading";

        case SyntaxKind::PackageRequiresClause: return "PackageRequiresClause";
        case SyntaxKind::PackageContainsClause: return "PackageContainsClause";
        case SyntaxKind::UsesClause: return "UsesClause";
        case SyntaxKind::UnitReference: return "UnitReference";

        // expressions
        case SyntaxKind::LogicalNotExpression: return "LogicalNotExpression";
        case SyntaxKind::LogicalOrExpression: return "LogicalOrExpression";
        case SyntaxKind::LogicalAndExpression: return "LogicalAndExpression";
        case SyntaxKind::EqualsExpression: return "EqualsExpression";
        case SyntaxKind::NotEqualsExpression: return "NotEqualsExpression";
        case SyntaxKind::ParenthesizedExpression: return "ParenthesizedExpression";
        case SyntaxKind::StringLiteralExpression: return "StringLiteralExpression";
        case SyntaxKind::NumericLiteralExpression: return "NumericLiteralExpression";
        case SyntaxKind::TrueLiteralExpression: return "TrueLiteralExpression";
        case SyntaxKind::FalseLiteralExpression: return "FalseLiteralExpression";
        case SyntaxKind::IdentifierNameExpression: return "IdentifierNameExpression";
        case SyntaxKind::QualifiedNameExpression: return "QualifiedNameExpression";
        case SyntaxKind::CallExpression: return "CallExpression";
    }

    return "";
}

} // end namespace polyglot::CodeAnalysis
