#include <gtest/gtest.h>

#include <tue/serialization/archive.h>
#include <tue/serialization/input_archive.h>
#include <tue/serialization/output_archive.h>

#include <tue/serialization/filesystem.h>
#include <tue/serialization/version.h>

#include <fstream>
#include <sstream>

// example


class tue_serialization : public testing::Test {
 protected:
    const double d_c = 3.15;
    const float f_c = 5.0;
    const int i_c = 123;
    const std::string s_c = "Hello, this is just a simple test";
};

TEST_F(tue_serialization, OutputArchive_InputArchive)
{
    std::stringstream ss;
    tue::serialization::OutputArchive a_out(ss);
    a_out << d_c << f_c << i_c << s_c;

    // read
    double d;
    float f;
    int i;
    std::string s;

    tue::serialization::InputArchive a_in(ss);
    a_in >> d >> f >> i >> s;
    EXPECT_DOUBLE_EQ(d, d_c);
    EXPECT_FLOAT_EQ(f, f_c);
    EXPECT_EQ(i, i_c);
    EXPECT_EQ(s, s_c);
    std::cout << "OutputArchive -> InputArchive:" << std::endl;
    std::cout << d << ", " << f << ", " << i << ", \"" << s << "\"" << std::endl;
    std::cout << "version: " << a_in.version() << std::endl;
}

TEST_F(tue_serialization, toFile_fromFile)
{
    std::string test_filename = "/tmp/tue_test_serialization";

    {
        tue::serialization::Archive a_out;
        a_out << d_c << f_c << i_c << s_c;

        tue::serialization::toFile(a_out, test_filename);
    }

    {
        tue::serialization::Archive a_in;
        tue::serialization::fromFile(test_filename, a_in);

        // read
        double d;
        float f;
        int i;
        std::string s;

        a_in >> d >> f >> i >> s;

        EXPECT_DOUBLE_EQ(d, d_c);
        EXPECT_FLOAT_EQ(f, f_c);
        EXPECT_EQ(i, i_c);
        EXPECT_EQ(s, s_c);
        std::cout << "toFile -> fromFile:" << std::endl;
        std::cout << d << ", " << f << ", " << i << ", \"" << s << "\"" << std::endl;
        std::cout << "version: " << a_in.version() << std::endl;
    }
}

TEST_F(tue_serialization, Archive)
{
    tue::serialization::Archive a;

    a << d_c << f_c << i_c << s_c;

    // read
    double d;
    float f;
    int i;
    std::string s;

    a >> d >> f >> i >> s;

    EXPECT_DOUBLE_EQ(d, d_c);
    EXPECT_FLOAT_EQ(f, f_c);
    EXPECT_EQ(i, i_c);
    EXPECT_EQ(s, s_c);
    std::cout << "Archive:" << std::endl;
    std::cout << d << ", " << f << ", " << i << ", \"" << s << "\"" << std::endl;
    std::cout << "version: " << a.version() << std::endl;
}

// Run all the tests that were declared with TEST()
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
