package Tests;

import org.junit.Test;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import Chess.Board;
import Chess.Pieces.Piece;

public class BoardTest {

    @Test
    public void constructorTest() {
        Board board = new Board();

        for(int r = Board.MIN_RANK; r <= Board.MAX_RANK; r++) {
            for(int f = Board.MIN_FILE; f <= Board.MAX_FILE; f++) {
                assertEquals(Piece.NO_PIECE, board.getPiece(r, f));
            }
        }
    }

    @Test
    public void setPieceTest() {
        Board board = new Board();

        for(int r = Board.MIN_RANK; r <= Board.MAX_RANK; r++) {
            for(int f = Board.MIN_FILE; f <= Board.MAX_FILE; f++) {
                assertEquals(Piece.NO_PIECE, board.getPiece(r, f));
            }
        }

        Piece testPiece = Piece.WHITE_KING;

        board.setPiece(0, 0, testPiece);

        assertEquals(testPiece, board.getPiece(0, 0));
    }

    @Test
    public void cloneTest() {
        Board board = Board.createDefaultBoard();

        Board clone = board.clone();

        assertTrue(board.equals(clone));

        Piece testPiece = Piece.WHITE_KNIGHT;

        clone.setPiece(0, 0, testPiece);

        assertFalse(board.equals(clone));
    }
    
}
