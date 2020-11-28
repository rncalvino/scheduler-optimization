#ifndef DATASOURCE_MOCK_
#define DATASOURCE_MOCK_

#include <map>
#include "datasource.h"

class MockDataSource : public JobDataSource {

public:
	std::vector<Job> getJobs() const {
		std::vector<Job> jobs;
		return jobs;
	}
};

#endif