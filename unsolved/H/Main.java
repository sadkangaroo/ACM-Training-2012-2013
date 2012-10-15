import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
    public static void main(String args[]) {
        Scanner cin = new Scanner(System.in);  
        int N = cin.nextInt();
        int Xs = cin.nextInt(), Ys = cin.nextInt();
        Point S = new Point(Xs, Ys);
        int Xt = cin.nextInt(), Yt = cin.nextInt();
        Point T = new Point(Xt, Yt);
        int Xd = cin.nextInt(), Yd = cin.nextInt();
        Rational Dir = new Rational(Xt - Xd, Yt - Yd);
        Mirror[] mirrors = new Mirror[N];
        for (int i = 0; i < N; ++i) {
            int x1 = cin.nextInt(), y1 = cin.nextInt();
            int x2 = cin.nextInt(), y2 = cin.nextInt();
            if (x1 == x2) {
                mirrors[i] = new Mirror(0, x1, Math.min(y1, y2), Math.max(y1, y2));
            }
            else mirrors[i] = new Mirror(1, y1, Math.min(x1, x2), Math.max(x1, x2));
        }
        (new Solver(S, T, Dir, mirrors)).solve();
    }
}

class Solver {
    int N;
    Point S, T;
    Rational Dir;
    Mirror[] mirrors;
    boolean[] used;
    Solver(Point S, Point T, Rational Dir, Mirror[] mirrors) {
        N = mirrors.length;
        this.S = S; this.T = T;
        this.Dir = Dir;
        this.mirrors = mirrors;
        used = new boolean[N];
    }
    void solve() {
        int ans = -1;     
        for (int rx = -1; rx <= 1; rx += 2)
            for (int ry = -1; ry <= 1; ry += 2) {
                int now = check(rx, ry);
                if (ans == -1 || now < ans) ans = now;
            }
        System.out.println(ans);
    }
    int check(int rx, int ry) {
        Point now = S;
        for (int i = 0; i < N; ++i) used[i] = false;
        Rational min; int label;
        while (true) {
            for (int i = 0; i < N; ++i) if (!used[i]) {
                label = -1;
                if (mirrors[i].type == 0) {
                    if (Dir.x == 0) continue; 
                    Rational t = (mirros[i].t - now.x); 
                    Point crossPoint = new Point(mirrors[i].t, now.y + t.divide(Dir));
                    if (crossPoint.compareTo(mirrors[i].l) >= 0 
                            crossPoint.compareTo(mirrors[i].r) <= 0) {
                        if (label == -1 || t.compareTo(min) < 0) {
                            label = i; min = t;
                        }
                    }
                }
                else {
                    if (Dir.y == 0) continue;
                    
                }
            }
        }
        return -1;
    }
}

class Mirror {
    int type, t, l, r; 
    Mirror(int type, int t, int l, int r) {
        this.type = type; this.t = t;
        this.l = l; this.r = r;
    }
}

class Point {
    Rational x, y; 
    Point(Rational x, Rational y) {
        this.x = x; this.y = y;
    }
    Point(int x, int y) {
        this.x = new Rational(x, 1); this.y = new Rational(y, 1);
    }
}

class Rational {
    long a, b;  
    Rational(int a, int b) {
        this.a = a; this.b = b;
        reduce();
    }
    void reduce() {
       int d = Math.abs(MyMath.gcd(a, b)); 
       a /= d; b /= d;
    }
    Rational add(Rational t) {
        return new Rational(a * t.b + b * t.a, b * t.b);
    }
    Rational subtract(Rational t) {
        return new Rational(a * t.b - b * t.a, b * t.b); 
    }
    Rational multiply(Rational t) {
        return new Rational(a * t.a, b * t.b);
    }
    Rational divide(Rational t) {
        return new Rational(a * t.b, b * t.a);
    }
}

class MyMath {
    static int gcd(int a, int b) {
        if (b == 0) return a;
        return gcd(b, a % b);
    }
}
