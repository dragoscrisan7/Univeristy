import copy
from heapq import heappush, heappop
import random
import time

class Graph:
    def __init__(self, vertices):
        '''vertices = iterable containing the vertices of the graph
        '''
        self.__out = {}
        self.__in = {}
        for x in vertices:
            self.__out[x] = set()
            self.__in[x] = set()
        
    def add_edge(self, x, y):
        self.__out[x].add(y)
        self.__in[y].add(x)
        
    def vertices(self):
        return [x for x in self.__out]
        
    def is_edge(self, x, y):
        return y in self.__out[x]
        
    def out_neighbors(self, x):
        for y in self.__out[x]:
            yield y
        
    def in_neighbors(self, x):
        for y in self.__in[x]:
            yield y
        
    def in_neighbors_bad(self, x):
        for y in self.__out:
            if self.is_edge(y, x):
                yield y
        
def print_graph(g):
    print("Outbounds:")
    for x in g.vertices():
        s = str(x) + ":"
        for y in g.out_neighbors(x):
            s = s + " " + str(y)
        print(s)
    print("Inbounds:")
    for x in g.vertices():
        s = str(x) + ":"
        for y in g.in_neighbors(x):
            s = s + " " + str(y)
        print(s)
    
def parse_graph(g):
    print("Outbounds:")
    start = time.time()
    for x in g.vertices():
        for y in g.out_neighbors(x):
            pass
    print("%sms" % ((time.time() - start)*1000,))
    print("Inbounds:")
    start = time.time()
    for x in g.vertices():
        for y in g.in_neighbors_bad(x):
            pass
    print("%sms" % ((time.time() - start)*1000,))
    
def build_graph():
    lst = [0,1,2,3, 4, 5]
    g = Graph(lst)
    lst.append("something")

    #g = Graph([0,1,2,3])
    for x, y in [(0,0), (0,1), (0,2), (1,2), (2,1), (2,5), (4,2)]:
        g.add_edge(x,y)
    return g

def build_random_graph(n, m):
    g = Graph(range(n))
    while m > 0:
        x = random.randrange(n)
        y = random.randrange(n)
        if not g.is_edge(x, y):
            g.add_edge(x, y)
            m = m - 1
    return g

def build_graph_with_costs():
    nr_vertices = 5
    g = Graph(range(nr_vertices))
    cost = {(0,1):3, (0,2):5, (1,2):1, (2,1):1, (2,3):2, (1,3):4, (3,4):2, (0,4):7}
    for x, y in cost.keys():
        g.add_edge(x,y)
    return g, cost

def build_dag_with_costs():
    nr_vertices = 5
    g = Graph(range(nr_vertices))
    cost = {(0,1):3, (0,2):5, (1,2):1, (2,3):2, (1,3):4, (3,4):2, (0,4):7}
    for x, y in cost.keys():
        g.add_edge(x,y)
    return g, cost

class WolfGoatCabbageGraph:
    def vertices(self):
        pass
        
    def is_edge(self, x, y):
        pass
        
    def out_neighbors(self, x):
        return x.neighbors()
        
    def in_neighbors(self, x):
        return x.neighbors()

    def initial_state(self):
        return WolfGoatCabbageState([False] * 4)

    def final_state(self):
        return WolfGoatCabbageState([True] * 4)

class WolfGoatCabbageState:
    def __init__(self, lst):
        '''lst = a list of size 4 of boolean values. Indexes represent: 0=wokf, 1=goat, 2=cabbage, 3=boat;
        Values represent: False = left bank, True = right bank
        '''
        self.__objects = copy.copy(lst)
    def __str__(self):
        left = []
        right = []
        for i in range(4):
            if self.__objects[i]:
                right.append(self.names[i])
            else:
                left.append(self.names[i])
        return ''.join(left) + '|' + ''.join(right)
    def __repr__(self):
        return self.__str__()
    def __eq__(self, other):
        return isinstance(other, WolfGoatCabbageState) and self.__objects == other.__objects
    def __ne__(self, other):
        return not self.__eq__(other)
    def __hash__(self):
        val = 0
        for obj in self.__objects:
            val = 2*val + (1 if obj else 0)
        return val
    def neighbors(self):
        '''Returns an iterable with all the states reachable within one move of the current state
        '''
        for i in range(4):
            if self.__objects[3] == self.__objects[i]:
                lst = copy.copy(self.__objects)
                lst[3] = not lst[3]
                if i != 3:
                    lst[i] = not lst[i]
                st = WolfGoatCabbageState(lst)
                if st.is_valid():
                    yield st
    def is_valid(self):
        '''Returns True if, in the current state, nobody eats nobody
        '''
        return self.__objects[3] == self.__objects[1] or (
            self.__objects[1] != self.__objects[0] and
            self.__objects[1] != self.__objects[2])
    names = ['W', 'G', 'C', 'B']

