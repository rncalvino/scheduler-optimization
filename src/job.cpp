#include "job.h"

Job::Job(const Job& job) {

	this->id = job.id;
	this->name = job.name;
	this->mean = job.mean;
	this->sd = job.sd;
	this->predecessors = job.predecessors;
}

Job::~Job() { }

bool Job::operator!=(const Job& otherJob) {

	return this->name != otherJob.name;
}

bool Job::hasPredecessor(const Job& job) {

	auto itPredecesor = std::find_if(std::begin(this->predecessors), std::end(this->predecessors), [&job](const Job& predecesor) {
		return job.id == predecesor.id;
	});

	return itPredecesor != std::end(this->predecessors);
}

void Job::addPredecessor(Job& job) {

	if (*this != job && !job.hasPredecessor(*this))
		this->predecessors.push_back(job);
}
