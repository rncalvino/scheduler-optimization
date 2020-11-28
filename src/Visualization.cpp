#include "visualization.h"

Visualization::Visualization() {

}

Visualization::~Visualization() {

}

bool Visualization::schedule(Schedule& schedule, const std::string& imageName, const std::string& imageType) {

    this->dot(schedule, imageName);
    this->image(imageName, imageType);

	return true;
}

bool Visualization::dot(Schedule& schedule, const std::string& imageName) {

    std::ofstream dot_file(imageName + ".dot");
    write_graphviz(dot_file, schedule.graph, NodeWriter(schedule), EdgeWriter(schedule));

    return true;
}

bool Visualization::image(const std::string& imageName, const std::string& imageType) {
    std::string dotFile(imageName + ".dot");
    GVC_t* gvc = gvContext();
    FILE* fp = fopen(dotFile.c_str(), "r");
    Agraph_t* g = agread(fp, 0);
    gvLayout(gvc, g, "dot");
    gvRender(gvc, g, imageType.c_str(), fopen((imageName + "." + imageType).c_str(), "w"));
    gvFreeLayout(gvc, g);
    agclose(g);
    remove(dotFile.c_str());
    return (gvFreeContext(gvc));
}