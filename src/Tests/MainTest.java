package Tests;

import Chess.*;

public class MainTest {

    public static void main(String[] args) {
        testPrintBoard();
    }

    static void testPrintBoard() {
        Board board = Board.createDefaultBoard();

        String s = board.toString();

        for(int i = 0; i < s.length(); i++) {
            System.out.print(s.charAt(i));
        }
    }
    


}
