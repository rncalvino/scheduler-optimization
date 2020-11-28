#ifndef SCHEDULE_H_
#define SCHEDULE_H_

#include <vector>
#include <fstream>
#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/format.hpp>

#include "datasource/datasource.h"
#include "job.h"
#include "path.h"
#include "CPM.h"

class Stage {
public:
	Job job;
	bool critic = false;
	Stage() { }
	Stage(Job job) : job(job) {}
	std::string label() {
		return this->job.name;
	}
};

class Task {
public:
	double media = 0;
	double desvio = 0;
	bool critic = false;
	Task() { }
	Task(double media, double desvio) : media(media), desvio(desvio) { }
	std::string label() {
		boost::format fmt("%.2f");
		std::string smedia = boost::str(fmt % std::fabs(this->media));
		std::string sdesvio = boost::str(fmt % this->desvio);
		return smedia + " (" + sdesvio + ")";
	}
};

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, Stage, Task> Graph;

class Schedule {

private:
	void assignDummyStart();
	void assignDummyEnd();
	void orderJobs();
	void compile();

public:
	const int START_DUMMY_JOB_ID = 0;
	const int END_DUMMY_JOB_ID = 9999;
	const std::string START_DUMMY_JOB_NAME = std::string("Start");
	const std::string END_DUMMY_JOB_NAME = std::string("End");

	Graph graph;
	Job dummyStart;
	Job dummyEnd;
	std::vector<Job> jobs;

	Schedule(const JobDataSource& jobDataSource);

	Path searchCriticalPath();
	void toFile(const std::string&);
};

#endif