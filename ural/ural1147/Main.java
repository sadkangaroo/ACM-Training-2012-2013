import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
    public static void main(String[] args) {
        (new Solver()).solve();
    }
}

class Solver {

    static final int MaxColorNumber = 2500;

    int A, B, N;
    Rect[] rects;
    int[] area;
    int[] coX, coY;

    Solver() {
        area = new int[MaxColorNumber + 5];
        Arrays.fill(area, 0);
    }
    void solve() {
        Scanner cin = new Scanner(System.in);
        A = cin.nextInt(); B = cin.nextInt(); N = cin.nextInt();
        N++;
        rects = new Rect[N];
        rects[0] = new Rect(0, 0, A, B, 1);
        ArrayList<Integer> _coX = new ArrayList<Integer>();
        ArrayList<Integer> _coY = new ArrayList<Integer>();
        for (int i = 0; i < N; ++i) {
            if (i != 0) {
                rects[i] = new Rect(); 
                rects[i].load(cin);
            }
            _coX.add(rects[i].x1); _coX.add(rects[i].x2);
            _coY.add(rects[i].y1); _coY.add(rects[i].y2);
        }
        coX = MyUtils.normalize(_coX); coY = MyUtils.normalize(_coY);
        Strip[] strips = new Strip[coX.length];
        for (int i = 0; i < coX.length; ++i) strips[i] = new Strip(coY.length);
        for (int i = N - 1; i >= 0; --i) {
            int x1 = Arrays.binarySearch(coX, rects[i].x1) + 1; 
            int y1 = Arrays.binarySearch(coY, rects[i].y1) + 1;
            int x2 = Arrays.binarySearch(coX, rects[i].x2); 
            int y2 = Arrays.binarySearch(coY, rects[i].y2);
            for (int k = x1; k <= x2; ++k)
                if (y1 <= y2)
                    strips[k].paint(y1, y2, rects[i].color, area, coX[k] - coX[k - 1], coY);
        }
        for (int i = 1; i <= MaxColorNumber; ++i) 
            if (area[i] != 0)
                System.out.println(i + " " + area[i]);
    }
}

class Strip {
    short[] fa;
    Strip(int len) {
        fa = new short[len];
        for (short i = 0; i < len; ++i) fa[i] = i;
    }
    short grand(short x) {
        if (fa[x] == x) return x;
        return fa[x] = grand(fa[x]);
    }
    void paint(int l, int r, int c, int[] area, int height, int[] coX) {
        while (r >= l) {
            if (grand((short)r) == r) {
                area[c] += height * (coX[r] - coX[r - 1]);
                fa[r] = (short)(r - 1);
            }
            r = grand((short)r);
        }
    }
}

class Rect {
    int x1, y1, x2, y2, color;
    Rect() {}
    Rect(int x1, int y1, int x2, int y2, int color) {
        this.x1 = x1; this.y1 = y1;
        this.x2 = x2; this.y2 = y2;
        this.color = color;
    }
    void load(Scanner cin) {
        x1 = cin.nextInt(); y1 = cin.nextInt(); 
        x2 = cin.nextInt(); y2 = cin.nextInt();
        color = cin.nextInt();
    }
}

class MyUtils {
    static int[] normalize(ArrayList<Integer> _a) {
        Collections.sort(_a);
        int[] a = new int[_a.size()];
        int top = 0;
        for (int i = 0; i < _a.size(); ++i) {
            if (i + 1 == _a.size() || _a.get(i) != _a.get(i + 1))
                a[top++] = _a.get(i);
        }
        return Arrays.copyOf(a, top);
    }
}
