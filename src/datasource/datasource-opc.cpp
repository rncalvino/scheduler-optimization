#include "datasource/datasource-opc.h"

Job DatasourceOPC::makeJob(const JobOpc& jobOpc) const {

	Job job(jobOpc.id, jobOpc.mean, jobOpc.deviation, jobOpc.name);

	for(auto predecesor : jobOpc.predecessors) {

		auto jobPredecesor = this->makeJob(predecesor);

		job.addPredecessor(jobPredecesor);
	}

	return job;
}

std::vector<JobOpc> DatasourceOPC::makeJobsFromResources(std::vector<std::unique_ptr<Resource>>& resources) const {

	int index = 0;
	std::map<std::string, JobOpc> jobs;
	std::map<std::string, ApplicationOpc> applicationes;

	/**
	 * 1st iteration will create all jobs.
	 */

	std::for_each(std::begin(resources), std::end(resources), [&index, &jobs, &applicationes](auto& resource) {

		auto itJob = jobs.find(resource->jcl);

		if (itJob == jobs.end()) {

			JobOpc job;
			job.id = ++index;
			job.name = resource->jcl;
			job.internalNumber = resource->internalNumber;
			job.mean = resource->mean;
			job.deviation = resource->deviation;

			auto it = applicationes.find(resource->application);

			if (it == applicationes.end()) {

				job.application = ApplicationOpc();
				job.application.name = resource->application;
				job.application.addJob(job);

				applicationes.insert(std::make_pair(job.application.name, job.application));

			} else {

				job.application = it->second;
				job.application.addJob(job);
			}

			jobs.insert(std::make_pair(job.name, job));
		}
	});

	/**
	* 2nd iteration will assign predecessors to each job.
	*/

	std::for_each(std::begin(resources), std::end(resources), [&jobs, &applicationes](auto& Resource) {

		auto itJob = jobs.find(Resource->jcl);

		if (itJob != std::end(jobs))
			Resource->addPredecessor(itJob->second, applicationes, jobs);
	});

	std::vector<JobOpc> vjobs;

	std::for_each(std::begin(jobs), std::end(jobs), [&vjobs](std::pair<std::string, JobOpc> pair) {

		vjobs.push_back(pair.second);
	});

	return vjobs;
}

std::vector<std::unique_ptr<Resource>> DatasourceOPC::readResources(const std::string& archivo) const {

	std::ifstream f(archivo);

	aria::csv::CsvParser parser = aria::csv::CsvParser(f)
		.delimiter(';')   
		.terminator('\n');

	std::vector<std::unique_ptr<Resource>> resources;

	for (auto csv : parser) {

		std::string tipoResource = csv.at(4);

		std::unique_ptr<Resource> Resource;

		if (tipoResource == "pint") {
			Resource = std::make_unique<ResourcePint>();
		} else if (tipoResource == "pext") {
			Resource = std::make_unique<ResourcePext>();
		} else if (tipoResource == "recu") {
			Resource = std::make_unique<ResourceRecu>();
		} else {
			throw std::invalid_argument("Tipo de Resource no valido");
		}

		Resource->initialize(csv);
		resources.push_back(std::move(Resource));
	}

	return resources;
}