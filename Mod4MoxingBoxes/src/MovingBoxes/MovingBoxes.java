package MovingBoxes;

import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

public class MovingBoxes {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int numCases = Integer.parseInt(in.nextLine()); // number of test cases in input
        for (int i = 0; i < numCases; i++) {
            System.out.println("Case " + (i+1));
            ReadInput(in);
        }
        in.close();
    }
    
    public static void ReadInput(Scanner in) {
        String[] info = in.nextLine().split(" ");
        int b = Integer.parseInt(info[0]);  // total number of boxes
        int m = Integer.parseInt(info[1]);  // number of boxes not shipped
        int c = Integer.parseInt(info[2]);  // number of companies
        
        Solution [] solutions = new Solution[c];
        
        String[] line;
        for (int i = 0; i < c; i++) {
            line = in.nextLine().split(" ");
            int boxes = b;
            String company = line[0];
            int perBox = Integer.parseInt(line[1]);
            int half = Integer.parseInt(line[2]);

            int minCost = 0;
            while (boxes > 0) {
                if (boxes - m <= m && boxes - m >= 0) {
                    minCost += ((boxes - m)*perBox);
                    boxes = 0;
                }
                else if (half < (boxes*perBox)) {
                    minCost += half;
                    boxes = boxes -(int)Math.ceil((double)boxes/2);
                }
                else {
                    minCost += (boxes*perBox);
                    boxes = 0;
                }
            }
            solutions[i] = new Solution(company, minCost);
        }
        Arrays.sort(solutions, new SortByMinCost());
        for (int i = 0; i < c; i++) {
            System.out.println(solutions[i].getCompany() + " " + solutions[i].getMinCost());
        }
    }
}

class Solution {
    String company;
    int minCost;
    public Solution(String c, int m) {
        setCompany(c);
        setMinCost(m);
    }
    public void setCompany(String c) {this.company = c;}
    public void setMinCost(int m) {this.minCost = m;}
    public String getCompany() {return this.company;}
    public int getMinCost() {return this.minCost;}
}

class SortByMinCost implements Comparator<Solution> {
    public int compare(Solution a, Solution b) { 
        int diff = a.getMinCost() - b.getMinCost();
        return diff;
//        if (diff != 0) return diff;
//        else return a.getCompany().compareTo(b.getCompany()); 
    }
}
