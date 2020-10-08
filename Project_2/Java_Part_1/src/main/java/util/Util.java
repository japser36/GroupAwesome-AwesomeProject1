package util;

import java.util.Random;

public class Util {
    private static final Random random = new Random();

    /**
     *@return Return a random int
     */
    public static int getInt(int[] minMax){
        return getInt(minMax[0],minMax[1]);
    }

    /**
     *@return Return a random int
     */
    public static int getInt(int min, int max){
        int num = random.nextInt(((max - min)+1))+min;
        return num;
    }

}
