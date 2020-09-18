import java.util.ArrayList;

public class graphIntro {
    public static void main(String[] args){
        solve();
    }
    // class to represent the edge between two vertex
    public static class Edge{
        int v; // it stores the target vertex
        int w; // and it stores the weight of the edge

        Edge(int v,int w){ // constructor
            this.v = v; // initialising 
            this.w = w;
        }
    }

    public static int N = 7; // number of vertex in the graph
    public static ArrayList<Edge>[] graph; // graph representation

    public static void createGraph(){
        graph = new ArrayList[N]; // initialising the array of arraylist
        for(int i=0;i<N;i++){
            graph[i] = new ArrayList<>(); // initialising the arraylist in the array
        }
        addEdge(graph,0,1,10);
        addEdge(graph,0,3,10);
        addEdge(graph,1,2,10);
        addEdge(graph,2,3,40);
        addEdge(graph,3,4,2);
        addEdge(graph,4,5,2);
        addEdge(graph,4,6,3);
        addEdge(graph,5,6,8);

        display(graph);
    
    }

    // function to print the graph
    public static void display(ArrayList<Edge>[] gp){
        for(int i=0;i<gp.length;i++){
            System.out.print(i+" -> ");
            for(Edge e:gp[i]){
                System.out.print("("+e.v+","+e.w+") ");
            }
            System.out.println();
        }
        System.out.println();
    }

    // function to add the edge in the graph
    public static void addEdge(ArrayList<Edge>[] gp,int u,int v,int w){
        gp[u].add(new Edge(v,w)); // adding edge from u to v
        gp[v].add(new Edge(u,w)); // adding edge from v to u
    }

    public static void solve(){
        createGraph();
    }
}