def shortest_path(graph, start_vertex, end_vertex):
    '''Finds the shortest (min length) path from start_vertex to end_vertex in the graph 'graph'.
    Returns the list of vertices along the path, strating with start_vertex and ending with end_vertex.
    If start_vertex == end_vertex, it returns [start_vertex]
    If there is no path, returns None.
    If there are multiple optimal paths, returns one of them.
    '''
    parent = bfs(graph, start_vertex)
    if end_vertex not in parent:
        return None
    current = end_vertex
    path = [end_vertex]
    while current != start_vertex:
        current = parent[current]
        path.append(current)
    path.reverse()
    return path

def bfs(graph, start_vertex):
    '''Does a BFS parsing of grapg 'graph', starting from start_vertex.
    Returns a dictionary where the keys are the vertices accessible from start_vertex and the corresponding
    values are their parents in the BFS tree. Parent of start_vertex will be None.
    '''
    parents={}
    queue=[start_vertex]
    index_queue=0
    parents[start_vertex]=None;
    
    while index_queue<len(queue):
        current=queue[index_queue]
        index_queue+=1
        
        for neighbour in graph.out_neighbors(current):
            if neighbour not in parents.keys():
                parents[neighbour]=current
                queue.append(neighbour)
    return parents

def min_cost_path_dijkstra(graph, cost, start_vertex, end_vertex):
    '''Finds the minimun cost path from start_vertex to end_vertex in the graph 'graph'.
    Returns the list of vertices along the path, strating with start_vertex and ending with end_vertex.
    If start_vertex == end_vertex, it returns [start_vertex]
    If there is no path, returns None.
    If there are multiple optimal paths, returns one of them.
    '''
    dist,parent = dijkstra(graph, cost, start_vertex, end_vertex)
    if end_vertex not in parent:
        return None
    print("distance to end_vertex = %s" % (dist[end_vertex],))
    current = end_vertex
    path = [end_vertex]
    while current != start_vertex:
        current = parent[current]
        path.append(current)
    path.reverse()
    return path

def dijkstra(graph, cost, start_vertex, end_vertex=None):
    '''Executes Dijkstra algorithm on the graph 'graph', starting from start_vertex.
    Returns a tuple of two dictionaries, dictionary where the keys are the vertices accessible from start_vertex and the corresponding
    values are the distance from start to that vertex and the previous vertex along the optimal path. Parent of start_vertex will be None.
    '''
    parents={}
    #dist = {x:float('inf') for x in graph.vertices()}
    dist = {}
    dist[start_vertex] = 0
    parents[start_vertex]=None
    queue = []
    heappush(queue, (0, start_vertex))
    
    while len(queue) > 0:
        print(f"queue={queue}")
        current_dist,current=heappop(queue)
        print(f"current={current}, current_dist={current_dist}")
        if current == end_vertex:
            print("Reached the target vertex")
            return dist,parents
        if current_dist > dist[current]:
            print("Skip")
            continue

        for neighbour in graph.out_neighbors(current):
            if neighbour not in dist or dist[neighbour] > dist[current] + cost[(current, neighbour)]:
                dist[neighbour] = dist[current] + cost[(current, neighbour)]
                parents[neighbour]=current
                heappush(queue, (dist[neighbour], neighbour))
        print(f"dist={dist}, parents={parents}")
    return dist,parents

