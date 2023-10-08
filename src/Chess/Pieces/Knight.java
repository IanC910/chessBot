package Chess.Pieces;

import java.util.LinkedList;

import Chess.Board;
import Chess.Move;

public class Knight extends Piece {
    
    public Knight(Colour colour) {
        super(colour, 'N', 3);
    }

    // TODO: getLegalMoves()
    public LinkedList<Move> getLegalMoves(Board board, int rank, int file) {
        return null;
    }
    
}
