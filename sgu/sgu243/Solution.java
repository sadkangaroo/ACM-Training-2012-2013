import java.io.*;
import java.math.*;
import java.util.*;

class Cell implements Comparable<Cell>, Cloneable {
    int x, y;
    Cell() {}
    Cell(int x, int y) {
        this.x = x; this.y = y;
    }
    public int compareTo(Cell t) {
        if (x != t.x) return x - t.x;
        return y - t.y;
    }
    public Cell clone() {
        return new Cell(x, y);
    }
}

class Piece implements Comparable<Piece>, Cloneable {
    char type; 
    ArrayList<Cell> elements;      
    int minY, maxY, maxX;
    Piece(char type) {
        elements = new ArrayList<Cell>();
        this.type = type;
    }
    void add(Cell x) {
        elements.add(x);
    }
    void rotate() {
        for (Cell now: elements) {
            int tmp = now.x; now.x = now.y; now.y = -tmp;
        }
    }
    void normalize() {
        Collections.sort(elements);
        int dx = elements.get(0).x, dy = elements.get(0).y;
        for (Cell now: elements) {
            now.x -= dx; now.y -= dy;
        }
    }
    public int compareTo(Piece t) {
        if (t.elements.size() != elements.size()) return t.elements.size() - elements.size();
        for (int i = 0; i < elements.size(); ++i)
            if (elements.get(i).compareTo(t.elements.get(i)) != 0) return t.elements.get(i).compareTo(elements.get(i));
        return 0;
    }
    public Piece clone() {
        Piece res = new Piece(type);
        for (Cell now: elements)
            res.add(now.clone());
        Collections.sort(elements);
        maxX = elements.get(0).x; minY = minY = elements.get(0).y;
        for (Cell now: elements) {
            maxX = Math.max(maxX, now.x);
            minY = Math.min(minY, now.y);
            maxY = Math.max(maxY, now.y);
        }
        return res;
    }
}

class Map {
    private final int N = 20;
    private char[][] map; 
    private boolean[][] visited;
    void load(Scanner cin) {
        map = new char[N][N];
        for (int i = 0; i < N; ++i) {
            String row = cin.next();
            for (int j = 0; j < N; ++j)
                map[i][j] = row.charAt(j);
        }
    }
    private boolean ok(int x, int y) {
        return x >= 0 && x < N && y >= 0 && y < N;
    }
    private void dfs(int nx, int ny, Piece piece) {
        piece.add(new Cell(nx, ny));
        visited[nx][ny] = true;
        for (int dx = -1; dx <= 1; ++dx)
            for (int dy = -1; dy <= 1; ++dy)
                if (Math.abs(dx + dy) == 1) {
                    int tx = nx + dx, ty = ny + dy;
                    if (ok(tx, ty) && !visited[tx][ty] && map[tx][ty] == piece.type) {
                        dfs(tx, ty, piece); 
                    }
                }
    }
    void travel(ArrayList<Piece> pieces) {
        visited = new boolean[N][N];
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) 
                visited[i][j] = false; 
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) 
                if (!visited[i][j] && map[i][j] != '.') {
                    Piece piece = new Piece(map[i][j]);
                    dfs(i, j, piece);
                    Piece[] tmp = new Piece[4];
                    for (int k = 0; k < 4; ++k) {
                        piece.rotate();
                        piece.normalize();
                        tmp[k] = piece.clone();
                    }
                    for (int k = 0; k < 4; ++k) {
                        int p;
                        for (p = 0; p < k; ++p) {
                           if (tmp[k].compareTo(tmp[p]) == 0) break; 
                        }
                        if (p == k) pieces.add(tmp[k]);
                    }
                }
    }
}

class Solver {
    private int N;
    private char[][] ans;
    private boolean[][] covered;
    private boolean[] used;
    private boolean found;
    private ArrayList<Piece> pieces;
    Solver(int N) {
        this.N = N;
        ans = new char[N][N];
        covered = new boolean[N][N];
        used = new boolean[26];
        for (int i = 0; i < 26; ++i) used[i] = false;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                covered[i][j] = false;
        found = false;
    }
    private void print() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) System.out.print(ans[i][j]);
            System.out.println();
        }
    }
    private boolean ok(int x, int y) {
        return x >= 0 && x < N && y >= 0 && y < N;
    }
    private boolean ok(int x, int y, Piece piece) {
        for (Cell now: piece.elements) 
            if (!ok(x + now.x, y + now.y) || covered[x + now.x][y + now.y]) return false;
        return true;
    }
    private void cover(int x, int y, Piece piece, boolean flag) {
        for (Cell now: piece.elements) {
            if (flag) ans[x + now.x][y + now.y] = piece.type;
            covered[x + now.x][y + now.y] = flag;
        }
    }
    private void dfs(int x, int y) {
       if (y == N) {
           x++; y = 0;
       }   
       if (x == N) {
           found = true; return;
       }
       if (covered[x][y]) dfs(x, y + 1);
       if (found) return;
       for (Piece now: pieces) if (!used[now.type - 'A']) {
           if (ok(x, y, now)) {
               cover(x, y, now, true);
               used[now.type - 'A'] = true;
               dfs(x, y + 1);
               if (found) return;
               used[now.type - 'A'] = false;
               cover(x, y, now, false);
           }
       }
    }
    void solve(ArrayList<Piece> pieces) {
        this.pieces = pieces;
        dfs(0, 0);
        if (found) print(); 
    }
}

public class Solution {
    public static void main(String args[]) {
        Scanner cin = new Scanner(System.in);
        int N = cin.nextInt();
        Map table = new Map(); 
        table.load(cin);
        ArrayList<Piece> pieces = new ArrayList<Piece>();
        table.travel(pieces);
        (new Solver(N)).solve(pieces);
    }
}
