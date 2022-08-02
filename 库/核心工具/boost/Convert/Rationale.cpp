/// 1

/// Convert: An extendible and configurable type-conversion framework.
/// 一个可扩展和可配置的类型转换框架。

/// 基本原理
/// 我广泛使用文本配置文件，并且还在XML中处理和准备大量数据。
/// 因此，我需要一个可扩展的库，它提供一个统一的接口来在内部二进制表示和外部（主要是文本）表示之间转换各种数据。

/// 与其他库相比，boost::lexical_cast 库（具有正交和可扩展的设计）看起来非常有前途（参见H.Sutter的The String Formatters of Manor Farm以了解替代方案的讨论）。

/// 很遗憾，

/// 许多部署的用户类型根本不满足boost::lexical_cast要求（即，默认可构造性）；
/// 未能转换用户提供的配置参数并不少见或异常，以证明异常处理的麻烦和开销是合理的；因此，在处理转换失败时需要额外的灵活性（如果、何时以及如何）；
/// 需要额外的与转换相关的功能（例如格式化和语言环境支持）。 

/// 最初的希望是看到boost::lexical_cast扩展以适用于更广泛的部署场景。
/// 然而，在与 Kevlin Henney（boost::lexical_cast作者）和 Boost开发者论坛讨论之后，
/// 共同决定所需的扩展与原始设计和 boost::lexical_cast所体现的想法不兼容，
/// 因此，需要一个具有更丰富界面和功能的新组件。
/// 该决定导致了本文档中描述的Boost.Convert的开发。