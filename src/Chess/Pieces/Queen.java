package Chess.Pieces;

import java.util.LinkedList;

import Chess.Board;
import Chess.Move;

public class Queen extends Piece {
    
    public Queen(Colour colour) {
        super(colour, 'Q', 9);
    }

    // TODO: getLegalMoves()
    public LinkedList<Move> getLegalMoves(Board board, int rank, int file) {
        return null;
    }
    
}
