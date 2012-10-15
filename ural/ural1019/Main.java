import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
    public static void main(String args[]) {
        Scanner cin = new Scanner(System.in);
        int N = cin.nextInt();
        N++;
        Segment[] segments = new Segment[N];
        int[] points = new int[N * 2 + 1];
        int top = 0;
        points[top++] = -1;
        for (int i = 1; i < N; ++i) {
            int l = cin.nextInt(), r = cin.nextInt(), color;
            String c = cin.next();
            if (c.compareTo("w") == 0) color = 0;
            else color = 1;
            segments[i] = new Segment(l, r, color);
            points[top++] = l;
            points[top++] = r;
        }
        final int MAX = 1000000000;
        segments[0] = new Segment(0, MAX, 0);
        points[top++] = 0;
        points[top++] = MAX;
        Arrays.sort(points, 0, top);
        (new Solver()).solve(segments, MyArray.unique(points, 0, top));
    }
}

class Solver {
    int[] fa, color;
    int grand(int x) {
        if (fa[x] == x) return fa[x];
        return fa[x] = grand(fa[x]);
    }
    void solve(Segment[] segments, int[] points) {
        for (Segment segment: segments) {
            segment.l = Arrays.binarySearch(points, segment.l);
            segment.r = Arrays.binarySearch(points, segment.r) - 1;
        }
        fa = new int[points.length];
        color = new int[points.length];
        for (int i = 0; i < fa.length; ++i) fa[i] = i;
        for (int i = segments.length - 1; i >= 0; --i) {
            int now = grand(segments[i].r); 
            while (now >= segments[i].l) {
                color[now] = segments[i].color;
                fa[now] = now - 1;
                now = grand(now);
            }
        }
        Answer answer = new Answer(-1, -1);
        int current = 0;
        for (int i = 2; i < points.length; ++i) {
            current += points[i] - points[i - 1];
            if (i == points.length - 1 || color[i] != color[i - 1]) {
                if (color[i - 1] == 0) answer.update(points[i] - current, points[i]);
                current = 0;
            }
        }
        System.out.println(answer.l + " " + answer.r);
    }
}

class Segment {
    int l, r, color;
    Segment(int l, int r, int color) {
        this.l = l; this.r = r; this.color = color;
    }
}

class Answer {
    int l, r;
    Answer(int l, int r) {
        this.l = l; this.r = r;
    }
    void update(int l, int r) {
        if (r - l > this.r - this.l || r - l == this.r - this.l && l < this.l) {
            this.l = l; this.r = r;
        }
    }
}

class MyArray {
    static int[] unique(int[] a, int fromIndex, int toIndex) {
        int top = 0;
        int[] res = new int[toIndex - fromIndex + 1];
        for (int i = fromIndex; i < toIndex; ++i)
            if (i == toIndex - 1 || a[i] != a[i + 1])
                res[top++] = a[i];
        return Arrays.copyOfRange(res, 0, top);
    }
}
