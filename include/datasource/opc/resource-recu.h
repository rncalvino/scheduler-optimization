#ifndef RECURSO_RECU_H_
#define RECURSO_RECU_H_

#include "tools/compiler.h"
#include "resource.h"

class ResourceRecu : public Resource {

public: 
	std::string externalResource;

	void initialize(const std::vector<std::string>& csv) {

		Resource::initialize(csv);

		this->externalResource = csv.at(6);
	}

	void addPredecessor(JobOpc& job, std::map<std::string, ApplicationOpc>& UNUSED(applications), const std::map<std::string, JobOpc>& jobs) {

		std::string jclSpecialResource = this->externalResource.substr(3, 8);

		auto itJobRecursoEspecial = jobs.find(jclSpecialResource);

		if (itJobRecursoEspecial != std::end(jobs)) {

			job.addPredecessor(itJobRecursoEspecial->second);
		}
	}
};

#endif