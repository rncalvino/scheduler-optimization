#ifndef CRITICAL_PATH_OPTION_
#define CRITICAL_PATH_OPTION_

#include <memory>
#include <exception>
#include "option.h"
#include "schedule.h"
#include "path.h"
#include "visualization.h"

class CriticalPathOption {

public:

    void execute(boost::program_options::variables_map& vm, JobDataSource& ds) {

		Schedule schedule(ds);

		try {
		
			auto criticalPath = schedule.searchCriticalPath();

			std::cout << "Critical Path found: " << std::endl;

			for (auto& job : criticalPath.jobs)
				std::cout << job.name << "," << job.mean << "," << job.sd << std::endl;

			boost::format fmt("%.2f");
			std::pair<double, double> interval = criticalPath.getConfidenceInterval();
			std::cout << "Interval [" << boost::str(fmt % interval.first) << ", " << boost::str(fmt % interval.second) << "] min. (Confidence Level=" << criticalPath.getConfidence() << "%)" << std::endl;
			std::cout << "Mean: " << boost::str(fmt % criticalPath.getDuration()) << " min. Standard Deviation: " << boost::str(fmt % criticalPath.getDeviation()) << " min." << std::endl;
			std::cout << "Processing time: " << criticalPath.elapsedTime << " seconds." << std::endl;

			if (!vm["StatisticsFile"].empty()) {
				std::cout << "Generating Statistics file..." << std::endl;
				criticalPath.toStatsFile(vm["StatisticsFile"].as<std::string>());
				std::cout << "Statistics file generated. " << std::endl;
			}

		    if(!vm["ImageName"].empty() && !vm["ImageType"].empty()) {
    			std::cout << "Generating graphics..." << std::endl;
				Visualization visualization;
				visualization.schedule(schedule, vm["ImageName"].as<std::string>(), vm["ImageType"].as<std::string>());
		    	std::cout << "Graphics generated." << std::endl;
		    }            

		} catch(std::exception& e) {

			std::cout << "Unable to compute the Critical Path. Error: " << e.what() << std::endl;
		}
    }
};

#endif