import java.util.*;
import java.math.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        (new Solver()).solve();
    }
}

class Solver {

    InputReader in;
    PrintWriter out;

    static final int MaxScore = 100;

    int N;
    MyList[] teams = new MyList[MaxScore + 5];
   
    void solve() throws IOException {
        in = new InputReader(System.in);
        out = new PrintWriter(System.out);

        N = in.nextInt();
        for (int i = 0; i <= MaxScore; ++i) teams[i] = new MyList();
        for (int i = 0; i < N; ++i) {
            int id = in.nextInt(), score = in.nextInt();
            teams[score].list.add(id);
        }
        for (int i = MaxScore; i >= 0; --i)
            for (int id: teams[i].list)
                out.println(id + " " + i);

        in.close(); out.close();
    }
}

class MyList {
    ArrayList<Integer>list;
    MyList() {
        list = new ArrayList<Integer>();
    }
}

class InputReader {
    BufferedReader reader;
    StringTokenizer tokenizer;
    InputReader(InputStream in) throws IOException {
        reader = new BufferedReader(new InputStreamReader(in));
        tokenizer = new StringTokenizer("");
    }
    String nextToken() throws IOException {
        while (!tokenizer.hasMoreTokens()) 
            tokenizer = new StringTokenizer(reader.readLine());
        return tokenizer.nextToken();
    }
    int nextInt() throws IOException {
        return Integer.parseInt(nextToken()); 
    }
    void close() throws IOException {
        reader.close();
    }
}
