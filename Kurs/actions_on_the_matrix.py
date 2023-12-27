class IncidenceMatrix:
    def __init__(self, vertex_list, adjacency_matrix):
        self.vertex_list = vertex_list
        self.adjacency_matrix = adjacency_matrix
        self.incidence_matrix = self.create_incidence_matrix()

    def create_incidence_matrix(self):
        incidence_matrix = []
        for i in range(len(self.vertex_list)):
            row = []
            for j in range(len(self.adjacency_matrix)):
                if self.adjacency_matrix[i][j] != 0:
                    row.append(1)
                else:
                    row.append(0)
            incidence_matrix.append(row)
        return incidence_matrix

    def print_incidence_matrix(self):
        print("Матрица инцидентности :")
        for row in self.incidence_matrix:
            print(row)


class Adjacency_list:
    def __init__(self, vertex_list, adjacency_matrix):
        self.vertex_list = vertex_list
        self.adjacency_matrix = adjacency_matrix
        self.adjacency_list = self.create_adjacency_list()

    def create_adjacency_list(self):
        adjacency_list = {}
        for i in range(len(self.vertex_list)):
            vertex = self.vertex_list[i]
            adjacency_list[vertex] = []
            for j in range(len(self.adjacency_matrix[i])):
                if self.adjacency_matrix[i][j] != 0:
                    adjacency_list[vertex].append(self.vertex_list[j])

        return adjacency_list

    def print_adjacency_list(self):
        print("Список смежности на основе списка всех вершин и матрицы смежности:")
        for vertex, neighbors in self.adjacency_list.items():
            print(f"{vertex}: {neighbors}")
