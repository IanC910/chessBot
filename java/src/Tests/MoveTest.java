package Tests;

import org.junit.Test;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import Chess.Move;
import Chess.Position;
import Chess.Board;
import Chess.Pieces.*;

public class MoveTest {

    @Test
    public void doesCheckOwnKingTest() {
        // Diagonal pin line
        // Attacker
        Board board = new Board();
        board.setPiece(0, 0, Piece.WHITE_KING);
        board.setPiece(5, 5, Piece.BLACK_BISHOP);
        Move move = new Move(1, 1, Piece.WHITE_PAWN, 2, 1);
        assertTrue(move.checksOwnKing(board));

        // Horizontal pin line
        // Attacker
        board = new Board();
        board.setPiece(7, 7, Piece.BLACK_KING);
        board.setPiece(7, 0, Piece.WHITE_ROOK);
        move = new Move(7, 6, Piece.BLACK_ROOK, 6, 6);
        assertTrue(move.checksOwnKing(board));

        // Horizontal pin line
        // Attacker
        // Move in same pin line
        board = new Board();
        board.setPiece(7, 7, Piece.BLACK_KING);
        board.setPiece(7, 0, Piece.WHITE_ROOK);
        move = new Move(7, 6, Piece.BLACK_ROOK, 7, 5);
        assertFalse(move.checksOwnKing(board));

        // Vertical pin line
        // Attacker
        // Defender
        board = new Board();
        board.setPiece(0, 5, Piece.WHITE_KING);
        board.setPiece(1, 5, Piece.WHITE_KNIGHT);
        board.setPiece(7, 5, Piece.BLACK_QUEEN);
        move = new Move(5, 5, Piece.WHITE_QUEEN, 1, 1);
        assertFalse(move.checksOwnKing(board));

        // Diagonal pin line
        // No Attacker
        board = new Board();
        board.setPiece(4, 5, Piece.WHITE_KING);
        move = new Move(6, 3, Piece.WHITE_KNIGHT, 4, 4);
        assertFalse(move.checksOwnKing(board));
    }
    
}
