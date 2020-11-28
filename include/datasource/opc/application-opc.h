#ifndef APPLICATION_OPC_H_
#define APPLICATION_OPC_H_

#include <string>
#include <vector>
#include <memory>

class JobOpc;

class ApplicationOpc {

public:
	std::string name;
	std::vector<JobOpc> jobs;
	ApplicationOpc();
	~ApplicationOpc();
	void addJob(JobOpc job);
	void addInternalPredecessor(JobOpc& job, int internalPredecessorNumber);
	void addExternalPredecessor(JobOpc& job, std::string externalPredecessorName, int externalPredecessorNumber);
};

#endif