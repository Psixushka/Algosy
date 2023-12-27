#from deque import Deque as deque
from collections import deque


class GraphTraversal:
    def __init__(self, graph):
        self.graph = graph
        self.visited = set()

    def iterative_dfs(self, start):
        path = []
        stack = [start]

        while stack:
            v = stack.pop()
            if v not in self.visited:
                path.append(v)
                self.visited.add(v)
                stack.extend([node for node in self.graph[v] if node not in self.visited])
        return path

    def bfs(self, start_node):
        visited = []
        queue = deque([start_node])
        while queue:
            vertex = queue.popleft()
            if vertex not in visited:
                visited.append(vertex)
                queue.extend(set(self.graph[vertex]) - set(visited))
        return visited
