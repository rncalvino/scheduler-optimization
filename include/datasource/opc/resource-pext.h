#ifndef RECURSO_PEXT_H_
#define RECURSO_PEXT_H_

#include "tools/compiler.h"
#include "application-opc.h"
#include "resource.h"

class ResourcePext : public Resource {

public:
	std::string externalPredecessorApplicationName;
	std::string externalPredecessorName;
	int externalPredecessorNumber;

	ResourcePext() : externalPredecessorNumber(0) { }

	void initialize(const std::vector<std::string>& csv) {

		Resource::initialize(csv);

		this->externalPredecessorApplicationName = boost::algorithm::trim_copy(csv.at(7));
		this->externalPredecessorName = boost::algorithm::trim_copy(csv.at(9));
		this->externalPredecessorName = this->externalPredecessorName == "INICIO" || this->externalPredecessorName == "FINAL" ? this->externalPredecessorApplicationName + "." + this->externalPredecessorName : this->externalPredecessorName;

		if (!csv.at(8).empty()) 
			this->externalPredecessorNumber = std::stoi(csv.at(8));
	}

	void addPredecessor(JobOpc& job, std::map<std::string, ApplicationOpc>& applications, const std::map<std::string, JobOpc>& UNUSED(jobs)) {
	
		auto itAplicacion = applications.find(this->externalPredecessorApplicationName);

		if (itAplicacion != applications.end()) {
			job.addExternalPredecessor(itAplicacion->second,
				this->externalPredecessorName,
				this->externalPredecessorNumber
			);
		}
	}
};

#endif