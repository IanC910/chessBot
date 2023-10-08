package Chess.Pieces;

import java.util.LinkedList;

import Chess.Board;
import Chess.Move;

public class Rook extends Piece {
    
    public Rook(Colour colour) {
        super(colour, 'R', 5);
    }

    // TODO: getLegalMoves()
    public LinkedList<Move> getLegalMoves(Board board, int rank, int file) {
        return null;
    }
    
}
