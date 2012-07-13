import java.util.*;
import java.math.*;
import java.io.*;

class Node implements Comparable {
    String name; int lab;
    Node(String _name, int _lab) {
        name = _name; lab = _lab;
    }
    public int compareTo(Object t) {
        return name.compareTo(((Node)t).name);
    }
}

public class Solution implements Runnable {

    public static void main(String args[]) {
        new Solution().run();
    }

    BufferedReader reader;
    StringTokenizer tokenizer;
    PrintWriter writer;

    int N;
    String[] a;
    Node[] b;
    int[] ma, mb;

    private void solve() throws Exception {
        N = nextInt();
        a = new String[N];
        b = new Node[N];
        for (int i = 0; i < N; ++i) {
            a[i] = nextToken();
        }
        for (int i = 0; i < N; ++i) {
            b[i] = new Node(nextToken(), i);
        }
        Arrays.sort(b, 0, N);
        ma = new int[N]; mb = new int[N];
        for (int i = 0; i < N; ++i) {
            ma[i] = b[Arrays.binarySearch(b, 0, N, new Node(a[i], 0))].lab;
            mb[ma[i]] = i;
        }
        int ca = 0, cb = 0, last = 0;
        for (int i = 0; i < N; ++i) {
            if (ma[i] < i) cb++;
            else if (ma[i] > i) ca--;
            if (mb[i] < i) ca++;
            else if (mb[i] > i) cb--;
            if (ca == 0 && cb == 0) {
               Arrays.sort(a, last, i + 1); 
               for (int k = last; k <= i; ++k)
                   writer.println(a[k]);
               last = i + 1;
            }
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


