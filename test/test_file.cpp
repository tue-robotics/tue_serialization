#include <tue/serialization/file.h>
#include <tue/serialization/filesystem.h>

int main(int argc, char **argv)
{
    {
        tue::Package pkg;

        pkg.set_meta_data("{\"foo\": 123, \"bar\": 456}");

        for(unsigned int i = 0; i < 7; ++i)
        {
            unsigned int size = i * 10000000;
            boost::shared_ptr<tue::VectorBinary> bin(new tue::VectorBinary);
            bin->allocate(size);

            for(unsigned int j = 0; j < size; ++j)
            {
                bin->vector()[j] = j * 5;
            }

            pkg.addBinary(bin);
        }

        tue::serialization::toFile(pkg, "/tmp/test-file");
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    {
        tue::Package pkg;

        if (!tue::serialization::fromFile("/tmp/test-file", pkg))
        {
            std::cout << "Could not read test file" << std::endl;
            return 1;
        }

        std::cout << "Meta-data: " << pkg.meta_data() << std::endl;

        for(unsigned int i = 0; i < pkg.binaries().size(); ++i)
        {
            const tue::BinaryConstPtr& bin = pkg.binaries()[i];
            std::cout << i << ": " << bin->size() << " byte" << std::endl;

//            for(unsigned int j = 0; j < bin->size(); ++j)
//            {
//                std::cout << " " << (int)bin->ptr()[j];
//            }

//            std::cout << std::endl;
        }
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

//    {
//        tue::StructuredData data;

//        boost::shared_ptr<tue::VectorBinary> rgb_data(new tue::VectorBinary);
//        {
//            std::vector<char>& v = rgb_data->vector();
//            v.resize(100);
//            for(unsigned int j = 0; j < v.size(); ++j)
//                v[j] = j * 3;
//        }

//        boost::shared_ptr<tue::VectorBinary> depth_data(new tue::VectorBinary);
//        {
//            std::vector<char>& v = depth_data->vector();
//            v.resize(100);
//            for(unsigned int j = 0; j < v.size(); ++j)
//                v[j] = j * 5;
//        }

//        JSONWriter w(data.meta_data());
//        w.writeValue("rgb-data", data.addBinary(rgb_data));
//        w.writeValue("depth-data", data.addBinary(depth_data));

//        w.writeGroup("model");
//        w.writeValue("fx", 100);
//        w.writeValue("fy", 100);
//        w.endGroup();
//    }

    return 0;
}
