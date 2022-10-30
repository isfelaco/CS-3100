package Trading;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;

public class Trading {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        ReadInput(in);
    }
    
    public static void ReadInput(Scanner in) {
        String count = in.nextLine();
        int num = Integer.parseInt(count);
        String line;
        Point[] points = new Point[num];
        if (num == 0) {
            in.close();
            return;
        }
        for (int i = 0; i < num; i++) {
            line = in.nextLine();
            if (line.length() != 1) {
                String[] idk = line.split(" ", 2);
                Point p = new Point(Double.parseDouble(idk[0]), Double.parseDouble(idk[1]));
                points[i] = p;
            }
        }
        Arrays.sort(points, new SortByX());
        double ans = solve(points);
        if (ans == 10000.0) System.out.println("infinity");
        else System.out.println(String.format("%.4f", ans));
        
        ReadInput(in);
    }
    
    public static double solve(Point[] points) {
        if (points.length <= 3) return getMin(points);
        
        // finding the median X point to split array
        int median = points.length/2;
        Point midPoint = points[median];
        
        // sorting by Y
        Point[] pointsX = points;
        Arrays.sort(pointsX, new SortByX());
        
        // splitting Y sorted at the median
        Point[] left = Arrays.copyOfRange(pointsX, 0, median);
        Point[] right = Arrays.copyOfRange(pointsX, median, points.length);
        
        // getting minimum distance on each side
        double leftMin = getMin(left);
        double rightMin = getMin(right);
        double d = Math.min(leftMin, rightMin);
        
        // creating the strip
        List<Point> strip = new ArrayList<>();
        for (int i = 0; i < pointsX.length; i++) {
            if (Math.abs(pointsX[i].getX() - midPoint.getX()) <= d) strip.add(points[i]);
        }
        double stripMin = getStripMin(strip, d);

        return Math.min(d, stripMin);
    }
    
    public static double getMin(Point[] points) {
        // brute force algorithm to get minimum distance
        double min = 10000.0;
        for (int i = 0; i < points.length; ++i)
            for (int j = i+1; j < points.length; ++j)
                if (getDist(points[i], points[j]) < min) min = getDist(points[i], points[j]);
        return min;
    }
    
    public static double getStripMin(List<Point> strip, double min)
    {
        Collections.sort(strip, new SortByY());
        int size = strip.size();
        for (int i = 0; i < size; ++i) {
            for (int j = i+1; j < size && (strip.get(j).getY() - strip.get(i).getY()) < min; ++j)
                if (getDist(strip.get(i),strip.get(j)) < min)
                    min = getDist(strip.get(i), strip.get(j));
        };
        return min;
    }
    
    public static double getDist(Point a, Point b) {
        double x1 = a.getX();
        double y1 = a.getY();
        double x2 = b.getX();
        double y2 = b.getY();       
        return Math.sqrt((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1));
    }

}

class Point {
    double xCord;
    double yCord;

    public Point(double x, double y) {
        setX(x);
        setY(y);
    }
    public void setX(double x) { this.xCord = x; }
    public void setY(double y) { this.yCord = y; }
    public double getX() { return this.xCord; }
    public double getY() { return this.yCord; }
}

class SortByX implements Comparator<Point> {
    public int compare(Point a, Point b) { return (int)(a.getX() - b.getX()); }
}
class SortByY implements Comparator<Point> {
    public int compare(Point a, Point b) { return (int)(a.getY() - b.getY()); }
}


