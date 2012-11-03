import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
    public static void main(String args[]) throws IOException {
        (new Solver()).solve();
    }
}

class Solver {
    int N, K, label;
    int[] c;
    void insert(int pos) {
        for (int i = pos; i <= N; i += (i & (-i)))
            c[i]++;
    }
    int query(int pos) {
        int res = 0;
        for (int i = pos; i > 0; i -= (i & (-i)))
            res += c[i];
        return res;
    }
    void solve() throws IOException {
        InputReader in = new InputReader(System.in);
        PrintWriter out = new PrintWriter(System.out);
        N = in.nextInt(); K = in.nextInt(); 
        c = new int[N + 1];
        int ans = -1, x;
        for (int k = 1; k <= K; ++k) {
            Arrays.fill(c, 1, N + 1, 0);
            int now = 0;
            for (int i = 1; i <= N; ++i) {
                x = N - in.nextInt() + 1; 
                insert(x);
                now += query(x - 1);
            }
            if (now > ans) {
                ans = now;
                label = k;
            }
        }
        out.println(label);
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
