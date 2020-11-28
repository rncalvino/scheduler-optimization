#include "schedule.h"

Schedule::Schedule(const JobDataSource& jobDataSource) {

	this->jobs = jobDataSource.getJobs();
	this->assignDummyStart();
	this->assignDummyEnd();
	this->orderJobs();
}

void Schedule::orderJobs() {

	std::sort(std::begin(this->jobs), std::end(this->jobs), [](const Job& j1, const Job& j2) {
		return j1.id < j2.id;
	});
}

void Schedule::assignDummyStart() {

	this->dummyStart = Job(Schedule::START_DUMMY_JOB_ID, 0, 0, Schedule::START_DUMMY_JOB_NAME);

	for (auto& job : this->jobs)
		if (job.predecessors.empty())
			job.predecessors.push_back(this->dummyStart);

	this->jobs.push_back(dummyStart);
}

void Schedule::assignDummyEnd() {

	this->dummyEnd = Job(Schedule::END_DUMMY_JOB_ID, 0, 0, Schedule::END_DUMMY_JOB_NAME);

	for (auto& job : this->jobs) {

		bool predecessor = false;

		for (auto& job2 : this->jobs)
			if (job2 != job)
				if (job2.hasPredecessor(job))
					predecessor = true;

		if (!predecessor)
			this->dummyEnd.predecessors.push_back(job);
	}

	jobs.push_back(this->dummyEnd);	
}

void Schedule::compile() {

	this->graph.clear();

	std::map<int, size_t> jobVerticeMap;

	for (auto& job : this->jobs) {
	
		auto itJobVerticeMap = jobVerticeMap.find(job.id);

		if (itJobVerticeMap == jobVerticeMap.end()) {
		
			auto v = boost::add_vertex(Stage(job), this->graph);

			std::cout << "Added Vertex(" << job.name << ") " << "(" << v << ")" << std::endl;

			jobVerticeMap.insert(std::make_pair(job.id, v));
		}

		for (auto& predecessor : job.predecessors) {
		
			auto itJobVerticePredecesorMap = jobVerticeMap.find(predecessor.id);

			if (itJobVerticePredecesorMap == jobVerticeMap.end()) {
			
				auto vp = boost::add_vertex(Stage(predecessor), this->graph);

				std::cout << "Added Vertex(" << predecessor.name << ")" << "(" << vp << ")" << std::endl;

				jobVerticeMap.insert(std::make_pair(predecessor.id, vp));
			}

			auto v = jobVerticeMap.at(job.id);
			auto vp = jobVerticeMap.at(predecessor.id);

			std::cout << "Added Edge(" << predecessor.name << "," << job.name << ") con W(" << predecessor.name << ")" << std::endl;

			boost::add_edge(vp, v, Task(static_cast<double>(predecessor.mean * -1.0), predecessor.sd), this->graph);
		}
	}
}

Path Schedule::searchCriticalPath() {

	this->compile();

	/**
	 * At this time we just need this method... However it should replaced by an abstraction.
	 */ 
	
	CPM cpm;
	
	auto path = cpm.searchCriticalPath(*this);

	return path;
}

void Schedule::toFile(const std::string& outputFileName) {

	std::ofstream dep;
	dep.open(outputFileName);

	// File Structures for import in other tools:
    // TODO: Make a Program option to choose application.
	// MS-Project: ID,Name,Start,Duration,Predecesoras
	// Gantt Project (Spanish): ID,Nombre,Fecha de inicio,Duración,Antecesores

    boost::gregorian::date today = boost::gregorian::day_clock::local_day();

	for (auto job : this->jobs) {

		dep << job.id << "," << job.name << boost::gregorian::to_iso_extended_string(today) << job.mean << ",";

		std::size_t index = 1;

		for (auto predecessor : job.predecessors) {
			if (index < job.predecessors.size()) dep << predecessor.id << ";";
			else dep << predecessor.id;
			index++;
		}
		dep << std::endl;
	}

	dep.close();

}