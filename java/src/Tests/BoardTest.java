package Tests;

import org.junit.Test;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import Chess.*;
import Chess.Pieces.*;

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

        Piece piece = clone.getPiece(Board.WHITE_START_RANK, Board.L_KNIGHT_START_FILE);
        assertTrue(piece.equals(Piece.WHITE_KNIGHT));
        
        clone.setPiece(Board.WHITE_START_RANK + 2, Board.L_KNIGHT_START_FILE + 1, piece);
        assertFalse(board.equals(clone));

        clone.setPiece(Board.WHITE_START_RANK, Board.L_KNIGHT_START_FILE, Piece.NO_PIECE);
        assertFalse(board.equals(clone));
    }

    @Test
    public void getKingPosTest() {
        Board board = Board.createDefaultBoard();

        Position whiteKingPos = board.getKingPos(Colour.WHITE);

        assertEquals(Board.WHITE_START_RANK, whiteKingPos.rank);
        assertEquals(Board.KING_START_FILE,  whiteKingPos.file);
    }
    
}
