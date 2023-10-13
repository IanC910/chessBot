package Chess.Pieces;

import java.util.LinkedList;

import Chess.Board;
import Chess.Colour;
import Chess.Move;

public class King extends Piece {
    
    public King(Colour colour) {
        super(colour, 'K', 0);
    }

    // TODO: getLegalMoves()
    public LinkedList<Move> getLegalMoves(Board board, int rank, int file) {
        return null;
    }
    
}
