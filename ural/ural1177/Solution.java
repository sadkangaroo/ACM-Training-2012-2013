import java.io.*;
import java.math.*;
import java.util.*;

public class Solution {

    public static void main(String args[]) throws IOException {
        (new Solver()).solve();
    }

}

class Solver {

    int N;

    String getInner(String s) {
        return s.substring(1, s.length() - 1);
    }

    void solve() throws IOException {

        InputReader in = new InputReader(System.in);
        PrintWriter out = new PrintWriter(System.out);

        N = in.getNumber();
        for (int i = 0; i < N; ++i) {
            String str = in.nextLine();
            out.println(str);
        }

        in.close();
        out.close();

    }

}

class InputReader {

    BufferedReader reader;

    InputReader(InputStream in) {
        reader = new BufferedReader(new InputStreamReader(in)); 
    }

    int getNumber() throws IOException {
        return Integer.parseInt(reader.readLine());
    }

    String nextLine() throws IOException {
        return reader.readLine();
    }

    void close() throws IOException {
        reader.close();
    }

}


