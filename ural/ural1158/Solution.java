import java.math.*;
import java.io.*;
import java.util.*;

public class Solution {

    public static void main(String args[]) throws IOException {
        (new Solver()).solve();
    }

}

class Solver {

    int N, M, P;
    char[] alphabet;
    HashMap<Character, Integer> map;
    BigInteger[][] f;

    void solve() throws IOException {

        InputReader in = new InputReader(System.in); 
        PrintWriter out = new PrintWriter(System.out);

        N = in.nextInt(); M = in.nextInt(); P = in.nextInt();
        alphabet = in.nextToken().toCharArray();
        map = new HashMap<Character, Integer>();
        for (int i = 0; i < N; ++i)
            map.put(alphabet[i], i);
        DFA dfa = new DFA(N);
        for (int i = 0; i < P; ++i) {
            String word = in.nextToken();
            dfa.insert(word, map);
        }
        dfa.construct();
        BigInteger ans = dp(M, dfa);
        out.println(ans);

        in.close(); 
        out.close();

    }

    BigInteger dp(int length, DFA dfa) {

        int dfaSize = dfa.size;
        int start = dfa.root.id;
        int alphabetSize = dfa.alphabetSize;
        f = new BigInteger[length + 1][dfaSize];    

        for (int i = 0; i <= length; ++i)
            for (int j = 0; j < dfaSize; ++j)
                f[i][j] = BigInteger.ZERO;
        f[0][start] = BigInteger.ONE;

        for (int i = 0; i < length; ++i)
            for (int j = 0; j < dfaSize; ++j)
                for (int k = 0; k < alphabetSize; ++k) {
                    Node nxt = dfa.idx.get(j).succ[k];
                    if (!nxt.accept) {
                        f[i + 1][nxt.id] = f[i + 1][nxt.id].add(f[i][j]);
                    }
                }

        BigInteger ans = BigInteger.ZERO;
        for (int j = 0; j < dfaSize; ++j)
            ans = ans.add(f[length][j]);
        return ans;

    }

}

class DFA {

    int alphabetSize;
    int size;
    Node root;
    ArrayList<Node> idx;

    DFA(int alphabetSize) {
       this.alphabetSize = alphabetSize; 
       size = 0;
       root = new Node(alphabetSize, size++);
       idx = new ArrayList<Node>();
       idx.add(root);
    }

    void insert(String str, HashMap<Character, Integer> map) {
        char[] s = str.toCharArray();
        Node now = root;
        for (char c: s) {
            int id = map.get(c);        
            if (now.succ[id] != null)
                now = now.succ[id];
            else {
                now = now.succ[id] = new Node(alphabetSize, size++);
                idx.add(now);
            }
        }
        now.accept = true;
    }

    void construct() {
        LinkedList<Node> queue = new LinkedList<Node>(); 
        queue.add(root); 
        while (!queue.isEmpty()) {
            Node now = queue.remove();
            for (int i = 0; i < alphabetSize; ++i) {
                if (now.succ[i] == null) {
                    if (now == root) now.succ[i] = root; 
                    else now.succ[i] = now.next.succ[i];
                }
                else {
                    queue.add(now.succ[i]);
                    if (now == root) now.succ[i].next = root;
                    else {
                        now.succ[i].next = now.next.succ[i];
                        now.succ[i].accept = now.succ[i].accept || now.next.succ[i].accept;
                    }
                }
            }
        }
    }

}

class Node {

    Node[] succ;
    Node next;
    boolean accept;
    int id;

    Node(int alphabetSize, int id) {
        succ = new Node[alphabetSize];
        for (int i = 0; i < alphabetSize; ++i)
            succ[i] = null;
        this.id = id;
        accept = false;
        next = null;
    }

}

class InputReader {

    BufferedReader reader;
    StringTokenizer tokenizer;

    InputReader(InputStream in) {
        reader = new BufferedReader(new InputStreamReader(in));
        tokenizer = new StringTokenizer("");
    }

    int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    String nextToken() throws IOException {
        while (!tokenizer.hasMoreTokens())
            tokenizer = new StringTokenizer(reader.readLine());
        return tokenizer.nextToken();
    }

    void close() throws IOException {
        reader.close();
    }

}
