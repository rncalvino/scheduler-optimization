#ifndef OPTION_H_
#define OPTION_H_

#include <boost/program_options.hpp>

class Option {

public:
    virtual bool shouldActivate(boost::program_options::variables_map&) = 0;
    virtual void activate(boost::program_options::variables_map&) = 0;
};

#endif