#include "datasource/opc/application-opc.h"
#include "datasource/opc/job-opc.h"

ApplicationOpc::ApplicationOpc() { }

ApplicationOpc::~ApplicationOpc() { }

void ApplicationOpc::addJob(JobOpc job) {

	this->jobs.push_back(job);
}

void ApplicationOpc::addInternalPredecessor(JobOpc& job, int internalPredecessorNumber) {

	for (auto j : this->jobs) 
		if (j.internalNumber == internalPredecessorNumber)
			if(!job.hasPredecessor(j))
				job.addPredecessor(j);
}

void ApplicationOpc::addExternalPredecessor(JobOpc& job, std::string externalPredecessorName, int externalPredecessorNumber) {

	for (auto j : this->jobs)
		if (j.internalNumber == externalPredecessorNumber || j.name == externalPredecessorName)
			if (!job.hasPredecessor(j))
				job.addPredecessor(j);
}