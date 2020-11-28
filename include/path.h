#ifndef PATH_H_
#define PATH_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include "tools/compiler.h"
#include "job.h"

class Path {

private:
	const int DEVIATIONS = 2;

public:
	std::vector<Job> jobs;
	long elapsedTime;
	Path() { }
	Path(const Path&);
	void operator=(const Path&);
	void addJob(const Job job);
	double getDuration();
	double getDeviation();
	int getConfidence();
	std::pair<double, double> getConfidenceInterval();
	void toStatsFile(const std::string&);
};

#endif