#include <tue/serialization/archive.h>
#include <tue/serialization/input_archive.h>
#include <tue/serialization/output_archive.h>

#include <tue/serialization/filesystem.h>
#include <tue/serialization/version.h>

#include <fstream>
#include <sstream>

int main()
{
    // example
    const double d_c = 3.15;
    const float f_c = 5.0;
    const int i_c = 123;
    const std::string s_c = "Hello, this is just a simple test";

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
        std::cout << d << ", " << f << ", " << i << ", \"" << s << "\"" << std::endl;
        std::cout << "version: " << a_in.version() << std::endl;
    }


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

        std::cout << d << ", " << f << ", " << i << ", \"" << s << "\"" << std::endl;
        std::cout << "version: " << a_in.version() << std::endl;
    }

    tue::serialization::Archive a;

    {
        a << d_c << f_c << i_c << s_c;
    }

    {
        // read
        double d;
        float f;
        int i;
        std::string s;

        a >> d >> f >> i >> s;

        std::cout << d << ", " << f << ", " << i << ", \"" << s << "\"" << std::endl;
        std::cout << "version: " << a.version() << std::endl;
    }

    return 0;
}
