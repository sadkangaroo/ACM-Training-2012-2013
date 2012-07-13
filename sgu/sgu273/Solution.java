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

    int N;
    String s;
    boolean[][][] trans = new boolean[4][4][4];
    int[] lab = new int[256], num = new int[4];
    int[][][] f;
    char col[] = new char[4];

    boolean dp(int l, int r, int c) {
        if (l == r) return s.charAt(l) == col[c];
        if (f[l][r][c] != -1) return f[l][r][c] == 1;
        int res = 0;
        for (int mid = l; mid < r; ++mid) {
            for (int i = 0; i < 4; ++i) if (dp(l, mid, i))
                for (int j = 0; j < 4; ++j) if (dp(mid + 1, r, j))
                    if (trans[i][j][c]) res = 1;
        }
        return (f[l][r][c] = res) == 1;
    }

    private void solve() throws Exception {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                for (int k = 0; k < 4; ++k)
                    trans[i][j][k] = false;
        lab['b'] = 0; lab['r'] = 1; lab['y'] = 2; lab['w'] = 3;
        col[0] = 'b'; col[1] = 'r'; col[2] = 'y'; col[3] = 'w';
        String ans = ""; char c1, c2;
        for (int i = 0; i < 4; ++i) num[i] = nextInt();
        for (int i = 0; i < 4; ++i) {
            for (int k = 0; k < num[i]; ++k) {
                s = nextToken();
                c1 = s.charAt(0); c2 = s.charAt(1);
                trans[lab[c1]][lab[c2]][i] = true;
            }
        }
        s = nextToken(); 
        N = s.length();
        f = new int[N][N][4];
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                for (int k = 0; k < 4; ++k)
                    f[i][j][k] = -1;
        for (int i = 0; i < 4; ++i)
            if (dp(0, N - 1, i)) ans += col[i];
        if (ans.compareTo("") == 0) writer.println("Nobody");
        else writer.println(ans);
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