def min_cost_path_dag(graph, cost, start_vertex, end_vertex):
    '''Finds the minimun cost path from start_vertex to end_vertex in the DAG 'graph'.
    Returns the list of vertices along the path, strating with start_vertex and ending with end_vertex.
    If start_vertex == end_vertex, it returns [start_vertex]
    If there is no path, returns None.
    If there are multiple optimal paths, returns one of them.
    '''
    sorted_list = toposort(graph)
    if sorted_list is None:
        print("Not a DAG")
        return None
    dist,parent = parse_dag(sorted_list, graph, cost, start_vertex)
    if end_vertex not in parent:
        return None
    print("distance to end_vertex = %s" % (dist[end_vertex],))
    current = end_vertex
    path = [end_vertex]
    while current != start_vertex:
        current = parent[current]
        path.append(current)
    path.reverse()
    return path
    
def toposort(graph):
    counter = {}
    queue = []
    for x in graph.vertices():
        counter[x] = len(list(graph.in_neighbors(x)))
        if counter[x] == 0:
            queue.append(x)
    sorted_list = []
    while queue:
        x = queue.pop()
        sorted_list.append(x)
        for y in graph.out_neighbors(x):
            counter[y] -= 1
            if counter[y] == 0:
                queue.append(y)
    print(f"sorted_list={sorted_list}")
    if len(sorted_list) == len(counter):
        return sorted_list
    else:
        print(get_cycle(graph, counter))
        return None

def get_cycle(graph, counter):
    '''Finds a cycle in the given graph, using the remaining predecessor counter from a failed topological sorting.
    Returns the cycle as a list of vertices, with the same vartex on the first and last position
    '''
    
    for cr in graph.vertices():
        if counter[cr]!=0:
            vertex=cr
            break
            
    Visited=set()
    Q=[]
    while vertex not in Visited:
        Visited.add(vertex)
        Q.append(vertex)
        
        for neighbour in graph.in_neighbors(vertex):
            if counter[neighbour]!=0:
                vertex=neighbour
                break
                
    Res=[]
    beforeStart=True
    for node in Q:
        if node==vertex:
            beforeStart=False
            
        if not beforeStart:
            Res.append(node)
            
    Res.append(vertex)
    Res.reverse()
    return Res

def parse_dag(sorted_list, graph, cost, start_vertex):
    '''
    Returns a tuple of two dictionaries, dictionary where the keys are the vertices accessible from start_vertex and the corresponding
    values are the distance from start to that vertex and the previous vertex along the optimal path. Parent of start_vertex will be None.
    '''
    parents={}
    dist = {}
    dist[start_vertex] = 0
    parents[start_vertex]=None

    for current in sorted_list:
        print(f"current={current}")
        if current not in dist:
            print("Inaccessible")
            continue

        for neighbour in graph.out_neighbors(current):
            if neighbour not in dist or dist[neighbour] > dist[current] + cost[(current, neighbour)]:
                dist[neighbour] = dist[current] + cost[(current, neighbour)]
                parents[neighbour]=current
        print(f"dist={dist}, parents={parents}")
    return dist,parents

def test_graph():
    n = 10000
    g = build_random_graph(n, 10*n)
    #print_graph(g)
    parse_graph(g)

def test_bfs():
    g = build_graph()
    print(shortest_path(g, 0, 5))

def test_dijkstra():
    g,cost = build_graph_with_costs()
    print(min_cost_path_dijkstra(g, cost, 0, 3))

def test_dag():
    g,cost = build_dag_with_costs()
    print(min_cost_path_dag(g, cost, 0, 3))

def test_wolf_goat_cabbage():
    g = WolfGoatCabbageGraph()
    s = g.initial_state()
    t = g.final_state()
    #print(s, s.__hash__())
    #print(t, t.__hash__())
    #x = WolfGoatCabbageState([True, False, True, False])
    #print(x, x.__hash__())
    #print(s == 1)
    #x = set()
    #x.add(s)
    #x.add(s)
    #x.add(t)
    #print(x)
    print(shortest_path(g, s, t))

def test_find_cycle():
    g,_ = build_graph_with_costs()
    toposort(g)

test_find_cycle()
