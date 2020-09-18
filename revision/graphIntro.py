# representing the edge through this class
class Edge:
    def __init__(self,v,w): # to initialise the edge
        self.v = v # it repersent the target vertex
        self.w = w # it represent the weight of the edge

graph = [[] for i in range(7)]

def addEdge(gp,u,v,w):
    gp[u].append(Edge(v,w))
    gp[v].append(Edge(u,w))

def display(gp):
    for i in range(len(gp)):
        print(str(i)+" -> ",end="")
        for e in gp[i]:
            print("("+str(e.v)+","+str(e.w)+") ",end="")
        print()

def createGraph():
    addEdge(graph,0,1,10)
    addEdge(graph,0,3,10)
    addEdge(graph,1,2,10)
    addEdge(graph,2,3,40)
    addEdge(graph,3,4,2)
    addEdge(graph,4,5,2)
    addEdge(graph,4,6,3)
    addEdge(graph,5,6,8)
    display(graph)

if __name__ == "__main__":
    createGraph()
    # print(graph)

