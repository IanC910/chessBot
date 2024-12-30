package Chess.Pieces;

import java.util.LinkedList;

import Chess.Board;
import Chess.Colour;
import Chess.Move;

public class Bishop extends Piece {
    
    public Bishop(Colour colour) {
        super(colour, 'B', 3);
    }

    // TODO: getLegalMoves()
    public LinkedList<Move> getLegalMoves(Board board, int rank, int file) {
        return null;
    }
    
}
