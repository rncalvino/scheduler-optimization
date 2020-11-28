#include <memory>
#include <iostream>
#include <boost/program_options.hpp>
#include "tools/compiler.h"
#include "options/option.h"
#include "options/critical-path-csv-option.h"
#include "options/critical-path-opc-option.h"
#include "options/schedule-export-csv-option.h"
#include "options/schedule-export-opc-option.h"

int main(int argc, char **argv) {

	boost::program_options::options_description config("Options");
	config.add_options()
		("JobsFileFormat,F", boost::program_options::value<std::string>(), "Schedule File Format (csv|opc).")
		("JobsFile,f", boost::program_options::value<std::string>(), "Schedule File.")
		("ImageName,i", boost::program_options::value<std::string>(), "Image name.")
		("ImageType,t", boost::program_options::value<std::string>()->default_value("svg"), "Image Type.")
		("StatisticsFile,s", boost::program_options::value<std::string>(), "Statistics File.")
		("JobsFileToStandard,p", boost::program_options::value<std::string>(), "Convert the jobs file to a standard job file.");

	boost::program_options::variables_map vm;
	boost::program_options::store(boost::program_options::parse_command_line(argc, argv, config), vm);
	boost::program_options::notify(vm);

	std::vector<std::unique_ptr<Option>> options;
	options.push_back(std::make_unique<CriticalPathCSVOption>());
	options.push_back(std::make_unique<CriticalPathOPCOption>());
    options.push_back(std::make_unique<ScheduleExportCSVOption>());
	options.push_back(std::make_unique<ScheduleExportOPCOption>());

	bool found = false;

	for(auto& option : options) {
		if(option->shouldActivate(vm)) {
			option->activate(vm);
			found = true;
		}
	}

	if(!found)
		std::cout << config << std::endl;

	return 0;
}