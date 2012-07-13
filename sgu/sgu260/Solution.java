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
    int[] state;
    int[][] S;
    boolean[][] a;
    boolean isFree[], ans[];

    int Gauss() {
        int i, j, k, p;
        for (i = 0, j = 0; i < N && j < N; ++i, ++j) {
            for (k = i; k < N; ++k) if (a[k][j] == true) break;
            if (k == N) {isFree[j] = true; i--; continue;}
            for (p = j; p <= N; ++p) {boolean tmp = a[i][p]; a[i][p] = a[k][p]; a[k][p] = tmp;}
            for (k = i + 1; k < N; ++k) if (a[k][j] == true) {
                for (p = j; p <= N; ++p) a[k][p] ^= a[i][p];
            }
        }
        if (i != N) {
            for (k = i; k < N; ++k) if (a[k][N] == true) return -1;
        }
        return N - i;
    }

    int solve(int col) {
        isFree = new boolean[N];
        Arrays.fill(isFree, 0, N, false);
        for (int i = 0; i < N; ++i)
            Arrays.fill(a[i], 0, N + 1, false);
        for (int i = 0; i < N; ++i) 
            if (state[i] != col) a[i][N] = true;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < S[i].length; ++j) {
                a[S[i][j]][i] = true;
            }
        return Gauss();
    }

    void getAns(int freeNum) {
        ans = new boolean[N];       
        for (int i = N - 1 - freeNum, j = N - 1; i >= 0; --i, --j) {
            if (isFree[j]) {i++; continue;}
            for (int k = j + 1; k < N; ++k) {
                a[i][N] ^= ans[k] & a[i][k];
            }
            ans[j] = a[i][N];
        }
        int cnt = 0;
        for (int i = 0; i < N; ++i) if (ans[i]) cnt++;
        writer.println(cnt);
        for (int i = 0; i < N; ++i) {
            if (ans[i]) {
                cnt--;
                if (cnt == 0) writer.println(i + 1);
                else writer.print(i + 1 + " ");
            }
        }
    }

    private void solve() throws Exception {
        N = nextInt();
        S = new int[N][];
        for (int i = 0; i < N; ++i) {
            int num = nextInt(), x;
            S[i] = new int[num];
            for (int k = 0; k < num; ++k) {
                x = nextInt();
                x--;
                S[i][k] = x;
            }
        }
        state = new int[N];
        for (int i = 0; i < N; ++i) {
            state[i] = nextInt();
        }
        a = new boolean[N + 1][N + 1];
        int t;
        if ((t = solve(1)) >= 0) getAns(t);
        else if ((t = solve(0)) >= 0) getAns(t);
             else writer.println(-1);
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


