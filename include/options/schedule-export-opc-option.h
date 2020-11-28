#ifndef SCHEDULER_EXPORT_OPC_OPTION_
#define SCHEDULER_EXPORT_OPC_OPTION_

#include <memory>
#include "option.h"
#include "schedule.h"
#include "datasource/datasource-opc.h"
#include "schedule-export-option.h"

class ScheduleExportOPCOption : public Option {

public:

    bool shouldActivate(boost::program_options::variables_map& vm) {

        return !vm["JobsFileToStandard"].empty() 
            && !vm["JobsFile"].empty()
            && !vm["JobsFileFormat"].empty()
            && vm["JobsFileFormat"].as<std::string>() == "opc" ;
    }

    void activate(boost::program_options::variables_map& vm) {

		std::unique_ptr<JobDataSource> ds = std::make_unique<DatasourceOPC>();
		ds->setOption("JobsFile", vm["JobsFile"].as<std::string>());
        
		ScheduleExportOption option;
        option.execute(vm, *ds);
    }
};

#endif