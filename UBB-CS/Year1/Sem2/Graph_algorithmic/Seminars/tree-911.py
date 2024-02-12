import copy
from heapq import heappush, heappop

class UndirectedGraph:
    def __init__(self, vertices):
        self.vertices = dict()
        for i in vertices:
            self.vertices[i] = set()
        
    def add_edge(self, x, y):
        self.vertices[x].add(y)
        self.vertices[y].add(x)
    
    def is_edge(self, x, y):
        return (y in self.vertices[x])

    def parse_vertices(self):
        vertices_list = list()
        for key in self.vertices:
            vertices_list.append(key)
        return vertices_list
       
    def parse_n(self, x):
        n_vertices = list()
        for y in self.vertices[x]:
            n_vertices.append(y)
        return n_vertices 

def print_graph(g):
    print("Neighborss:")
    for x in g.parse_vertices():
        s = str(x) + ":"
        for y in g.parse_n(x):
            s = s + " " + str(y)
        print(s)

def create_graph_and_cost():
    g = UndirectedGraph(range(1,7))
    cost1 = {
        (1,2): 3,
        (1,3): 2,
        (1,4): 4,
        (2,3): 2,
        (2,6): 1,
        (3,4): 4,
        (3,5): 3,
        (3,6): 2,
        (4,5): 5,
        (5,6): 5,
    }
    cost = {}
    for edge in cost1.keys():
        g.add_edge(edge[0], edge[1])
        cost[edge] = cost1[edge]
        cost[(edge[1], edge[0])] = cost1[edge]
    return g, cost

def prim(g, cost):
    '''Constructs the min. tree from the given graph and costs.
    Returns a list of pairs of vertices representing the edges of the tree
    '''
    tree_edges = []
    tree_vertices = set()
    for x in g.parse_vertices():
        start_vertex = x
        break
    tree_vertices.add(start_vertex)
    q = []

    for x in g.parse_n(start_vertex):
        heappush(q, (cost[start_vertex,x] , start_vertex, x))
    while len(q) > 0:
        _, tree_vertex, outside_vertex = heappop(q)
        if outside_vertex in tree_vertices:
            continue
        tree_vertices.add(outside_vertex)
        tree_edges.append((tree_vertex, outside_vertex))
        for x in g.parse_n(outside_vertex):
            if x not in tree_vertices:
                heappush(q, (cost[outside_vertex, x] , outside_vertex, x))
    return tree_edges

class DisjointSets:
    def __init__(self, vertices):
        self.parent = {}
        self.height = {}
        for v in vertices:
            self.parent[v] = None
            self.height[v] = 0
    def checkAndMerge(self, x, y):
        '''If x and y are in the same component, returns False,
        otherwise, joins the components of x and y and returns True
        '''
        rx = self.getRoot(x)
        ry = self.getRoot(y)
        if rx == ry:
            return False
        if self.height[rx] > self.height[ry]:
            self.parent[ry] = rx
        elif self.height[rx] < self.height[ry]:
            self.parent[rx] = ry
        else:
            self.parent[ry] = rx
            self.height[rx] += 1
        return True
        
    def getRoot(self, x):
        while self.parent[x] != None:
            x = self.parent[x]
        return x

def kruskal(g, cost):
    edges = []
    for x in g.parse_vertices():
        for y in g.parse_n(x):
            edges.append((cost[x,y], x, y))
    edges.sort()
    components = DisjointSets(g.parse_vertices())
    tree_edges = []
    for _,x,y in edges:
        if components.checkAndMerge(x, y):
            tree_edges.append((x,y))
    return tree_edges

def test_min_tree():
    g,cost=create_graph_and_cost()
    print(kruskal(g, cost))

test_min_tree()
