package Tests;

import org.junit.Test;
import static org.junit.Assert.assertEquals;

import Chess.Board;

public class BoardTest {

    @Test
    public void ConstructorTest() {
        Board board = new Board();

        for(int r = Board.MIN_RANK; r < Board.MAX_RANK; r++) {
            for(int f = Board.MIN_FILE; f < Board.MAX_FILE; f++) {
                assertEquals(null, board.getPiece(r, f));
            }
        }
    }
    
}
