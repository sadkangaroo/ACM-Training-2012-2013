import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
    public static void main(String[] args) {
        (new Solver()).solve(); 
    }
}

class Solver {
    int L, A, M;
    Square[] squares;
    int[] coX, coY;
    int[][] importance;
    int[][] maxValue;
    void solve() {
        Scanner cin = new Scanner(System.in);
        L = cin.nextInt(); A = cin.nextInt(); M = cin.nextInt();
        squares = new Square[M];
        importance = new int[M * 2 + 2][M * 2 + 2];
        maxValue = new int[M * 2 + 2][M * 2 + 2];
        coX = new int[M * 2 + 2]; coY = new int[M * 2 + 2];
        for (int i = 0; i < M; ++i) {
            int ipt = cin.nextInt(), side = cin.nextInt();
            int x1 = cin.nextInt(), y1 = cin.nextInt();
            squares[i] = new Square(ipt, x1, y1, side);
            coX[2 * i] = squares[i].x1; coX[2 * i + 1] = squares[i].x2;
            coY[2 * i] = squares[i].y1; coY[2 * i + 1] = squares[i].y2;
        }
        coX[2 * M] = 1; coX[2 * M + 1] = L + 1;
        coY[2 * M] = 1; coY[2 * M + 1] = L + 1;
        coX = MyUtils.normalize(coX, M * 2 + 2); coY = MyUtils.normalize(coY, M * 2 + 2); 
        coverSquares();
        check();
    }
    void check() {
        int top = 0, ans = 255;;
        for (int bot = 0; bot < coX.length; ++bot) { 
            while (top < coX.length && coX[top] - coX[bot] < A) top++;
            if (top != coX.length) {
                for (int i = 0; i < coY.length; ++i) {
                    int tmp = importance[bot][i];
                    for (int k = bot + 1; k < top; ++k)
                        tmp = Math.max(tmp, importance[k][i]);
                    maxValue[bot][i] = tmp;
                }
                for (int i = 0; i < coY.length; ++i) {
                    int tmp = maxValue[bot][i];
                    for (int j = i + 1; j < coY.length; ++j) {
                        if (coY[j] - coY[i] >= A) ans = Math.min(ans, tmp);
                        tmp = Math.max(tmp, maxValue[bot][j]); 
                    }
                }
            }
        }
        if (ans <= 100) System.out.println(ans);
        else System.out.println("IMPOSSIBLE");
    }
    void coverSquares() {
        for (int i = 0; i < coX.length; ++i)
            for (int j = 0; j < coY.length; ++j)
                importance[i][j] = 1;
        for (int k = 0; k < M; ++k) {
            int x1 = Arrays.binarySearch(coX, squares[k].x1); 
            int x2 = Arrays.binarySearch(coX, squares[k].x2); 
            int y1 = Arrays.binarySearch(coY, squares[k].y1); 
            int y2 = Arrays.binarySearch(coY, squares[k].y2); 
            for (int i = x1; i < x2; ++i)
                for (int j = y1; j < y2; ++j)
                    importance[i][j] = squares[k].importance;
        }
    }
}

class Square {
    int x1, y1, x2, y2, importance; 
    Square(int importance, int x1, int y1, int side) {
        this.importance = importance;
        this.x1 = x1; this.y1 = y1;
        this.x2 = x1 + side; this.y2 = y1 + side;
    }
}

class MyUtils {
    static int[] normalize(int[] a, int size) {
        Arrays.sort(a, 0, size);
        int len = 0;
        for (int i = 0; i < size; ++i) {
            if (i == size - 1 || a[i] != a[i + 1])
                a[len++] = a[i];
        }
        return Arrays.copyOf(a, len);
    }
}
