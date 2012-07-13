import java.util.*;
import java.math.*;
import java.io.*;

public class Solution implements Runnable {

    public static void main(String args[]) {
        new Solution().run();
    }

    BufferedReader reader;
    StringTokenizer tokenizer;
    PrintWriter writer;

    private void solve() throws Exception {
        int N = nextInt();
        for (int i = 0; i < N; ++i) {
            long M = nextLong(); 
            M = Math.max((M << 3) - 7, 0);
            long t = (long)(Math.sqrt(M) + 0.5);
            if (t * t == M && (t & 1) == 1 && t >= 3)
                writer.println("YES");
            else writer.println("NO");
        }
    }

    public void run() {
        try {

            reader = new BufferedReader(new InputStreamReader(System.in));
            tokenizer = null;
            writer = new PrintWriter(System.out);
            solve();
            reader.close(); writer.close();

        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    int nextInt() throws Exception {
        return Integer.parseInt(nextToken());
    }

    long nextLong() throws Exception {
        return Long.parseLong(nextToken());
    }

    double nextDouble() throws Exception {
        return Double.parseDouble(nextToken());
    }

    String nextToken() throws Exception {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            tokenizer = new StringTokenizer(reader.readLine());
        }
        return tokenizer.nextToken();
    }

}


