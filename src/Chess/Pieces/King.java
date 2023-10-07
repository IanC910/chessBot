package Chess.Pieces;

import java.util.LinkedList;

import Chess.Board;
import Chess.Position;

public class King extends Piece {
    
    public King(Colour colour) {
        super(colour, 'K', 0);
    }

    // TODO: getLegalMoves()
    public LinkedList<Position> getLegalMoves(Board board, Position position) {
        return null;
    }
    
}
