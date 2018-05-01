#include "common.h"

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        std::cout << "Usage: rclst N modelfname" << std::endl;
        return 0;
    }

    std::size_t N{std::stoul(argv[1])};
    std::string modelfname{argv[2]};


    dlib::kcentroid<kernel_type> kc(kernel_type(), 0.01, 8);
    dlib::kkmeans<kernel_type> test(kc);

    std::vector<sample_type> samples;
    std::vector<sample_type> initial_centers;

    std::string line;

    while(std::getline(std::cin, line))
    {
        auto sample = getSampleFromLine(line);
        if(sample(0) != -1)
            samples.emplace_back(std::move(sample ));
    }

    test.set_number_of_centers(N);
    dlib::pick_initial_centers(test.number_of_centers(), initial_centers, samples, test.get_kernel());
    dlib::find_clusters_using_kmeans(samples, initial_centers);
    test.train(samples, initial_centers);

    clusters_type clusters;
    for(const auto& sample: samples)
    {
        auto cluster = test(sample);
        clusters[cluster].push_back(sample);
    }

    dlib::serialize(modelfname) << clusters << test;

    return 0;
}
