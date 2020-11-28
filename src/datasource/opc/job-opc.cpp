#include "datasource/opc/job-opc.h"
#include "datasource/opc/application-opc.h"

JobOpc::~JobOpc() { }

void JobOpc::addInternalPredecessor(int predecessorInternalNumber) {

	this->application.addInternalPredecessor(*this, predecessorInternalNumber);
}

void JobOpc::addExternalPredecessor(ApplicationOpc& application, std::string externalPredecessorName, int externalPredecessorNumber) {
	
	application.addExternalPredecessor(*this, externalPredecessorName, externalPredecessorNumber);
}

bool JobOpc::hasPredecessor(JobOpc& job) {

	auto itPredecessor = std::find_if(std::begin(this->predecessors), std::end(this->predecessors), [&job](JobOpc& predecessor) {
		return job.id == predecessor.id;
	});

	return itPredecessor != std::end(this->predecessors);
}

void JobOpc::addPredecessor(JobOpc job) {

	auto x = *this;

	if (this->id != job.id && !job.hasPredecessor(x))
		this->predecessors.push_back(job);
}
