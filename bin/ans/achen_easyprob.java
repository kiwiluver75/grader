/*
PROG: easyprob
LANG: JAVA
*/

import java.util.*;
import java.io.*;

public class easyprob
{
    public static void main(String[] alex) throws IOException
    {
        //BufferedReader w = new BufferedReader(new FileReader("easyprob.in"));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("easyprob.out")));

	Scanner sc=new Scanner(System.in);
        int sum = 0;
        int N = Integer.parseInt(sc.nextLine());
        for(int i = 0; i < N; i++)
            sum += Integer.parseInt(sc.nextLine());
        System.out.println(sum);
        //out.close();

        System.exit(0);
    }
}
