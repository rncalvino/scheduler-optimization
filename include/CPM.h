#ifndef CPM_H_
#define CPM_H_

#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/format.hpp>
#include <chrono>
#include <future>

#include "job.h"
#include "schedule.h"
#include "path.h"

class Schedule;

class CPM {

	public:
		Path searchCriticalPath(Schedule&);
};

#endif