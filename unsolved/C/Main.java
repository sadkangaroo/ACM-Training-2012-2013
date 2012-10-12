import java.util.*;
import java.io.*;
import java.math.*;

public class Main {
	public static void main(String args[]) {
		Scanner cin = new Scanner(System.in);		
		Solver solver = new Solver();
		while (true) {
			int N = cin.nextInt();	
			if (N == 0) break;
			Circle[] haws = new Circle[N];
			for (int i = 0; i < N; ++i) {
				double x = cin.nextDouble(), y = cin.nextDouble(), z = cin.nextDouble();
				haws[i] = new Circle(x, y, z);
			}
			solver.solve(N, haws);
		}
	}
}

class Solver {
	double normalize(double x) {
		while (x < 0) x += 2 * Math.PI;
		while (x >= 2 * Math.PI) x -= 2 * Math.PI;
		return x;
	}
	void solve(int N, Circle[] haws) {
		Event[] events = new Event[N * 2];
		int ans = 0;
		for (int i = 0; i < N; ++i) {
			int top = 0, now = 1;
			for (int j = 0; j < N; ++j) if (j != i) {
				double t1 = haws[i].intangent(haws[j]);								
				double t2 = haws[i].outtangent(haws[j]);
				t1 = normalize(t1); t2 = normalize(t2);
				events[top++] = new Event(t1, 1, haws[i]); events[top++] = new Event(t2, -1);
				if (t1 > t2) now++;	
			}
			Arrays.sort(events, 0, top);
			int cnt = now;
			for (int k = 0; k < top; ++k) {
				now += events[k].type;
				cnt = Math.max(cnt, now);
			}
			ans = Math.max(ans, cnt);
		}
		System.out.println(ans);
	}
}

class Circle {
	double x, y, r;
	Circle(double x, double y, double r) {
		this.x = x; this.y = y; this.r = r;
	}
	double outtangent(Circle t) {
		double d = Math.sqrt(Math.hypot(x - t.x, y - t.y));	
		double delta = Math.asin((t.r - r) / d);
		return Math.atan2(t.y - y, t.x - x) + delta;			
	}
	double intangent(Circle t) {
		double d = Math.sqrt(Math.hypot(x - t.x, y - t.y));	
		d = d * r / (r + t.r);
		double delta = Math.asin((t.r - r) / d);
		return Math.atan2(t.y - y, t.x - x) - delta;			
	}
}

class Event implements Comparable<Event> {
	double x; int type; Circle haw;
	Event(double x, int type, Circle haw) {
		this.x = x; this.type = type; this.haw = haw;
	}
	public int compareTo(Event t) {
		if (Math.abs(x - t.x) < MyMath.eps) {
			return t.type - type;
		}
		else {
			if (x > t.x) return 1;
			else return -1;
		}
	}
}

final class MyMath {
	static double eps = 1e-8;
}
