#ifndef CRITICAL_PATH_OPC_OPTION_
#define CRITICAL_PATH_OPC_OPTION_

#include <memory>
#include "option.h"
#include "critical-path-option.h"
#include "datasource/datasource-opc.h"

class CriticalPathOPCOption : public Option {

public:

    bool shouldActivate(boost::program_options::variables_map& vm) {

        return !vm["JobsFile"].empty() && vm["JobsFileFormat"].as<std::string>() == "opc" ;
    }

    void activate(boost::program_options::variables_map& vm) {

        std::unique_ptr<JobDataSource> ds = std::make_unique<DatasourceOPC>();
		ds->setOption("JobsFile", vm["JobsFile"].as<std::string>());

		CriticalPathOption option;
		option.execute(vm, *ds);
	}
};

#endif