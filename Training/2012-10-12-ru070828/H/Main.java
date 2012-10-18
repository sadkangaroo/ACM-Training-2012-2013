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
        Mirror[] mirrors = new Mirror[N];
        for (int i = 0; i < N; ++i) {
            int x1 = cin.nextInt(), y1 = cin.nextInt();
            int x2 = cin.nextInt(), y2 = cin.nextInt();
            if (x1 == x2) {
                mirrors[i] = new Mirror(0, x1, Math.min(y1, y2), Math.max(y1, y2));
            }
            else mirrors[i] = new Mirror(1, y1, Math.min(x1, x2), Math.max(x1, x2));
        }
        (new Solver(S, T, Xt - Xd, Yt - Yd, mirrors)).solve();
    }
}

class Solver {
    int N, Dx, Dy;
    Point S, T;
    Mirror[] mirrors;
    boolean[] used;
    Solver(Point S, Point T, int Dx, int Dy, Mirror[] mirrors) {
        N = mirrors.length;
        this.S = S; this.T = T;
        int d = (int)Math.abs(MyMath.gcd(Dx, Dy));
        this.Dx = Dx / d; this.Dy = Dy / d;
        this.mirrors = mirrors;
        used = new boolean[N];
    }
    void solve() {
        int ans = -1;     
        for (int rx = -1; rx <= 1; rx += 2)
            for (int ry = -1; ry <= 1; ry += 2) {
                int now = check(rx, ry);
                if (now == -1) continue;
                if (ans == -1 || now < ans) ans = now;
            }
        System.out.println(ans);
    }
    int check(int rx, int ry) {
        Point now = S;
        for (int i = 0; i < N; ++i) used[i] = false;
        Rational min; int mirrorLabel = 0; Point nextPosition = null;
        int count = 0;
        while (true) {
            min = null;
            Rational nDx = Rational.valueOf(Dx * rx), nDy = Rational.valueOf(Dy * ry);
            for (int i = 0; i < N; ++i) if (!used[i]) {
                if (mirrors[i].type == 0) {
                    if (Dx == 0) continue; 
                    Rational t = (mirrors[i].t.subtract(now.x)).divide(nDx); 
                    Point crossPoint = new Point(mirrors[i].t, now.y.add(t.multiply(nDy)));
                    if (crossPoint.y.compareTo(mirrors[i].l) >= 0
                            && crossPoint.y.compareTo(mirrors[i].r) <= 0
                                && t.compareTo(Rational.valueOf(0)) > 0) {
                                    if (min == null || t.compareTo(min) < 0) {
                                        min = t; mirrorLabel = i; nextPosition = crossPoint;
                                    }
                    }
                }
                else {
                    if (Dy == 0) continue;
                    Rational t = (mirrors[i].t.subtract(now.y)).divide(nDy);
                    Point crossPoint = new Point(now.x.add(t.multiply(nDx)), mirrors[i].t);
                       if (crossPoint.x.compareTo(mirrors[i].l) >= 0
                            && crossPoint.x.compareTo(mirrors[i].r) <= 0
                                && t.compareTo(Rational.valueOf(0)) > 0) {
                                    if (min == null || t.compareTo(min) < 0) {
                                        min = t; mirrorLabel = i; nextPosition = crossPoint;
                                    }
                    }
                }
            }
            
            Rational t;
            if (T.subtract(now).x.multiply(nDy).compareTo(T.subtract(now).y.multiply(nDx)) == 0) {
                if (Dx != 0) t = T.subtract(now).x.divide(nDx);
                else t = T.subtract(now).y.divide(nDy);
                if (t.compareTo(Rational.valueOf(0)) > 0) {
                    if (min == null || t.compareTo(min) < 0)
                        if (rx == 1 && ry == 1) {
                            return count;
                        }
                }
            }
            if (min == null) break;
            else {
                if (mirrors[mirrorLabel].type == 0) rx *= -1;
                else ry *= -1;
                now = nextPosition;
                used[mirrorLabel] = true;
                count++;
            }
        }
        return -1;
    }
}

class Mirror {
    int type;
    Rational t, l, r; 
    Mirror(int type, int t, int l, int r) {
        this.type = type; 
        this.t = Rational.valueOf(t); this.l = Rational.valueOf(l); this.r = Rational.valueOf(r);
    }
    void out() {
        System.out.print(type + " ");
        t.out(); l.out(); r.out();
        System.out.println();
    }
}

class Point {
    Rational x, y; 
    Point(Rational x, Rational y) {
        this.x = x; this.y = y;
    }
    Point(int x, int y) {
        this.x = Rational.valueOf(x); this.y = Rational.valueOf(y);
    }
    Point subtract(Point t) {
        return new Point(x.subtract(t.x), y.subtract(t.y));
    }
    void out() {
        x.out(); System.out.print(", "); y.out(); System.out.println();
    }
}

class Rational implements Comparable<Rational> {
    long a, b;  
    Rational(long a, long b) {
        this.a = a; this.b = b;
        reduce();
    }
    void reduce() {
        long d = MyMath.gcd(a, b); 
        a /= d; b /= d;
        if (b < 0) {
            a *= -1; b *= -1; 
        }
    }
    public int compareTo(Rational t) {
        return Long.signum(a * t.b - b * t.a);
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
    static Rational valueOf(long a) {
        return new Rational(a, 1);
    }
    void out() {
        System.out.print(a + "/" + b + " ");
    }
}

class MyMath {
    static long gcd(long a, long b) {
        if (b == 0) return a;
        return gcd(b, a % b);
    }
}
