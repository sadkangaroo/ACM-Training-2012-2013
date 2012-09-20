import java.io.*;
import java.math.*;
import java.util.*;

class Solver {
    BigInteger solve(int N, int M, int W, int H, int K) {
        if (W > N) W = N;
        if (H > N) H = N;
        if (M + H < N) H = N - M;
        if (M + W < N) W = N - M;
        if (K > N + M) return BigInteger.ZERO;
        int D = M + W - N;
        BigInteger[][][] f = new BigInteger[M + H + 1][K + 1][D + 1];
        for (int i = 0; i <= M + H; ++i)
            for (int j = 0; j <= K; ++j)
                for (int k = 0; k <= D; ++k)
                    f[i][j][k] = BigInteger.ZERO;
        f[0][0][0] = BigInteger.ONE;
        for (int i = 0; i < M + H; ++i) 
            for (int j = 0; j <= K; ++j)
                for (int k = 0; k <= D; ++k)
                    if (f[i][j][k].compareTo(BigInteger.ZERO) > 0) {
                        f[i + 1][j][k] = f[i + 1][j][k].add(f[i][j][k]);
                        if (j < K) {
                            if (i + 1 <= M + H - N) {
                                if (k < D) f[i + 1][j + 1][k + 1] = f[i + 1][j + 1][k + 1].add(f[i][j][k].multiply(BigInteger.valueOf(D - k)));
                                if (j - k < M - D) f[i + 1][j + 1][k] = f[i + 1][j + 1][k].add(f[i][j][k].multiply(BigInteger.valueOf(M - D - j + k)));
                            }
                            else 
                            if (i + 1 > M) {
                                if (j - k < N) f[i + 1][j + 1][k] = f[i + 1][j + 1][k].add(f[i][j][k].multiply(BigInteger.valueOf(N - j + k))); 
                            }
                            else {
                                if (k < D) f[i + 1][j + 1][k + 1] = f[i + 1][j + 1][k + 1].add(f[i][j][k].multiply(BigInteger.valueOf(D - k)));
                                if (j - k < N) f[i + 1][j + 1][k] = f[i + 1][j + 1][k].add(f[i][j][k].multiply(BigInteger.valueOf(N - j + k))); 
                            }
                        }
                    }
        BigInteger res = BigInteger.ZERO;
        for (int i = 0; i <= D; ++i)
            res = res.add(f[M + H][K][i]);
        return res;
    }
}

public class Solution {
    public static void main(String args[]) {
        Scanner cin = new Scanner(System.in);
        int N = cin.nextInt(), M = cin.nextInt();
        int W = cin.nextInt(), H = cin.nextInt(), K = cin.nextInt();
        System.out.println((new Solver()).solve(N, M, W, H, K));
    }
}
