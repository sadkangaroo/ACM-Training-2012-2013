import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
    public static void main(String args[]) throws IOException {
        (new Solver()).solve(); 
    }
}

class Solver {

    static final int MaxRequestNumber = 80000;
    static final int MaxBlockNumber = 30000;
    static final int Duration = 600;

    int Q;
    Request[] requests = new Request[MaxRequestNumber];
    int[] count = new int[MaxBlockNumber + 5];
    TreeSet<Integer> freeBlocks = new TreeSet<Integer>();

    void solve() throws IOException {

        InputReader in = new InputReader(System.in);
        PrintWriter out = new PrintWriter(System.out);
        Q = 0;
        try {
            while (true) {
                int time = in.nextInt(), pos;
                String tag = in.nextToken();
                if (tag.compareTo("+") == 0) pos = -1;
                else pos = in.nextInt();
                requests[Q] = new Request(time, pos, Q);
                Q++;     
            } 
        } catch (NullPointerException e) {}
        Arrays.sort(requests, 0, Q);
        for (int i = 1; i <= MaxBlockNumber; ++i) {
            count[i] = 0;
            freeBlocks.add(i);
        }
        int head = 0;
        for (int i = 0; i < Q; ++i) {
            int now = requests[i].time;
            while (now >= requests[head].time + Duration) { 
                int pos = requests[head].pos;
                if (pos != -1) {
                    count[pos]--;
                    if (count[pos] == 0) 
                        freeBlocks.add(pos);
                }
                head++;
            }
            if (requests[i].pos == -1) {
                int freeOne = freeBlocks.pollFirst();
                out.println(freeOne);    
                requests[i].pos = freeOne;
                count[freeOne]++;
            }
            else {
                int pos = requests[i].pos;                
                if (count[pos] == 0) {
                    out.println("-");
                    requests[i].pos = -1;
                }
                else {
                    out.println("+");
                    count[pos]++;
                }
            }
        }

        in.close(); out.close();

    }

}
        
class Request implements Comparable<Request> {
    int time, pos, order;
    Request(int time, int pos, int order) {
        this.time = time;
        this.pos = pos;
        this.order = order;
    }
    public int compareTo(Request t) {
        if (time != t.time) return time - t.time;    
        else return order - t.order;
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
