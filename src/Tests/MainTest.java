package Tests;

import Chess.*;

public class MainTest {

    public static void main(String[] args) {
        Board board = Rules.createDefaultBoard();

        String s = board.toString();

        for(int i = 0; i < s.length(); i++) {
            if(s.charAt(i) == '\n') {

            }
            else
                System.out.print(s.charAt(i));
        }
    }
    
}
