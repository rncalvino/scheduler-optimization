#include "path.h"

Path::Path(const Path& criticalPath) {

	this->jobs = criticalPath.jobs;
}

void Path::operator=(const Path& criticalPath) {

	this->jobs = criticalPath.jobs;
}

void Path::addJob(const Job job) {

	auto itJob = std::find_if(std::begin(this->jobs), std::end(this->jobs), [&job](auto& j) {
		return job.id == j.id;
	});

	if (itJob == std::end(this->jobs)) {
	
		this->jobs.push_back(job);
	}
}

double Path::getDuration() {

	double duration = 0;

	for (auto job : this->jobs)
		duration += job.mean;

	return duration;
}

double Path::getDeviation() {

	double varsum = 0;

	for (auto job : this->jobs)
		varsum += std::pow(job.sd, 2);

	double standarDeviation = std::sqrt(varsum);

	return standarDeviation;
}

int Path::getConfidence() {
	return Path::DEVIATIONS == 1 ? 68
		  : Path::DEVIATIONS == 2 ? 95 
		  : Path::DEVIATIONS == 3 ? 99 : 100;
}

std::pair<double, double> Path::getConfidenceInterval() {

	double duration = this->getDuration();
	double deviation = this->getDeviation();

	auto ic = std::make_pair<double, double>(0, 0);
	ic.first = duration - Path::DEVIATIONS * deviation;
	ic.second = duration + Path::DEVIATIONS * deviation;
	return ic;
}

void Path::toStatsFile(const std::string& outputFileName) {

	std::ofstream csv(outputFileName);

	if (csv.good()) {

		double index = 1;
		double mean = this->getDuration();
		double sd = this->getDeviation();
		double Fm = 0;
		double Fr = 0;

		csv << "Order,Job,Mean,StandardDeviation,F(m),Fr,fr" << std::endl;

		for (auto &job : this->jobs) {

			Fm += job.mean;
			Fr += job.mean / mean;

			csv << std::fixed
				<< std::setprecision(2) 
				<< index << ","
				<< job.name << ","
				<< job.mean << ","
				<< job.sd << ","
				<< Fm << ","
				<< Fr << ","
				<< job.mean / mean << std::endl;

			++index;
		}

		csv << 0 << ","
			<< "Total" << ","
			<< mean << ","
			<< sd << ","
			<< Fm << ","
			<< Fr << ","
			<< 0 << std::endl;

		csv.close();
	}
}