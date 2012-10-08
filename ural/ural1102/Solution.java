import java.math.*;
import java.io.*;
import java.util.*;

public class Solution {
    public static void main(String args[]) throws IOException {
        (new Solver()).solve();
    }
}

class Solver {

    DFA constructDFA() {
        String[] dic = {"out", "output", "puton", "in", "input", "one"};
        Trie nfa = new Trie();
        for (String word: dic) 
            nfa.insert(word); 
        DFA dfa = new DFA(nfa);
        return dfa;
    }

    void solve() throws IOException {
        InputReader in = new InputReader(System.in);
        PrintWriter out = new PrintWriter(System.out);
        int N = in.getNumber();
        DFA dfa = constructDFA();
        for (int i = 0; i < N; ++i) {
            if (dfa.travel(in)) out.println("YES");
            else out.println("NO");
        }
        in.close(); out.close();
    }
}

class Trie {
    Node root;
    int size;
    List<Node> idx;
    Trie() {
        size = 0;
        root = new Node(size++);
        idx = new ArrayList<Node>();
        idx.add(root);
    }
    void insert(String str) {
        char[] s = str.toCharArray();
        Node now = root; 
        for (char c: s) {
            if (now.succ[c - 'a'] != null) {
                now = now.succ[c - 'a'];
            }
            else {
                now = now.succ[c - 'a'] = new Node(size++);
                idx.add(now);
            }
        }
        now.accept = true;
    }
}

class DFA {
    Node start;
    HashMap<Integer, Node> map;
    void dfs(int id, Trie nfa) {
        Node node = map.get(id); 
        for (int k = 0; k < nfa.size; ++k)
            if ((((id >> k) & 1) == 1) && nfa.idx.get(k).accept)
                node.accept = true;
        for (int c = 0; c < 26; ++c) {
            int nxt = 0;
            for (int k = 0; k < nfa.size; ++k)
                if (((id >> k) & 1) == 1) {
                    if (nfa.idx.get(k).succ[c] != null)
                        nxt |= (1 << (nfa.idx.get(k).succ[c].id));
                    if (nfa.idx.get(k).accept && nfa.root.succ[c] != null)
                        nxt |= (1 << (nfa.root.succ[c].id));
                }
            if (nxt != 0) {
                if (!map.containsKey(nxt)) {
                    Node nxtNode = new Node(nxt);
                    map.put(nxt, nxtNode);
                    node.succ[c] = nxtNode;
                    dfs(nxt, nfa);
                }
                else node.succ[c] = map.get(nxt);
            }
        }
    }
    DFA(Trie nfa) {
        int startID = (1 << nfa.root.id);
        start = new Node(startID); 
        map = new HashMap<Integer, Node>();
        map.put(startID, start); 
        dfs(startID, nfa);
    }
    boolean travel(InputReader in) throws IOException {
        Node now = start;
        char c;
        boolean flag = true;
        while (!Character.isLowerCase(c = (char)in.nextChar())) {}
        do {
            if (flag && now.succ[c - 'a'] != null) 
                now = now.succ[c - 'a'];
            else flag = false;
        } while (Character.isLowerCase(c = (char)in.nextChar()));
        return flag && now.accept;
    }
}

class Node {
    Node[] succ;
    boolean accept;
    int id;
    Node(int id) {
        succ = new Node[26];
        for (int i = 0; i < 26; ++i)
            succ[i] = null;
        accept = false;
        this.id = id;
    }
}

class InputReader {
    BufferedReader reader;

    InputReader(InputStream in) {
        reader = new BufferedReader(new InputStreamReader(in));
    }

    int getNumber() throws IOException {
        String number = reader.readLine();
        return Integer.parseInt(number);
    }

    int nextChar() throws IOException {
        return reader.read();
    }

    void close() throws IOException {
        reader.close();
    }

}
