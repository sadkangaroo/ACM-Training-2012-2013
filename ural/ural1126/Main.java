import java.util.*;
import java.io.*;
import java.math.*;

public class Main {
    public static void main(String[] args) throws IOException {
        (new Solver()).solve();
    }
}

class Solver {

    static final int MaxN = 25000;

    InputReader in;
    PrintWriter out;
    TreeMap<Integer, Integer> map;

    int[] number = new int[MaxN + 5];

    void add(TreeMap<Integer, Integer> map, int x) {
        if (map.containsKey(x)) map.put(x, map.get(x) + 1);
        else map.put(x, 1);
    }

    void remove(TreeMap<Integer, Integer> map, int x) {
        int t = map.get(x) - 1;
        if (t == 0) map.remove(x);
        else map.put(x, t);
    }

    void solve() throws IOException {
        in = new InputReader(System.in);
        out = new PrintWriter(System.out);
        int M = in.nextInt();
        map = new TreeMap<Integer, Integer>();
        int x;
        for (int i = 1; ; ++i) {
            x = number[i] = in.nextInt();
            if (x == -1) break;
            add(map, x);
            if (i > M) remove(map, number[i - M]);
            if (i >= M) out.println(map.lastKey());
        }
        in.close(); out.close();
    }
}

class InputReader {
    BufferedReader reader;
    StringTokenizer tokenizer;
    InputReader(InputStream in) throws IOException {
        reader = new BufferedReader(new InputStreamReader(in));
        tokenizer = new StringTokenizer("");
    }
    String nextToken() throws IOException {
        while (!tokenizer.hasMoreTokens()) 
            tokenizer = new StringTokenizer(reader.readLine());
        return tokenizer.nextToken();
    }
    int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }
    void close() throws IOException {
        reader.close();
    }
}

