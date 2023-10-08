package Tests.PieceTests;

import org.junit.Test;
import static org.junit.Assert.assertEquals;

import java.util.LinkedList;

import Chess.Board;
import Chess.Pieces.*;
import Chess.Move;
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
    }
}
