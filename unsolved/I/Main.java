import java.util.*;
import java.io.*;
import java.math.*;

public class Main {
	public static void main(String args[]) {
		int[][] f = (new Solver()).solve(1000);
		Scanner cin = new Scanner(System.in);
		try {
			while (true) {
				int N = cin.nextInt();
				System.out.println(f[N][N]);
			}
		} catch (NoSuchElementException e) {}
	}
}

class Solver {
	int[][] solve(int N) {
		int[][] f = new int[N + 1][N + 1], g = new int[N + 1][N + 1];	
		for (int i = 1; i <= N; ++i)
			for (int j = 1; j <= N; ++j) {
				if (i == 1 || j == 1) {
					f[i][j] = g[i][j] = 1;
				}
				else {
					f[i][j] = g[i][j] = 0;
					for (int k = 1; k * k <= i; ++k) {
						if (i % k == 0) {
							if (k != 1) f[i][j] += g[i / k][j];
							int t = i / k;
							if (t != k) f[i][j] += g[k][j];
						}
					}
					for (int k = 1; k * k <= j; ++k) {
						if (j % k == 0) {
							if (k != 1) g[i][j] += f[i][j / k];
							int t = j / k;
							if (t != k ) g[i][j] += f[i][k];
						}
					}
				}
			}
		for (int i = 1; i <= N; ++i)
			for (int j = 1; j <= N; ++j)
				f[i][j] = (f[i][j] + g[i][j]) / 2;
		return f;
	}
}
