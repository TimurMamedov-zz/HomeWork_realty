#include "common.h"

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cout << "Usage: rclss modelfname" << std::endl;
        return 0;
    }

    std::string modelfname{argv[1]};

    dlib::kcentroid<kernel_type> kc(kernel_type(), 0.01, 8);
    dlib::kkmeans<kernel_type> test(kc);

    clusters_type clusters;

    dlib::deserialize(modelfname) >> clusters >> test;

    std::string line;

    while(std::getline(std::cin, line))
    {
        auto sample = getSampleFromLine(line);
        findNearestSamples(sample, clusters[test(sample)]);
    }

    return 0;
}
