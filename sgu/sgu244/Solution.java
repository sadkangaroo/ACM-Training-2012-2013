import java.io.*;
import java.math.*;
import java.util.*;
import java.text.*;

class Solver {
    private static final double eps = 1e-8;
    private double getBisector(double h, double d, double t) {
        double t1 = Math.hypot(h, d - t), t2 = Math.hypot(h, d + t);
        double p = (t2 * (d - t) + t1 * (d + t)) / (t1 + t2);
        return Math.hypot(h, p);
    }
    void solve(double AH, double AD, double AM) {
        if (!(Math.abs(AH - AD) < eps && Math.abs(AD - AM) < eps || AH < AD - eps && AD < AM - eps)) {
            System.out.println("NO"); 
            return;
        }
        double d = Math.sqrt(Math.max(0.0, AM * AM - AH * AH));
        double l = 0, r = 200.0, mid;
        while (l + eps < r) {
            mid = (l + r) / 2.0;
            if (getBisector(AH, d, mid) < AD) r = mid;
            else l = mid;
        }
        double t = (l + r) / 2.0;
        System.out.println("YES");
        System.out.printf(Locale.ENGLISH, "%.8f %.8f\n%.8f %.8f\n%.8f %.8f\n", 0.0, AH, d - t, 0.0, d + t, 0.0);
    }
}

public class Solution {
    public static void main(String args[]) {
        Scanner cin = new Scanner(System.in);
        double AH = cin.nextDouble(), AD = cin.nextDouble(), AM = cin.nextDouble();
        (new Solver()).solve(AH, AD, AM); 
    }

}
