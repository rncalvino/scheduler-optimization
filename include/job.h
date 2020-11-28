#ifndef JOB_H_
#define JOB_H_

#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <memory>

class Aplicacion;

class Job {

public:
	int id;
	double mean;
	double sd;
	std::string name;
	std::vector<Job> predecessors;
	Job(int id, double mean, double sd, std::string name) : id(id), mean(mean), sd(sd), name(name) { };
	Job() : id(0), mean(0), sd(0) { };
	Job(const Job& job);
	~Job();
	bool operator!=(const Job& otherJob);
	Job& operator=(const Job&) = default;
	bool hasPredecessor(const Job&);
	void addPredecessor(Job&);
};

#endif