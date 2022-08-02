/// 6

#include <boost/detail/lightweight_test.hpp>

#include <boost/convert.hpp>
#include <boost/convert/lexical_cast.hpp>
#include <boost/convert/stream.hpp>

using boost::convert;

using boost::lexical_cast;
using std::string;

void getting_started_example5()
{
    //[getting_started_example5
    boost::cnv::cstream cnv;

    int i1 = lexical_cast<int>("123");  // 转换失败时抛出。
    int i2 = convert<int>("123", cnv).value();  // 转换失败时抛出。
    int i3 = convert<int>("uhm", cnv).value_or(-1);  // 转换失败时返回-1。

    BOOST_TEST(i1 == 123);
    BOOST_TEST(i2 == 123);
    BOOST_TEST(i3 == -1);
    //]
}

/// 以上被翻译成英文为

/// 对i1和i2“将字符串转换为int”和
/// 对i3将字符串转换为int并在转换失败时返回-1”。

/// i1和i2部署看起来足够接近并且行为相同。 即，用户指令对转换失败保持沉默，这些指令被视为“异常”并抛出。
/// 规范明确说明了转换失败。 如果请求的转换失败，则返回提供的备用值。
/// 对于各种转换部署，基本的错误检测和处理可能就足够了。 例如：

void log(char const*)
{
    // 演示如何记录问题的虚拟函数。
}

void getting_started_example6()
{
    std::string s1 = "123";
    std::string s2 = "456";
    int default_i1 = 11;
    int default_i2 = 12;
    auto cnv = boost::cnv::cstream();

    //[getting_started_example6

    int i1 = convert<int>(s1, cnv(std::hex)).value_or(-1);  // 读取为十六进制
    int i2 = convert<int>(s2, cnv(std::dec)).value_or(-1);  // 读为十进制

    if (i1 == -1)
        log("bad i1"), i1 = default_i1;  // 日志失败。 继续默认
    if (i2 == -1)
        log("bad i2"), i2 = default_i2;  // 日志失败。 继续默认

    // ... proceed
    //]
    BOOST_TEST(i1 == 291);
    BOOST_TEST(i2 == 456);
}

/// 或者

//[getting_started_example9_func
int fallback_fun(char const* msg, int fallback_value)
{
    /// fallback_func优于 fallback_value的主要优点是前者仅在转换请求失败时调用。
    /// 因此，仅在绝对必要时才计算返回的 fallback_value（这可能很昂贵）。
    log(msg);
    return fallback_value;
}
//]

struct boost::cnv::by_default : boost::cnv::lexical_cast
{
};

void getting_started_example9()
{
    std::string const s1 = "123";
    std::string const s2 = "456";
    int const default_i1 = 11;
    int const default_i2 = 12;

    //[getting_started_example9
    int i1 = convert<int>(s1).value_or_eval(std::bind(fallback_fun, "bad i1", default_i1));
    int i2 = convert<int>(s2).value_or_eval(std::bind(fallback_fun, "bad i2", default_i2));
    // ... proceed
    //]
    BOOST_TEST(i1 == 123);
    BOOST_TEST(i2 == 456);
}

/// 或者，如果我们不关心记录转换失败：

void getting_started_example7()
{
    std::string s1 = "123";
    std::string s2 = "456";
    int default_i1 = 11;
    int default_i2 = 12;
    auto cnv = boost::cnv::cstream();

    //[getting_started_example7

    int i1 = convert<int>(s1, cnv(std::hex)).value_or(default_i1);  // 如果失败，请继续使用默认值
    int i2 = convert<int>(s2, cnv(std::dec)).value_or(default_i2);  // 如果失败，请继续使用默认值
    // ... proceed
    //]
    BOOST_TEST(i1 == 291);
    BOOST_TEST(i2 == 456);
}

/// 到目前为止，与boost::lexical_cast相比，boost::convert的部署似乎更灵活、更紧凑、更自然（您的里程可能会有所不同）
/// 并且可能更有效，后者通过以下方式实现了类似的结果：

void getting_started_example8()
{
    std::string const str = "123";
    int const default_i1 = 12;
    //[getting_started_example8
    int i1 = default_i1;

    try
    {
        i1 = lexical_cast<int>(str);
    }
    catch (...)
    {
        log("bad i1");
    }
    //]
    BOOST_TEST(i1 == 123);
}

/// 按照设计，这是 boost::lexical_cast的唯一行为——简单易懂，但有限。
/// 它使相当多的合法流程/程序流难以实施且难以实施。
/// Boost.Convert以附加的功能、灵活性和便利性解决了这个问题。