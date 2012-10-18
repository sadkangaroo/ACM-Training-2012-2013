import java.util.*;
import java.io.*;
import java.math.*;

public class Main {
	public static void main(String arg[]) {
		Scanner cin = new Scanner(System.in);		
		try {
			while (true) {
				int N = cin.nextInt();
				Dwarf[] dwarfs = new Dwarf[N + 1];
				int body, arm;
				for (int i = 1; i <= N; ++i) {
					body = cin.nextInt(); arm = cin.nextInt();	
					dwarfs[i] = new Dwarf(body, arm);
				}
				Arrays.sort(dwarfs, 1, N + 1);
				int H = cin.nextInt();
				System.out.println((new Solver()).solve(dwarfs, N, H));
			}
		} catch (NoSuchElementException e) {}
	}
}

class Solver {
	int[][] dp;	
	int[] sum;
	int solve(Dwarf[] dwarfs, int N, int H) {
		dp = new int[N + 1][N + 1];	
		dp[0][0] = H;
		sum = new int[N + 1];
		sum[0] = 0;
		for (int i = 1; i <= N; ++i) sum[i] = sum[i - 1] + dwarfs[i].body;
		for (int i = 1; i <= N; ++i)
			for (int j = 0; j <= i; ++j) {
				dp[i][j] = 0;
				if (i != j) dp[i][j] = Math.max(dp[i][j], dp[i - 1][j] + dwarfs[i].body);
				if (j != 0) dp[i][j] = Math.max(dp[i][j], Math.min(dp[i - 1][j - 1], sum[i - 1] + dwarfs[i].body + dwarfs[i].arm));
			}
		for (int i = N; i >= 0; --i)
			if (dp[N][i] >= H) return i;
		return -1;
	}
}

class Dwarf implements Comparable<Dwarf> {
	int body, arm;
	Dwarf(int body, int arm) {
		this.body = body; this.arm = arm;
	}
	public int compareTo(Dwarf t) {
		return (t.body + t.arm) - (body + arm);
	}
}
