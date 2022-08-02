/// 5

/// ��û��ʲô�ȱ仯���ȶ�����������������

/// ���磨�ڳ�ʼ������ά���׶Σ�����Ժ���Ӧ�Ա�ú���Ҫ��
/// Boost.Convert�Ĳ��������ڸ���������ݱ���е����͸��ġ�
/// ���磬����������������ڷ��׳���Ϊ����ô��

#include <boost/detail/lightweight_test.hpp>

#include <boost/convert.hpp>
#include <boost/convert/lexical_cast.hpp>

using boost::convert;
using boost::lexical_cast;
using std::string;

void getting_started_example2()
{
    // ���׳��� ʧ��ʱ���غ�ֵ (-1)��
    int i = convert<int>("uhm", boost::cnv::lexical_cast()).value_or(-1);

    BOOST_TEST(i == -1);  // ת��ʧ�ܡ� 'i'�����˺�ֵ��
}

/// ���ߣ���������ʶ��Ϊ̫���������ͨ������ת��������С��Ŭ��������ܣ�

#ifdef _MSC_VER
    #pragma warning(disable : 4459)
#endif

#include <boost/convert/spirit.hpp>
#include <boost/convert/strtol.hpp>

void getting_started_example3()
{
    auto cnv1 = boost::cnv::lexical_cast();
    auto cnv2 = boost::cnv::strtol();
    auto cnv3 = boost::cnv::spirit();

    [[maybe_unused]] int i1 = convert<int>("123", cnv1).value();
    [[maybe_unused]] int i2 = convert<int>("123", cnv2).value();  // ��lexical_cast��������
    [[maybe_unused]] int i3 = convert<int>("123", cnv3).value();  // ��lexical_cast���ı���
}

/// �෴�����Ҫ�����Ϊ֧�ָ��������ʽ����Ҫĳ�������ʽ����ôͬ������ͨ�����·�ʽ���㣺

namespace
{
    namespace local
    {
#if defined(_MSC_VER)
        static bool const is_msc = true;
#else
        static bool const is_msc = false;
#endif
    }
}

#include <boost/convert/stream.hpp>

void getting_started_example4()
{
    try
    {
        [[maybe_unused]] int i1 = lexical_cast<int>("   123");  // ��������
        BOOST_TEST(!"Never reached");
    }
    catch (...)
    {
    }

    auto cnv = boost::cnv::cstream();
    int i2 = convert<int>("   123", cnv(std::skipws)).value();  // �ɹ�
    string s1 = lexical_cast<string>(12.34567);
    string s2 = convert<string>(12.34567, cnv(std::fixed)(std::setprecision(3))).value();
    string s3 = convert<string>(12.34567, cnv(std::scientific)(std::setprecision(3))).value();
    // string expected = local::is_msc ? "1.235e+001" : "1.235e+01";(ԭ���룬����ʧ�ܡ�)
    string expected = "1.235e+01";

    BOOST_TEST(i2 == 123);  // boost::cnv::cstream. "   123"ת���ɹ���
    BOOST_TEST(s1 == "12.34567");  // boost::lexical_cast. ���Ȳ������á�
    BOOST_TEST(s2 == "12.346");  // boost::cnv::cstream.��������Ϊ3���̶��ġ�
    BOOST_TEST(s3 == expected);  // boost::cnv::cstream.��������Ϊ3����ѧ������.
}