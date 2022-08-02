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

    int i1 = lexical_cast<int>("123");  // ת��ʧ��ʱ�׳���
    int i2 = convert<int>("123", cnv).value();  // ת��ʧ��ʱ�׳���
    int i3 = convert<int>("uhm", cnv).value_or(-1);  // ת��ʧ��ʱ����-1��

    BOOST_TEST(i1 == 123);
    BOOST_TEST(i2 == 123);
    BOOST_TEST(i3 == -1);
    //]
}

/// ���ϱ������Ӣ��Ϊ

/// ��i1��i2�����ַ���ת��Ϊint����
/// ��i3���ַ���ת��Ϊint����ת��ʧ��ʱ����-1����

/// i1��i2���������㹻�ӽ�������Ϊ��ͬ�� �����û�ָ���ת��ʧ�ܱ��ֳ�Ĭ����Щָ���Ϊ���쳣�����׳���
/// �淶��ȷ˵����ת��ʧ�ܡ� ��������ת��ʧ�ܣ��򷵻��ṩ�ı���ֵ��
/// ���ڸ���ת�����𣬻����Ĵ�����ʹ�����ܾ��㹻�ˡ� ���磺

void log(char const*)
{
    // ��ʾ��μ�¼��������⺯����
}

void getting_started_example6()
{
    std::string s1 = "123";
    std::string s2 = "456";
    int default_i1 = 11;
    int default_i2 = 12;
    auto cnv = boost::cnv::cstream();

    //[getting_started_example6

    int i1 = convert<int>(s1, cnv(std::hex)).value_or(-1);  // ��ȡΪʮ������
    int i2 = convert<int>(s2, cnv(std::dec)).value_or(-1);  // ��Ϊʮ����

    if (i1 == -1)
        log("bad i1"), i1 = default_i1;  // ��־ʧ�ܡ� ����Ĭ��
    if (i2 == -1)
        log("bad i2"), i2 = default_i2;  // ��־ʧ�ܡ� ����Ĭ��

    // ... proceed
    //]
    BOOST_TEST(i1 == 291);
    BOOST_TEST(i2 == 456);
}

/// ����

//[getting_started_example9_func
int fallback_fun(char const* msg, int fallback_value)
{
    /// fallback_func���� fallback_value����Ҫ�ŵ���ǰ�߽���ת������ʧ��ʱ���á�
    /// ��ˣ����ھ��Ա�Ҫʱ�ż��㷵�ص� fallback_value������ܺܰ��󣩡�
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

/// ���ߣ�������ǲ����ļ�¼ת��ʧ�ܣ�

void getting_started_example7()
{
    std::string s1 = "123";
    std::string s2 = "456";
    int default_i1 = 11;
    int default_i2 = 12;
    auto cnv = boost::cnv::cstream();

    //[getting_started_example7

    int i1 = convert<int>(s1, cnv(std::hex)).value_or(default_i1);  // ���ʧ�ܣ������ʹ��Ĭ��ֵ
    int i2 = convert<int>(s2, cnv(std::dec)).value_or(default_i2);  // ���ʧ�ܣ������ʹ��Ĭ��ֵ
    // ... proceed
    //]
    BOOST_TEST(i1 == 291);
    BOOST_TEST(i2 == 456);
}

/// ��ĿǰΪֹ����boost::lexical_cast��ȣ�boost::convert�Ĳ����ƺ����������ա�����Ȼ��������̿��ܻ�������ͬ��
/// ���ҿ��ܸ���Ч������ͨ�����·�ʽʵ�������ƵĽ����

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

/// ������ƣ����� boost::lexical_cast��Ψһ��Ϊ�������׶��������ޡ�
/// ��ʹ�൱��ĺϷ�����/����������ʵʩ������ʵʩ��
/// Boost.Convert�Ը��ӵĹ��ܡ�����Ժͱ����Խ����������⡣