#ifndef DATASOURCE_CSV_
#define DATASOURCE_CSV_

#include <sstream>
#include <vector>
#include "job.h"
#include "parser.h"
#include "datasource.h"

class DatasourceCSV : public JobDataSource {

public:
	std::vector<Job> getJobs() const {

		std::map<int, Job> jobsMap;
		std::map<int, std::vector<int>> predecessorsMap;

		std::ifstream f(this->options.at("JobsFile"));

		aria::csv::CsvParser parser = aria::csv::CsvParser(f)
			.delimiter(';')   
			.terminator('\n');

		/** 
		 * Itereate through the CSV file and create each Job.
		 */

		std::string predecessorToken;

		for (auto csv : parser) {
			Job job;
			job.id = std::stoi(csv.at(0));
			job.name = csv.at(1);
			job.mean = std::stod(csv.at(3));
			job.sd = std::stod(csv.at(4));

			std::stringstream ss(csv.at(2));

			while(std::getline(ss, predecessorToken, ',')) {
				if(!predecessorsMap.count(job.id))
					predecessorsMap.insert(std::make_pair<int, std::vector<int>>(std::stoi(csv.at(0)), {}));
				predecessorsMap[job.id].push_back(std::stoi(predecessorToken));
			}

			jobsMap.insert(std::make_pair(job.id, job));
		}

		/**
		* Iterate throgh the predecessorMap and assign predecessor.
		*/
		
		for (auto it = std::begin(predecessorsMap); it != std::end(predecessorsMap); ++it)
			for(auto predecessor : it->second)
				jobsMap[it->first].addPredecessor(jobsMap[predecessor]);

		/**
		 * Move map values to a vector.
		 */

		std::vector<Job> jobs;
		for(auto it = std::begin(jobsMap); it != std::end(jobsMap); ++it)
			jobs.push_back(std::move(it->second));

		return jobs;
	}
};

#endif