#ifndef GENERATE_DOT_FILE
#define GENERATE_DOT_FILE

#include "Graph.h"
#include "MyString.h"

void GenerateDOTFileDouble(Graph<double, double> const & graph, MyString graphName, Path<double, double> const & path = Path<double, double>());

#endif //GENERATE_DOT_FILE
