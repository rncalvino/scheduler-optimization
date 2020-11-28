#ifndef JOB_OPC_H_
#define JOB_OPC_H_

#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <memory>

#include "datasource/opc/application-opc.h"

class JobOpc {

public:
	int id;
	float mean;
	float deviation;
	int internalNumber;
	std::string name;
	ApplicationOpc application;
	std::vector<JobOpc> predecessors;
	JobOpc(int id, std::string name, float mean, float deviation, int internalNumber) : id(id), mean(mean), deviation(deviation), internalNumber(internalNumber), name(name) { };
	JobOpc() : id(0), mean(0), deviation(0), internalNumber(0), name("") { };
	~JobOpc();
	bool hasPredecessor(JobOpc& job);
	void addInternalPredecessor(int predecessorInternalNumber);
	void addExternalPredecessor(ApplicationOpc& application, std::string externalPredecessorName, int externalPredecessorNumber);
	void addPredecessor(const JobOpc job);
};

#endif