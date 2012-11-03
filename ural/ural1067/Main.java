import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
    public static void main(String args[]) {
        (new Solver()).solve(); 
    }
}

class Solver {
    Node root;
    void insert(String[] path) {
        Node now = root;
        for (String name: path) {
            boolean found = false;
            for (Node t: now.subNodes) {
                if (name.compareTo(t.name) == 0) {
                    found = true;
                    now = t;
                    break;
                }
            }
            if (!found) {
                Node t = new Node(name);    
                now.subNodes.add(t);
                now = t;
            }
        }
    }
    void print(int depth, Node now) {
        if (now != root) {
            for (int i = 0; i < depth; ++i) 
                System.out.print(" ");
            System.out.println(now.name);
        }
        Collections.sort(now.subNodes);
        for (Node t: now.subNodes)
            print(depth + 1, t);
    }
    void solve() {
        root = new Node(null);
        Scanner cin =new Scanner(System.in);
        int N = cin.nextInt();
        for (int i = 0; i < N; ++i) {
            String pathString = cin.next();
            String[] path = pathString.split("\\\\");
            insert(path);
        }
        print(-1, root);
    }
}

class Node implements Comparable<Node> {
    String name; ArrayList<Node> subNodes;
    Node(String name) {
        this.name = name; 
        subNodes = new ArrayList<Node>();
    }
    public int compareTo(Node t) {
        return name.compareTo(t.name); 
    }
}
