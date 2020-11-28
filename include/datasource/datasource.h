#ifndef DATASOURCE_H_
#define DATASOURCE_H_

#include <vector>
#include <map>
#include <string>
#include <boost/algorithm/string.hpp>

#include "job.h"

class JobDataSource {

protected:
	std::map<std::string, std::string> options;

public:

	void setOption(const std::string& key, const std::string& value) { 

		this->options.insert(std::make_pair(key, value));
	};

	virtual std::vector<Job> getJobs() const = 0;
};

#endif