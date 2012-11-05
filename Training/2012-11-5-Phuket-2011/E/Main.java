import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
    public static void main(String[] args) {
        (new Solver()).solve();        
    }
}

class Solver {
    int[][] sg = new int[25][4 * 768];
    void preSolve() {
        int R = 25, C = 4 * 768;
        int[] hash = new int[R * C + 5];
        Arrays.fill(hash, 0);
        int cnt = 0;
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                if (i == 0 && j == 0) sg[i][j] = 0;
                else {
                    cnt++;
                    for (int k = 0; k < i; ++k)
                        hash[sg[k][j]] = cnt;
                    for (int k = 0; k < j; ++k)
                        hash[sg[i][k]] = cnt;
                    for (int k = 1; k <= i && k <= j; ++k)
                        hash[sg[i - k][j - k]] = cnt;
                    for (int k = 0; ; k++)
                        if (hash[k] != cnt) {
                            sg[i][j] = k;
                            break;
                        }
                }
            }
        }
    }
    long getSG(int x, long y) {
        if (y >= 4 * 768) {
            int y2 = (int)(y % 768 + 3 * 768);
            return sg[x][y2] + (y - y2);
        }
        else return sg[x][(int)y];
    }
    void solve() {
        preSolve();
        Scanner cin = new Scanner(System.in);
        int T = cin.nextInt(); 
        for (int tt = 0; tt < T; ++tt) {
            int R = cin.nextInt(); long C = cin.nextLong(); int N = cin.nextInt(); 
            long ans = 0;
            int x; long y;
            for (int i = 0; i < N; ++i) {
                x = cin.nextInt() - 1; y = cin.nextLong() - 1; 
                ans = (ans ^ getSG(x, y));
            }
            if (ans == 0) System.out.println("NO");
            else System.out.println("YES");
        }
    }
}
