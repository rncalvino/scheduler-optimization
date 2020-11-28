#ifndef RECURSO_H_
#define RECURSO_H_

#include <string>
#include <memory>
#include "datasource/opc/job-opc.h"

class Resource {

public:

	std::string application;
	std::string jcl;
	int internalNumber;
	double mean;
	double deviation;

	Resource() : internalNumber(0), mean(0), deviation(0) { }

	virtual void initialize(const std::vector<std::string>& csv) {

		this->application = boost::algorithm::trim_copy(csv.at(1));
		this->jcl = boost::algorithm::trim_copy((csv.at(3)));
		this->jcl = this->jcl == "INICIO" || this->jcl == "FINAL" ? this->application + "." + this->jcl : this->jcl;
		this->internalNumber = std::stoi(csv.at(2));
		this->mean = std::stof(csv.at(10));
		this->deviation = std::stof(csv.at(11));
	}

	virtual void addPredecessor(JobOpc&, std::map<std::string, ApplicationOpc>&, const std::map<std::string, JobOpc>&) = 0;
};

#endif