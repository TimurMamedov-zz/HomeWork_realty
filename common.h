#pragma once
#include <stdexcept>
#include <iostream>
#include <map>
#include <cmath>

#include <boost/tokenizer.hpp>

#include <dlib/clustering.h>

using sample_type = dlib::matrix<double, 7, 1>;
using kernel_type = dlib::linear_kernel<sample_type>;
using clusters_type = std::map<std::size_t, std::vector<sample_type> >;

static boost::char_separator<char> sep{";\n", " ", boost::keep_empty_tokens};

sample_type getSampleFromLine(const std::string& line)
{
    std::vector<std::string> tokens;

    boost::tokenizer<boost::char_separator<char>> tok{line, sep};
    std::copy( tok.begin(), tok.end(), std::back_inserter(tokens) );

    sample_type m;
    try
    {
        for(auto i = std::size_t{0}; i < 7; i++)
            m(i) = std::stod(tokens[i]);
        if(tokens.size() > 7)
        {
            if(std::stoul(tokens[6]) == 1 ||
                    std::stoul(tokens[6]) == std::stoul(tokens[7]))
                m(6) = 0;
            else
                m(6) = 1;
        }
    }
    catch(...)
    {
        for(auto i = std::size_t{0}; i < tokens.size(); i++)
            std::cerr << tokens[i] << ";";
        std::cerr << tokens[tokens.size() - 1] << "\n";
        m(0) = -1;
    }

    return m;
}

template <typename Type>
Type sqr(Type x)
{
   return x * x;
}

inline double distance(const sample_type& first, const sample_type& second)
{
   return std::sqrt(sqr(first(0) - second(0)) + sqr(first(1) - second(1)));
}

void findNearestSamples(sample_type m, std::vector<sample_type> samples)
{
    std::sort(samples.begin(), samples.end(),
              [&m](const sample_type& first, const sample_type& second)
    {
        return distance(first, m) < distance(second, m);
    });

    if(!samples.empty())
    {
        std::for_each(samples.begin(), samples.end(), [](const sample_type& sample)
        {
            for(auto i = std::size_t{0}; i < 6; i++)
                std::cout << std::setprecision(15) <<sample(i) << ";";
            std::cout << sample(6) << "\n";
        });
    }
}
