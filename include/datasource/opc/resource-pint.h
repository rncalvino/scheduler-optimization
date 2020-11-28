#ifndef RECURSO_PINT_H_
#define RECURSO_PINT_H_

#include "tools/compiler.h"
#include "resource.h"

class ResourcePint : public Resource {

public: 
	
	int internalPredecessorNumber;

	ResourcePint() : internalPredecessorNumber(0) { }

	void initialize(const std::vector<std::string>& csv) {

		Resource::initialize(csv);

		if (!csv.at(5).empty()) 
			this->internalPredecessorNumber = std::stoi(csv.at(5));
	}

	void addPredecessor(JobOpc& job, std::map<std::string, ApplicationOpc>& UNUSED(applications), const std::map<std::string, JobOpc>& UNUSED(jobs)) {

		job.addInternalPredecessor(this->internalPredecessorNumber);
	}
};

#endif