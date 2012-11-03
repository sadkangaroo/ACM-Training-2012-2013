import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
    public static void main(String args[]) throws IOException {
        (new Solver()).solve();
    }
}

class Solver {

    static final int MaxCo = 32001;
    int N;
    int[] c, sum;
    void insert(int pos, int x) {
        for (int i = pos; i <= MaxCo; i += (i & (-i)))
            c[i] += x;
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

        N = in.nextInt();
        c = new int[MaxCo + 5];
        sum = new int[N + 5];
        Arrays.fill(c, 1, MaxCo + 1, 0);
        Arrays.fill(sum, 0, N + 1, 0);
        for (int i = 0; i < N; ++i) {
            int x = in.nextInt() + 1, y = in.nextInt();
            sum[query(x)]++;
            insert(x, 1);    
        }
        for (int i = 0; i < N; ++i) 
            out.println(sum[i]);

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


