# Courses

A group of courses in university can be described as an oriented graph, where each course is a vertex and there is an edge from course A to course B, if knowledge from course A is required to start the course B. Your program should support 2 modes:

Design - Your program receives a n and m, number of courses and dependencies correspondingly. On next n lines your program receives course names. After that, next m lines your program receives two course names A B, describing the dependency of course B from course A (i.e. oriented edge from A to B). After that, your program should output courses in some order so that they can be completed without breaking any knowledge dependencies. If it’s impossible (i.e. there is a dependency cycle) your program should print that and exit. If the sorting was possible, your program should continue waiting for an input: new inputs will start with new course name A and number of new edges k. The following k lines will describe the new edges (the edges can be both incoming and outgoing). If the new course introduces a cycle, your program should print information about that and ignore that new course, otherwise the new sorting order for courses should be printed. All steps should have O(n + m) time complexity


Analyze -  Your program receives a n and m, number of courses and dependencies correspondingly. On next n lines your program receives course names. After that, next m lines your program receives two course names A B, describing the dependency of course B from course A (i.e. oriented edge from A to B). The courses and dependencies have a very messy design so they contain a lot of dependencies. Your program should determine and print dependency components (i.e. components where each course depends on others). The check should have O(n + m) time complexity

Requirements: Use Topological sorting and Strongly connected components algorithms. Use std::unordered_map<std::string, int> to map course names to vertex numbers.
