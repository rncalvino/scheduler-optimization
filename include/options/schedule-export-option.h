#ifndef SCHEDULER_EXPORT_OPTION_
#define SCHEDULER_EXPORT_OPTION_

#include <memory>
#include "option.h"
#include "schedule.h"

class ScheduleExportOption {

public:

    void execute(boost::program_options::variables_map& vm, JobDataSource& ds) {

		Schedule schedule(ds);

        std::cout << "Creating Schedule file. " << std::endl;
        schedule.toFile(vm["JobsFileToStandard"].as<std::string>());
        std::cout << "Schedule file created. " << std::endl;
    }
};

#endif
