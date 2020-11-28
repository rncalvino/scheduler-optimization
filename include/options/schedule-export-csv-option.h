#ifndef SCHEDULER_EXPORT_CSV_OPTION_
#define SCHEDULER_EXPORT_CSV_OPTION_

#include <memory>
#include "option.h"
#include "schedule.h"
#include "datasource/datasource-csv.h"
#include "schedule-export-option.h"

class ScheduleExportCSVOption : public Option {

public:

    bool shouldActivate(boost::program_options::variables_map& vm) {

        return !vm["JobsFileToStandard"].empty() 
            && !vm["JobsFile"].empty()
            && !vm["JobsFileFormat"].empty()
            && vm["JobsFileFormat"].as<std::string>() == "csv" ;
    }

    void activate(boost::program_options::variables_map& vm) {

		std::unique_ptr<JobDataSource> ds = std::make_unique<DatasourceCSV>();
		ds->setOption("JobsFile", vm["JobsFile"].as<std::string>());
        
		ScheduleExportOption option;
        option.execute(vm, *ds);
    }
};

#endif