#ifndef VISUALIZATION_H_
#define VISUALIZATION_H_

#include <iostream>
#include <cstdio>
#include <graphviz/gvc.h>

#include "path.h"
#include "schedule.h"

struct NodeWriter {
	NodeWriter(Schedule& s_) : s(s_) {};
	template <class Stage>
	void operator()(std::ostream& out, Stage v) {
		out << " [label=\"" << s.graph[v].label() << "\",fontcolor=\"white\",color=\"" << (s.graph[v].critic ? "#a82814" : "#4c6e2a") << "\"]";
	}
	Schedule s;
};

struct EdgeWriter {
	EdgeWriter(Schedule& s_) : s(s_) {};
	template <class Task>
	void operator()(std::ostream& out, Task e) {
		out << " [label=\"" << s.graph[e].label() << "\",fontcolor=\"white\",color=\"" << (s.graph[e].critic ? "#a82814" : "#4c6e2a") << "\"]";
	}
	Schedule s;
};

struct GraphWriter {
	GraphWriter() { }
	GraphWriter(Path c_) : c(c_) { }
	void operator()(std::ostream& out) {
		std::pair<double, double> interval = this->c.getConfidenceInterval();
		boost::format fmt("%.2f");
		out << "graph [rankdir=\"LR\",labelloc=\"t\",labeljust=\"center\",fontsize=\"16\",labelcolor=\"white\",fontcolor=\"white\",bgcolor=\"#dddddd\",";
		out << "label=\"Critical Path Duration: " + boost::str(fmt % c.getDuration()) << "hs. Interval [" << boost::str(fmt % interval.first) << ", " << boost::str(fmt % interval.second) << "] hs. (Confidence Level=95%)\"]" << std::endl;
	}
	Path c;
};

class Schedule;

class Visualization {

public:
	Visualization();
	~Visualization();
	bool schedule(Schedule&, const std::string& imageName, const std::string& imageType);

private: 
    bool dot(Schedule& schedule, const std::string& imageName);
    bool image(const std::string& imageName, const std::string& imageType);
};

#endif