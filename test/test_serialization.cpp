#include <tue/serialization/archive.h>
#include <tue/serialization/input_archive.h>
#include <tue/serialization/output_archive.h>

#include <fstream>

int main(int argc, char **argv) {

    std::string test_filename = "/tmp/tue_test_serialization";

    {
        // example
        double d = 3.15;
        float f = 5.0;
        int i = 123;
        std::string s = "Hello, this is just a simple test";

        // write
        std::ofstream f_out;
        f_out.open(test_filename.c_str(), std::ifstream::binary);

        tue::serialization::OutputArchive a_out(f_out, 0);
        a_out << d << f << i << s;
        f_out.close();
    }

    {
        // read
        double d;
        float f;
        int i;
        std::string s;

        std::ifstream f_in;
        f_in.open(test_filename.c_str(), std::ifstream::binary);

        tue::serialization::InputArchive a_in(f_in);
        a_in >> d >> f >> i >> s;
        f_in.close();

        std::cout << d << ", " << f << ", " << i << ", \"" << s << "\"" << std::endl;
    }

    tue::serialization::Archive a;

    {
        // example
        double d = 3.15;
        float f = 5.0;
        int i = 123;
        std::string s = "Hello, this is just a simple test";

        a << d << f << i << s;
    }

    {
        // read
        double d;
        float f;
        int i;
        std::string s;

        a >> d >> f >> i >> s;

        std::cout << d << ", " << f << ", " << i << ", \"" << s << "\"" << std::endl;
    }

    return 0;
}
