package Tests.PieceTests;

import org.junit.Test;
import static org.junit.Assert.assertEquals;

import Chess.Board;
import Chess.Pieces.*;
import Chess.Position;

public class PawnTest {
    
    @Test
    public void getLegalMovesTest() {
        Board board = new Board();

        Position whitePawnPos = new Position(3, 6);
        
        assertEquals(1, Piece.WHITE_PAWN.getLegalMoves(board, whitePawnPos).size());

        board.setPiece(4, 6, Piece.BLACK_BISHOP);
        assertEquals(0, Piece.WHITE_PAWN.getLegalMoves(board, whitePawnPos).size());

        board.setPiece(4, 6, Piece.WHITE_BISHOP);
        assertEquals(0, Piece.WHITE_PAWN.getLegalMoves(board, whitePawnPos).size());

        board.setPiece(4, 5, Piece.BLACK_PAWN);
        assertEquals(1, Piece.WHITE_PAWN.getLegalMoves(board, whitePawnPos).size());

        board.setPiece(4, 7, Piece.BLACK_KNIGHT);
        assertEquals(2, Piece.WHITE_PAWN.getLegalMoves(board, whitePawnPos).size());

        board.setPiece(4, 6, Piece.NO_PIECE);
        assertEquals(3, Piece.WHITE_PAWN.getLegalMoves(board, whitePawnPos).size());

        board = new Board();
        board.setPiece(3, 3, Piece.WHITE_KING);
        board.setPiece(4, 4, Piece.WHITE_PAWN);
        board.setPiece(5, 5, Piece.BLACK_QUEEN);
        assertEquals(1, Piece.WHITE_PAWN.getLegalMoves(board, 4, 4).size());
    }

    @Test
    public void promotionTest() {
        Board board = new Board();

        Position whitePawnPos = new Position(6, 5);

        // 1 move forward, 4 promotion options
        board.setPiece(whitePawnPos, Piece.WHITE_PAWN);
        assertEquals(4, Piece.WHITE_PAWN.getLegalMoves(board, whitePawnPos).size());

        // 1 moves forward, 1 diagonal, 4 promotions each
        board.setPiece(7, 6, Piece.BLACK_QUEEN);
        assertEquals(8, Piece.WHITE_PAWN.getLegalMoves(board, whitePawnPos).size());

        // pawn blocked on the front, 1 move diagonal
        board.setPiece(7, 5, Piece.BLACK_QUEEN);
        assertEquals(4, Piece.WHITE_PAWN.getLegalMoves(board, whitePawnPos).size());

        // Pawn is pinned to the king, blocked on the front and no moves diagonal
        board.setPiece(5, 5, Piece.WHITE_KING);
        assertEquals(0, Piece.WHITE_PAWN.getLegalMoves(board, whitePawnPos).size());
    }
}
