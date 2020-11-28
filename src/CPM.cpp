#include "CPM.h"

Path CPM::searchCriticalPath(Schedule& schedule) {

	std::size_t vstart = 0, vend = 0;

	for(auto i = std::size_t(0); i < boost::num_vertices(schedule.graph); ++i) {
		if(schedule.graph[i].job.id == schedule.dummyStart.id)
			vstart = i;
		else if(schedule.graph[i].job.id == schedule.dummyEnd.id)
			vend = i;
	}

	std::vector<std::size_t> predecessors(boost::num_vertices(schedule.graph));
	std::vector<decltype(Task::media)> distances(boost::num_vertices(schedule.graph));
	std::fill(std::begin(distances), std::end(distances), static_cast<double>(9999999999));
	distances[vstart] = 0;
	
	std::cout << "Critical path search started." << std::endl;

	auto startTime = std::chrono::system_clock::now();

	bool resultado = boost::bellman_ford_shortest_paths(schedule.graph, num_vertices(schedule.graph),
		boost::weight_map(boost::get(&Task::media, schedule.graph))
		.predecessor_map(
			boost::make_iterator_property_map(predecessors.begin(),
				boost::get(boost::vertex_index, schedule.graph)))
		.distance_map(
			boost::make_iterator_property_map(distances.begin(),
				boost::get(boost::vertex_index, schedule.graph))
		)
	);

	auto endTime = std::chrono::system_clock::now();

	std::cout << "Critical path search ended." << std::endl;

	if (!resultado)
		throw std::logic_error("Unable to compute the critical path.");

	std::vector<Graph::edge_descriptor> pathFromStartToEnd;

	auto vendAux = vend;
	for (auto vcurrent = predecessors[vendAux]; vcurrent != vendAux; vendAux = vcurrent, vcurrent = predecessors[vendAux]) {
		auto edgePair = boost::edge(vcurrent, vendAux, schedule.graph);
		pathFromStartToEnd.push_back(edgePair.first);
	}

	Path criticalPath;
	criticalPath.elapsedTime = static_cast<long>(std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count());

	for (auto it = pathFromStartToEnd.rbegin(); it != pathFromStartToEnd.rend(); ++it) {
		auto src = boost::source(*it, schedule.graph);
		auto dst = boost::target(*it, schedule.graph);
		schedule.graph[*it].critic = true;
		schedule.graph[src].critic = true;
		schedule.graph[dst].critic = true;
		criticalPath.addJob(schedule.graph[src].job);
		criticalPath.addJob(schedule.graph[dst].job);			
	}

	return criticalPath;
}
