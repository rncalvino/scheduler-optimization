# Scheduler Optimization

Computes the critical path of the scheduled jobs. Generates statistics and visualizations.

Assumptions: This project model jobs/tasks using random variables of the normal distribution. 

## Requirements:

 - VS140 or VS142 or GCC 7.3.
 - CMake
 - Boost C++ 1.67.0 or newer.
 - Graphviz 2.38 libs.
 - CSV Parser (AriaFallah)
  
## Input available formats:

### CSV Format (Standard file)

Order | Description
----- | -----------
0     | ID
1     | JOB
2     | PREDECESSORS (comma separated list)
3     | MEAN
4     | STANDARD DEVIATION

### CSV Format (OPC Workload Schedule)

Order | Description
----- | -----------
0     | ROW NUMBER
1     | APPLICATION
2     | RESOURCE INTERNAL ORDER
3     | JOB
4     | RESOURCE TYPE
5     | INTERNAL ORDER
6     | EXTERNAL RESOURCE
7     | EXTERNAL RESOURCE APPLICATION NAME
8     | EXTERNAL RESOURCE ORDER
9     | MEAN
10    | STANDARD DEVIATION
