#ifndef DATASOURCE_OPC_
#define DATASOURCE_OPC_

#include "job.h"
#include "parser.h"
#include "datasource.h"
#include "datasource/opc/resource.h"
#include "datasource/opc/resource-pint.h"
#include "datasource/opc/resource-pext.h"
#include "datasource/opc/resource-recu.h"
#include "datasource/opc/application-opc.h"

class DatasourceOPC : public JobDataSource {

public:
	std::vector<Job> getJobs() const {

		auto resources = this->readResources(this->options.at("JobsFile"));

		std::vector<Job> jobs;

		for(const auto& jobOpc : this->makeJobsFromResources(resources)) {
			auto job = this->makeJob(jobOpc);
			jobs.push_back(job);
		}

		return jobs;
	}

private:
	std::vector<std::unique_ptr<Resource>> readResources(const std::string& archivo) const;
	std::vector<JobOpc> makeJobsFromResources(std::vector<std::unique_ptr<Resource>>& rows) const;
	Job makeJob(const JobOpc& job) const;
};

#endif