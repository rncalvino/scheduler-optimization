#ifndef CRITICAL_PATH_CSV_OPTION_
#define CRITICAL_PATH_CSV_OPTION_

#include <memory>
#include "datasource/datasource-csv.h"
#include "critical-path-option.h"

class CriticalPathCSVOption : public Option {

public:

    bool shouldActivate(boost::program_options::variables_map& vm) {

        return !vm["JobsFile"].empty() && vm["JobsFileFormat"].as<std::string>() == "csv" ;
    }

    void activate(boost::program_options::variables_map& vm) {

      std::unique_ptr<JobDataSource> ds = std::make_unique<DatasourceCSV>();
      ds->setOption("JobsFile", vm["JobsFile"].as<std::string>());

      CriticalPathOption option;
      option.execute(vm, *ds);
    }
};

#endif
